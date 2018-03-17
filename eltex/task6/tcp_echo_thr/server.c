#include "threadpool.h"
#include "tcp_echo.h"

static int sockfd, listenfd;
static int nclients;
static struct threadpool_t pool;

int
main(int argc, char *argv[])
{
	int optval, rc, clnt_len, serv_len;
	int *_sockfd;
	struct hostent *clnt_host;
	struct sockaddr_in clnt_addr, serv_addr;

	pthread_t client_thr[MAX_THREADS];

	clnt_len = sizeof(clnt_addr);
	serv_len = sizeof(serv_addr);

	if (argc < 2) {
		port = _DEF_PORT;
		printf(_RED_CLR"[System]"_DEF_CLR" using default port: %d\n", port);
	} else
		port = atoi(argv[1]);

	listenfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (listenfd < 0) {
		fprintf(stderr, _RED_CLR"[System] "_DEF_CLR);
		perror("socket");
		exit(EXIT_FAILURE);
	}

	optval = 1;

	rc = setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR,
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

	rc = bind(listenfd, (struct sockaddr *) &serv_addr, serv_len);
	if (rc < 0) {
		fprintf(stderr, _RED_CLR"[System] "_DEF_CLR);
		perror("bind");
		exit(EXIT_FAILURE);
	}

	rc = getsockname(listenfd, (struct sockaddr *) &serv_addr,
		(socklen_t *) &serv_len);
	if (rc < 0) {
		fprintf(stderr, _RED_CLR"[System] "_DEF_CLR);
		perror("getsockname");
		exit(EXIT_FAILURE);
	}

	printf(_BLUE_CLR"[Server]"_DEF_CLR" port: %d\n",
		ntohs(serv_addr.sin_port));

	rc = listen(listenfd, MAX_THREADS);
	if (rc < 0) {
		fprintf(stderr, _RED_CLR"[System] "_DEF_CLR);
		perror("listen");
		exit(EXIT_FAILURE);
	}

	signal(SIGUSR1, (__sighandler_t) killthr);
	signal(SIGINT, (__sighandler_t) killproc);

	int cid = 0;

	tp_init(&pool);

	while (0x1) {
		sockfd = accept(listenfd, (struct sockaddr *) &clnt_addr,
			(socklen_t *) &clnt_len);
		if (sockfd < 0) {
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
		*_sockfd = sockfd;

		rc = pthread_create(&client_thr[cid++], NULL, &server_routine, (void *) _sockfd);
		if (rc != 0) {
			fprintf(stderr, _RED_CLR"[System] "_DEF_CLR);
			perror("pthread_create");
			exit(EXIT_FAILURE);
		}

		printf(_BLUE_CLR"[Server]"_DEF_CLR" active clients: %d\n", ++nclients);

		if (cid == MAX_THREADS)
			// no error handling btw
			printf(_BLUE_CLR"[Server]"_DEF_CLR" clients limit is reached\n");
	}

	return 0;
}

void *
server_routine(void *_sfd)
{
	int _sockfd = *(int *) _sfd;
	int bytes;

	pthread_t this_thr = pthread_self();
	printf(_RED_CLR"[System]"_DEF_CLR" thread created: 0x%lx\n", this_thr);

	while (0x1) {
		char packet[MSGSIZ];

		msggen(packet);

		bytes = send(_sockfd, packet, MSGSIZ, 0);
		if (bytes < 0) {
			fprintf(stderr, _RED_CLR"[System] "_DEF_CLR);
			perror("send");
			tp_push(&pool, this_thr);

			if (pool.m_cursize > 0) {
				printf(_RED_CLR"[System]"_DEF_CLR" current pool:\n");
				for (int i = 0; i < pool.m_cursize; ++i)
					printf("  [%d]: 0x%x\n", i, (unsigned int) pool.m_threads[i]);
			}

			close(_sockfd);
			free(_sfd);
			pthread_kill(this_thr, SIGUSR1);
		}

		bytes = recv(_sockfd, packet, MSGSIZ, 0);
		if (bytes < 0) {
			fprintf(stderr, _RED_CLR"[System] "_DEF_CLR);
			perror("recv");
			tp_push(&pool, this_thr);

			if (pool.m_cursize > 0) {
				printf(_RED_CLR"[System]"_DEF_CLR" current pool:\n");
				for (int i = 0; i < pool.m_cursize; ++i)
					printf("  [%d]: 0x%x\n", i, (unsigned int) pool.m_threads[i]);
			}

			close(_sockfd);
			free(_sfd);
			pthread_kill(this_thr, SIGUSR1);
		}

		pthread_yield();
	}

	return NULL;
}

void killthr(void)
{
	printf(_BLUE_CLR"[Server]"_DEF_CLR" active clients: %d\n", --nclients);

	while (!tp_empty(&pool)) {
		pthread_t thr = tp_pop(&pool);
		printf(_RED_CLR"[System]"_DEF_CLR" thread destroyed: 0x%lx\n", thr);

		if (pool.m_cursize > 0) {
			printf(_RED_CLR"[System]"_DEF_CLR" current pool:\n");
			for (int i = 0; i < pool.m_cursize; ++i)
				printf("  [%d]: 0x%x\n", i, (unsigned int) pool.m_threads[i]);
		}

		pthread_exit(NULL);
	}
}

void
killproc(void)
{
	close(listenfd);
	close(sockfd);
	printf(_BLUE_CLR"[Server]"_DEF_CLR" quit.\n");
	exit(EXIT_SUCCESS);
}

void
msggen(char *msg)
{
	int start = (int)' ';
	int end = (int)'~';
	int i = 0;

	for (; i < MSGSIZ - 1; ++i)
		msg[i] = (char)(start + rand() % (end - start));

	msg[i] = '\0';
}
