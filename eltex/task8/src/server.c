#include "threadpool.h"
#include "tcp_udp_server.h"

static int epollfd, tcp_sockfd, udp_sockfd, tcp_listenfd;
static int /*tclnts, */uclnts, nclnts;

static struct sockaddr_in udp_clients[POOLSIZ];

/*
 * Bug: if interrupt a tcp client while processing udp stuff --
 *      the program will crash :( also it crashes after long work
 *		w/ lot of clients... hmmm fix it soon
 */

// 1. 'udp_clients' doesnt work properly
// 2. no error handling

int
main(int argc, char *argv[])
{
	int nfds;
	struct epoll_event efds[2];

	server_state = INIT;

	while (0x1) {
		switch (server_state) {
			case IDLE:
				idle(&nfds, efds);
				server_state = RESPONSE;
				break;
			case RESPONSE:
				response(nfds, efds);
				server_state = IDLE;
				break;
			case INIT:
				init(argc, argv);
				server_state = IDLE;
				break;
			case ERROR:
//				error_handler();
				server_state = IDLE;
				break;
			default:
				fprintf(stderr, _RED_CLR"[System] "_DEF_CLR);
				perror("unknown error");
				exit(EXIT_FAILURE);
		}
	}

	return 0;
}

void
init(int argc, char *argv[])
{
	int rc, serv_len;
	struct sockaddr_in serv_addr;
	struct epoll_event ev;

	printf(_RED_CLR"[System]"_DEF_CLR" main thread: 0x%lx\n", pthread_self());

	if (argc < 2) {
		port = _DEF_PORT;
		printf(_RED_CLR"[System]"_DEF_CLR" using default port\n");
	} else
		port = atoi(argv[1]);

//	signal(SIGUSR1, (__sighandler_t) killthr);
	signal(SIGINT, (__sighandler_t) killproc);
	srand((unsigned) time(NULL));

	serv_len = sizeof(serv_addr);

	memset((char *) &serv_addr, 0, serv_len);
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	serv_addr.sin_port = htons(port);

	/* TCP part */

	tcp_listenfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (tcp_listenfd < 0) {
		fprintf(stderr, _RED_CLR"[System] "_DEF_CLR);
		perror("tcp socket");
		exit(EXIT_FAILURE);
	}

	int reuse = 1;

	rc = setsockopt(tcp_listenfd, SOL_SOCKET, SO_REUSEADDR,
		(const void *) &reuse, sizeof(reuse));
	if (rc < 0) {
		fprintf(stderr, _RED_CLR"[System] "_DEF_CLR);
		perror("setsockopt 1");
		exit(EXIT_FAILURE);
	}

	rc = bind(tcp_listenfd, (struct sockaddr *) &serv_addr, serv_len);
	if (rc < 0) {
		fprintf(stderr, _RED_CLR"[System] "_DEF_CLR);
		perror("tcp bind");
		exit(EXIT_FAILURE);
	}

	rc = listen(tcp_listenfd, MAX_LISTENERS);
	if (rc < 0) {
		fprintf(stderr, _RED_CLR"[System] "_DEF_CLR);
		perror("listen");
		exit(EXIT_FAILURE);
	}

	/* UDP part */

	udp_sockfd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	if (udp_sockfd < 0) {
		fprintf(stderr, _RED_CLR"[System] "_DEF_CLR);
		perror("udp socket");
		exit(EXIT_FAILURE);
	}

	rc = bind(udp_sockfd, (struct sockaddr *) &serv_addr, serv_len);
	if (rc < 0) {
		fprintf(stderr, _RED_CLR"[System] "_DEF_CLR);
		perror("udp bind");
		exit(EXIT_FAILURE);
	}

	printf(_BLUE_CLR"[Server]"_DEF_CLR" port: %d\n",
		ntohs(serv_addr.sin_port));

	/* EPOLL part */

	epollfd = epoll_create(0x666);
	if (epollfd < 0) {
		fprintf(stderr, _RED_CLR"[System] "_DEF_CLR);
		perror("epoll_create");
		exit(EXIT_FAILURE);
	}

	ev.events = EPOLLIN;
	ev.data.fd = tcp_listenfd;
	rc = epoll_ctl(epollfd, EPOLL_CTL_ADD, tcp_listenfd, &ev);
	if (rc < 0) {
		fprintf(stderr, _RED_CLR"[System] "_DEF_CLR);
		perror("epoll_ctl tcp");
		exit(EXIT_FAILURE);
	}

	ev.events = EPOLLIN;
	ev.data.fd = udp_sockfd;
	rc = epoll_ctl(epollfd, EPOLL_CTL_ADD, udp_sockfd, &ev);
	if (rc < 0) {
		fprintf(stderr, _RED_CLR"[System] "_DEF_CLR);
		perror("epoll_ctl udp");
		exit(EXIT_FAILURE);
	}

	tp_init(); // threadpool initializing
}

