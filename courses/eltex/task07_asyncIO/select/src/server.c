#include "threadpool.h"
#include "tcp_udp_server.h"

static int tcp_sockfd, udp_sockfd, tcp_listenfd;
static int tclnts, uclnts, nclnts;
static struct threadpool_t pool;

static unsigned short udp_clients[MAX_THREADS];

int
main(int argc, char *argv[])
{
	int optval, rc, clnt_len, serv_len;
	int *_sockfd;
	struct hostent *clnt_host;
	struct sockaddr_in clnt_addr, serv_addr;
	fd_set readfds;

	pthread_t client_thr[MAX_THREADS];

	clnt_len = sizeof(clnt_addr);
	serv_len = sizeof(serv_addr);

	if (argc < 2) {
		port = _DEF_PORT;
		printf(_RED_CLR"[System]"_DEF_CLR" using default port: %d\n", port);
	} else
		port = atoi(argv[1]);

	/* TCP part */

	tcp_listenfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (tcp_listenfd < 0) {
		fprintf(stderr, _RED_CLR"[System] "_DEF_CLR);
		perror("tcp socket");
		exit(EXIT_FAILURE);
	}

	optval = 1;

	rc = setsockopt(tcp_listenfd, SOL_SOCKET, SO_REUSEADDR,
		(const void *) &optval, sizeof(optval));
	if (rc < 0) {
		fprintf(stderr, _RED_CLR"[System] "_DEF_CLR);
		perror("setsockopt");
		exit(EXIT_FAILURE);
	}

	memset((char *) &serv_addr, 0, serv_len);
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	serv_addr.sin_port = htons(port);

	rc = bind(tcp_listenfd, (struct sockaddr *) &serv_addr, serv_len);
	if (rc < 0) {
		fprintf(stderr, _RED_CLR"[System] "_DEF_CLR);
		perror("tcp bind");
		exit(EXIT_FAILURE);
	}

	rc = listen(tcp_listenfd, MAX_THREADS);
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

	rc = getsockname(tcp_listenfd, (struct sockaddr *) &serv_addr,
		(socklen_t *) &serv_len);
	if (rc < 0) {
		fprintf(stderr, _RED_CLR"[System] "_DEF_CLR);
		perror("getsockname");
		exit(EXIT_FAILURE);
	}

	printf(_BLUE_CLR"[Server]"_DEF_CLR" port: %d\n",
		ntohs(serv_addr.sin_port));

	signal(SIGUSR1, (__sighandler_t) killthr);
	signal(SIGINT, (__sighandler_t) killproc);

	int cid = 0;
	int nfds = (tcp_listenfd > udp_sockfd ? tcp_listenfd : udp_sockfd) + 1;

	tp_init(&pool);

	srand((unsigned) time(NULL));

	while (0x1) {
		FD_ZERO(&readfds);
		FD_SET(tcp_listenfd, &readfds);
		FD_SET(udp_sockfd, &readfds);

		rc = select(nfds, &readfds, NULL, NULL, NULL);
		if (rc < 0) {
			fprintf(stderr, _RED_CLR"[System] "_DEF_CLR);
			perror("select");
			exit(EXIT_FAILURE);
		}

		if (FD_ISSET(tcp_listenfd, &readfds)) {
			tcp_sockfd = accept(tcp_listenfd, (struct sockaddr *) &clnt_addr,
				(socklen_t *) &clnt_len);
			if (tcp_sockfd < 0) {
				fprintf(stderr, _RED_CLR"[System] "_DEF_CLR);
				perror("accept");
				exit(EXIT_FAILURE);
			}

			clnt_host = gethostbyaddr((const char *) &clnt_addr.sin_addr.s_addr,
				sizeof(clnt_addr.sin_addr.s_addr), AF_INET);
			if (clnt_host == NULL) {
				fprintf(stderr, _RED_CLR"[System] "_DEF_CLR);
				perror("gethostbyaddr");
				exit(EXIT_FAILURE);
			}

			printf(_BLUE_CLR"[Server]"_DEF_CLR" established connection with %s ~> %s:%d\n",
				clnt_host->h_name, inet_ntoa(clnt_addr.sin_addr), ntohs(clnt_addr.sin_port));

			_sockfd = malloc(sizeof(*_sockfd));
			*_sockfd = tcp_sockfd;

			rc = pthread_create(&client_thr[cid++], NULL, &tcp_routine, (void *) _sockfd);
			if (rc != 0) {
				fprintf(stderr, _RED_CLR"[System] "_DEF_CLR);
				perror("pthread_create");
				exit(EXIT_FAILURE);
			}

			++tclnts; ++nclnts;

			printf(_BLUE_CLR"[Server]"_DEF_CLR" active clients: %d\n", nclnts);
		}

		if (FD_ISSET(udp_sockfd, &readfds)) {
			char chkpkt[1];
			ssize_t bytes = recvfrom(udp_sockfd, chkpkt, 1, 0,
				(struct sockaddr *) &clnt_addr, (socklen_t *) &clnt_len);
			if (bytes < 0) {
				fprintf(stderr, _RED_CLR"[System] "_DEF_CLR);
				perror("recvfrom");
				exit(EXIT_FAILURE);
			}

			clnt_host = gethostbyaddr((const char *) &clnt_addr.sin_addr.s_addr,
				sizeof(clnt_addr.sin_addr.s_addr), AF_INET);
			if (clnt_host == NULL) {
				fprintf(stderr, _RED_CLR"[System] "_DEF_CLR);
				perror("gethostbyaddr");
				exit(EXIT_FAILURE);
			}

			if (!is_active_udp_client(ntohs(clnt_addr.sin_port))) {
				printf(_BLUE_CLR"[Server]"_DEF_CLR" established connection with %s ~> %s:%d\n",
					clnt_host->h_name, inet_ntoa(clnt_addr.sin_addr), ntohs(clnt_addr.sin_port));

				udp_clients[uclnts] = ntohs(clnt_addr.sin_port);
				++uclnts; ++nclnts;

				printf(_BLUE_CLR"[Server]"_DEF_CLR" active clients: %d\n", nclnts);
			}

			char packet[PKTSIZ];

			udp_pkt_gen(packet);

			bytes = sendto(udp_sockfd, packet, PKTSIZ, 0, (struct sockaddr *) &clnt_addr,
				clnt_len);
			if (bytes < 0) {
				fprintf(stderr, _RED_CLR"[System] "_DEF_CLR);
				perror("sendto");
				exit(EXIT_FAILURE);
			}

			bytes = recvfrom(udp_sockfd, packet, PKTSIZ, 0, NULL, NULL);
			if (bytes < 0) {
				fprintf(stderr, _RED_CLR"[System] "_DEF_CLR);
				perror("recvfrom");
				exit(EXIT_FAILURE);
			}

			bytes = recvfrom(udp_sockfd, chkpkt, 1, 0, (struct sockaddr *) &clnt_addr,
				(socklen_t *) &clnt_len);
			if (bytes < 0) {
				fprintf(stderr, _RED_CLR"[System] "_DEF_CLR);
				perror("recvfrom");
				exit(EXIT_FAILURE);
			}

			if (chkpkt[0] == 'q') {
				--uclnts; --nclnts;
				printf(_BLUE_CLR"[Server]"_DEF_CLR" active clients: %d\n", nclnts);
				// also need 2 rm from udp_clients
			}

		}

		if (cid == MAX_THREADS)
			// no error handling btw
			printf(_BLUE_CLR"[Server]"_DEF_CLR" clients limit is reached\n");
	}

	return 0;
}

