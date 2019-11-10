#include "tcp_udp_server.h"

static int sockfd;

int
main(int argc, char *argv[])
{
	int rc, serv_len, connected;
	struct sockaddr_in serv_addr;
	ssize_t bytes;

	serv_len = sizeof(serv_addr);

	if (argc < 2) {
		port = _DEF_PORT;
		printf(_RED_CLR"[System]"_DEF_CLR" using default port\n");
	} else
		port = atoi(argv[1]);

	signal(SIGINT, (__sighandler_t) killproc);
	srand((unsigned) time(NULL));

	while (0x1) {
		sockfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
		if (sockfd < 0) {
			fprintf(stderr, _RED_CLR"[System] "_DEF_CLR);
			perror("socket");
			exit(EXIT_FAILURE);
		}

		memset((char *) &serv_addr, 0, serv_len);
		serv_addr.sin_family = AF_INET;
		serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
		serv_addr.sin_port = htons(port);

		connected = 0;

		do {
			rc = connect(sockfd, (struct sockaddr *) &serv_addr, serv_len);
			if (rc >= 0)
				connected = 1;
			else {
				printf(_YELLOW_CLR"[TCP Client]"_DEF_CLR" connection refused...\n");
				sleep(1);
			}
		} while (!connected);

		char packet[PKTSIZ];

		bytes = recv(sockfd, packet, PKTSIZ, 0);
		if (bytes < 0) {
			fprintf(stderr, _RED_CLR"[System] "_DEF_CLR);
			perror("recv");
			exit(EXIT_FAILURE);
		}

		if (strncmp(packet, "TCP", 3) != 0) {
			printf("%s", packet);
			close(sockfd);
			sleep(1);
			continue;
		}

		printf(_YELLOW_CLR"[TCP Client]"_DEF_CLR" connected on port %d\n", port);
		printf(_YELLOW_CLR"[TCP Client]"_DEF_CLR" check message: %s\n", packet);

		char request[PKTSIZ] = "current_time";

		printf(_YELLOW_CLR"[TCP Client]"_DEF_CLR" requesting for time..\n");

		bytes = send(sockfd, request, PKTSIZ, 0);
		if (bytes < 0) {
			fprintf(stderr, _RED_CLR"[System] "_DEF_CLR);
			perror("send");
			exit(EXIT_FAILURE);
		}

		bytes = recv(sockfd, packet, PKTSIZ, 0);
		if (bytes < 0) {
			fprintf(stderr, _RED_CLR"[System] "_DEF_CLR);
			perror("recv");
			exit(EXIT_FAILURE);
		}

		printf(_YELLOW_CLR"[TCP Client]"_DEF_CLR" server time: %s", packet);

		close(sockfd);

		int timeout = 3 + rand() % 5;

		printf(_YELLOW_CLR"[TCP Client]"_DEF_CLR" waiting for %ds..\n", timeout);

		sleep(timeout);
	}

	return 0;
}

void __attribute__ ((noreturn))
killproc(void)
{
	close(sockfd);
	printf(_YELLOW_CLR"[TCP Client]"_DEF_CLR" disconnected\n");
	printf(_YELLOW_CLR"[TCP Client]"_DEF_CLR" quit\n");
	exit(EXIT_SUCCESS);
}