void
idle(int *nfds, struct epoll_event *efds)
{
	int nevents = 2;	// tcp/udp connection events
	int timeout = 1000; // ms

	while (0x1) {
		*nfds = epoll_wait(epollfd, efds, nevents, timeout);
		if (*nfds < 0) {
			fprintf(stderr, _RED_CLR"[System] "_DEF_CLR);
			perror("epoll");
			exit(EXIT_FAILURE);
		} else if (*nfds == 0) {
			printf(_BLUE_CLR"[Server]"_DEF_CLR" current time: %s", current_time());
			printf(_BLUE_CLR"[Server]"_DEF_CLR" active clients: %d\n", nclnts);
			if (pool.m_size > 0) {
				printf(_RED_CLR"[System]"_DEF_CLR" pool state:\n");
				for (int i = 0; i < pool.m_size; ++i) {
					printf("  [%d]: 0x%lx (%s)\n", pool.m_worker[i].m_id,
						(unsigned long) pool.m_worker[i].m_thread,
						pool.m_worker[i].m_busy ? "busy" : "free");
				}
			}
		} else break;
	}
}

void
response(int nfds, struct epoll_event *efds)
{
	int clnt_len;
	struct hostent *clnt_host;
	struct sockaddr_in clnt_addr;
	ssize_t bytes;

	clnt_len = sizeof(clnt_addr);

	for (int i = 0; i < nfds; ++i) {
		if (efds[i].data.fd == tcp_listenfd) {
			tcp_sockfd = accept(tcp_listenfd, (struct sockaddr *) &clnt_addr,
				(socklen_t *) &clnt_len);
			if (tcp_sockfd < 0) {
				fprintf(stderr, _RED_CLR"[System] "_DEF_CLR);
				perror("accept");
				exit(EXIT_FAILURE);
			}

			// grab information
			clnt_host = gethostbyaddr((const char *) &clnt_addr.sin_addr.s_addr,
				sizeof(clnt_addr.sin_addr.s_addr), AF_INET);
			if (clnt_host == NULL) {
				fprintf(stderr, _RED_CLR"[System] "_DEF_CLR);
				perror("gethostbyaddr");
				exit(EXIT_FAILURE);
			}

			printf(_BLUE_CLR"[Server]"_DEF_CLR" established connection with TCP client "
				"[ %s ~> %s:%d ]\n", clnt_host->h_name, inet_ntoa(clnt_addr.sin_addr),
				ntohs(clnt_addr.sin_port));

			choose_worker(tcp_sockfd, NULL, 0);
		}

		if (efds[i].data.fd == udp_sockfd) {
			char request[PKTSIZ];
			// for udp client 'request' is a number of packets to send
			bytes = recvfrom(udp_sockfd, request, PKTSIZ, 0, (struct sockaddr *) &clnt_addr,
				(socklen_t *) &clnt_len);
			if (bytes < 0) {
				fprintf(stderr, _RED_CLR"[System] "_DEF_CLR);
				perror("recvfrom");
				exit(EXIT_FAILURE);
			}

			int npkts = atoi(request);

			clnt_host = gethostbyaddr((const char *) &clnt_addr.sin_addr.s_addr,
				sizeof(clnt_addr.sin_addr.s_addr), AF_INET);
			if (clnt_host == NULL) {
				fprintf(stderr, _RED_CLR"[System] "_DEF_CLR);
				perror("gethostbyaddr");
				exit(EXIT_FAILURE);
			}

			if (!is_active_udp_client(ntohs(clnt_addr.sin_port))) {
				printf(_BLUE_CLR"[Server]"_DEF_CLR" established connection with UDP client "
					"[ %s ~> %s:%d ]\n", clnt_host->h_name, inet_ntoa(clnt_addr.sin_addr),
					ntohs(clnt_addr.sin_port));

//				udp_clients[uclnts++] = ntohs(clnt_addr.sin_port);
				udp_clients[0] = clnt_addr;
//				++nclnts;
			}

			choose_worker(npkts, (struct sockaddr *) &clnt_addr, sizeof(clnt_addr));
		}
	}
}

void
choose_worker(int val, struct sockaddr *clnt_addr, int clnt_len)
{
	int done = 0;

	for (int i = 0; i < pool.m_size; ++i) {
		if (!pool.m_worker[i].m_busy) {
			if (val == tcp_sockfd) // !!!!!!! tcp_sock can be eq to npkts
				pool.m_worker[i].m_job = tcp_routine;
			else
				pool.m_worker[i].m_job = udp_routine;

			pool.m_worker[i].m_val = val;
			pool.m_worker[i].m_busy = 1;
			done = 1;
			++nclnts;
			break;
		}
	}

	// server is busy, send notification to the client
	if (!done) {
		char notification[PKTSIZ];

		fprintf(stderr, _RED_CLR"[System]"_DEF_CLR" server is busy, no workers left\n");
		sprintf(notification, _CYAN_CLR"{NOTIFICATION}"_DEF_CLR
			" server is busy, try again later\n");

		ssize_t bytes;

		if (val == tcp_sockfd)
			bytes = send(tcp_sockfd, notification, PKTSIZ, 0);
		else
			bytes = sendto(udp_sockfd, notification, PKTSIZ, 0,
				clnt_addr, clnt_len);
		if (bytes < 0) {
			fprintf(stderr, _RED_CLR"[System] "_DEF_CLR);
			perror("send notification");
			exit(EXIT_FAILURE);
		}
	}

	// wake up the workers for check their job
	pthread_cond_broadcast(&pool.m_cond);
}