void *
tcp_routine(void *_sfd)
{
	int _sockfd = *(int *) _sfd;
	ssize_t bytes;

	pthread_t this_thr = pthread_self();
	printf(_RED_CLR"[System]"_DEF_CLR" thread created: 0x%lx\n", this_thr);

	while (0x1) {
		char packet[PKTSIZ];

		tcp_pkt_gen(packet);

		bytes = send(_sockfd, packet, PKTSIZ, 0);
		if (bytes < 0) {
			fprintf(stderr, _RED_CLR"[System] "_DEF_CLR);
			perror("send");
			tp_push(&pool, this_thr);

			if (pool.m_cursize > 0) {
				printf(_RED_CLR"[System]"_DEF_CLR" current pool:\n");
				for (int i = 0; i < pool.m_cursize; ++i)
					printf("  [%d]: 0x%lx\n", i, (unsigned long) pool.m_threads[i]);
			}

			close(_sockfd);
			free(_sfd);
			pthread_kill(this_thr, SIGUSR1);
		}

		bytes = recv(_sockfd, packet, PKTSIZ, 0);
		if (bytes < 0) {
			fprintf(stderr, _RED_CLR"[System] "_DEF_CLR);
			perror("recv");
			tp_push(&pool, this_thr);

			if (pool.m_cursize > 0) {
				printf(_RED_CLR"[System]"_DEF_CLR" current pool:\n");
				for (int i = 0; i < pool.m_cursize; ++i)
					printf("  [%d]: 0x%lx\n", i, (unsigned long) pool.m_threads[i]);
			}

			close(_sockfd);
			free(_sfd);
			pthread_kill(this_thr, SIGUSR1);
		}

		pthread_yield();
	}

	return NULL;
}

int
is_active_udp_client(unsigned short client)
{
	for (int i = 0; i < MAX_THREADS; ++i) {
		if (udp_clients[i] == client)
			return 1;
	}

	return 0;
}

void
killthr(void)
{
	--tclnts; --nclnts;

	printf(_BLUE_CLR"[Server]"_DEF_CLR" active clients: %d\n", nclnts);

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

void __attribute__ ((noreturn))
killproc(void)
{
	close(tcp_listenfd);
	close(tcp_sockfd);
	close(udp_sockfd);
	printf(_BLUE_CLR"[Server]"_DEF_CLR" quit.\n");
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
