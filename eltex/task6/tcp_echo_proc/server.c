#include "tcp_echo.h"

static int sockfd, listenfd;
static int nclients;

int
main(int argc, char *argv[])
{
	int optval, rc, clnt_len, serv_len;
	struct hostent *clnt_host;
	struct sockaddr_in clnt_addr, serv_addr;

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

	rc = listen(listenfd, 5);
	if (rc < 0) {
		fprintf(stderr, _RED_CLR"[System] "_DEF_CLR);
		perror("listen");
		exit(EXIT_FAILURE);
	}

	signal(SIGCHLD, (__sighandler_t) killproc);

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

		switch (fork()) {
		case -1:
			fprintf(stderr, _RED_CLR"[System] "_DEF_CLR);
			perror("fork");
			exit(EXIT_FAILURE);
			break;
		case 0:
			server_routine();
			break;
		default:
			printf(_BLUE_CLR"[Server]"_DEF_CLR" active clients: %d\n", ++nclients);
			break;
		}
	}

	return 0;
}

void __attribute__ ((noreturn))
server_routine(void)
{
	int bytes;

	while (0x1) {
		char packet[MSGSIZ];

		msggen(packet);

		bytes = send(sockfd, packet, MSGSIZ, 0);
		if (bytes < 0) {
			fprintf(stderr, _RED_CLR"[System] "_DEF_CLR);
			perror("send");
			exit(EXIT_FAILURE);
		}

		bytes = recv(sockfd, packet, MSGSIZ, 0);
		if (bytes < 0) {
			fprintf(stderr, _RED_CLR"[System] "_DEF_CLR);
			perror("recv");
			exit(EXIT_FAILURE);
		}
	}
}

void
killproc(void)
{
	printf(_BLUE_CLR"[Server]"_DEF_CLR" active clients: %d\n", --nclients);

	if (!nclients) {
		int wstatus = 0;
		wait(&wstatus);
		close(listenfd);
		close(sockfd);
		printf(_BLUE_CLR"[Server]"_DEF_CLR" quit.\n");
		exit(EXIT_SUCCESS);
	}
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