void *
udp_routine(int _npkts)
{
	int clnt_len;
	struct sockaddr_in clnt_addr;
	ssize_t bytes;

	clnt_addr = udp_clients[0];
	clnt_len = sizeof(clnt_addr);

	pthread_t this_thr = pthread_self();
	printf(_RED_CLR"[System]"_DEF_CLR" working thread: 0x%lx\n", this_thr);

	for (int i = 0; i < _npkts; ++i) {
		char packet[PKTSIZ];

		udp_pkt_gen(packet);

		bytes = sendto(udp_sockfd, packet, PKTSIZ, 0, (struct sockaddr *) &clnt_addr, clnt_len);
		if (bytes < 0) {
			fprintf(stderr, _RED_CLR"[System] "_DEF_CLR);
			perror("sendto");
			exit(EXIT_FAILURE);
		}
	}

	sleep(5);
	printf(_RED_CLR"[System]"_DEF_CLR" thread 0x%lx did the job\n", this_thr);

	--uclnts; --nclnts;	// not threadsafe xd

	return NULL;
}

void *
tcp_routine(int _sfd)
{
	int _sockfd = _sfd;
	ssize_t bytes;

	pthread_t this_thr = pthread_self();
	printf(_RED_CLR"[System]"_DEF_CLR" working thread: 0x%lx\n", this_thr);

	char packet[PKTSIZ];

	tcp_pkt_gen(packet);

	bytes = send(_sockfd, packet, PKTSIZ, 0);
	if (bytes < 0) {
		fprintf(stderr, _RED_CLR"[System] "_DEF_CLR);
		perror("send");
	}

	char request[PKTSIZ];

	bytes = recv(_sockfd, request, PKTSIZ, 0);
	if (bytes < 0) {
		fprintf(stderr, _RED_CLR"[System] "_DEF_CLR);
		perror("recv");
		exit(EXIT_FAILURE);
	}

	strcpy(packet, current_time());

	bytes = send(_sockfd, packet, PKTSIZ, 0);
	if (bytes < 0) {
		fprintf(stderr, _RED_CLR"[System] "_DEF_CLR);
		perror("send");
		exit(EXIT_FAILURE);
	}

	close(_sockfd);
//	pthread_kill(this_thr, SIGUSR1);

	sleep(5);
	printf(_RED_CLR"[System]"_DEF_CLR" thread 0x%lx did the job\n", this_thr);

	--nclnts;	// not threadsafe xd

	return NULL;
}

int
is_active_udp_client(unsigned short client)
{
	for (int i = 0; i < POOLSIZ; ++i) {
		if (udp_clients[i].sin_port == client)
			return 1;
	}

	return 0;
}

char *
current_time(void)
{
	struct tm *timeinfo;
	time_t rawtime;

	time(&rawtime);
	timeinfo = localtime(&rawtime);

	return asctime(timeinfo);
}
/*
void
killthr(void)
{
	--tclnts; --nclnts;

	printf(_BLUE_CLR"[Server]"_DEF_CLR" active requests: %d\n", nclnts);

	while (!tp_empty(&pool)) {
		pthread_t thr = tp_pop(&pool);
		printf(_RED_CLR"[System]"_DEF_CLR" thread destroyed: 0x%lx\n", thr);

		if (pool.m_cursize > 0) {
			printf(_RED_CLR"[System]"_DEF_CLR" current pool:\n");
			for (int i = 0; i < pool.m_cursize; ++i)
				printf("  [%d]: 0x%lx\n", i, (unsigned long) pool.m_threads[i]);
		}

		pthread_exit(NULL);
	}
}
*/
void __attribute__ ((noreturn))
killproc(void)
{
	close(tcp_listenfd);
	close(tcp_sockfd);
	close(udp_sockfd);
	close(epollfd);
	printf(_BLUE_CLR"[Server]"_DEF_CLR" quit\n");
	exit(EXIT_SUCCESS);
}

void
tcp_pkt_gen(char *pkt)
{
	int start = (int)' ';
	int end = (int)'~';
	int i = 3;

	pkt[0] = 'T';
	pkt[1] = 'C';
	pkt[2] = 'P';

	for (; i < PKTSIZ - 1; ++i)
		pkt[i] = (char)(start + rand() % (end - start));

	pkt[i] = '\0';
}

void
udp_pkt_gen(char *pkt)
{
	int start = (int)' ';
	int end = (int)'~';
	int i = 3;

	pkt[0] = 'U';
	pkt[1] = 'D';
	pkt[2] = 'P';

	for (; i < PKTSIZ - 1; ++i)
		pkt[i] = (char)(start + rand() % (end - start));

	pkt[i] = '\0';
}
