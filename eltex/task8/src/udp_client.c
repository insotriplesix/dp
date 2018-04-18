#include "tcp_udp_server.h"

static int sockfd;

int
main(int argc, char *argv[])
{
	int serv_len;
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
		sockfd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
		if (sockfd < 0) {
			fprintf(stderr, _RED_CLR"[System] "_DEF_CLR);
			perror("socket");
			exit(EXIT_FAILURE);
		}

		memset((char *) &serv_addr, 0, serv_len);
		serv_addr.sin_family = AF_INET;
		serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
		serv_addr.sin_port = htons(port);

		printf(_GREEN_CLR"[UDP Client]"_DEF_CLR" connected on port %d\n", port);

		int npkts = 5 + rand() % 10;
		char request[PKTSIZ];

//		itoa(npkts, request, 10);
		sprintf(request, "%d", npkts);

		printf(_GREEN_CLR"[UDP Client]"_DEF_CLR" requesting for %d packets..\n", npkts);

		bytes = sendto(sockfd, request, PKTSIZ, 0, (struct sockaddr *) &serv_addr, serv_len);
		if (bytes < 0) {
			fprintf(stderr, _RED_CLR"[System] "_DEF_CLR);
			perror("sendto");
			exit(EXIT_FAILURE);
		}

//		bytes = sendto(sockfd, request, PKTSIZ, 0, (struct sockaddr *) &serv_addr, serv_len);
//		if (bytes < 0) {
//			fprintf(stderr, _RED_CLR"[System] "_DEF_CLR);
//			perror("sendto");
//			exit(EXIT_FAILURE);
//		}

		for (int i = 0; i < npkts; ++i) {
			char packet[PKTSIZ];

			bytes = recvfrom(sockfd, packet, PKTSIZ, 0, NULL, NULL);
			if (bytes < 0) {
				fprintf(stderr, _RED_CLR"[System] "_DEF_CLR);
				perror("recvfrom");
				exit(EXIT_FAILURE);
			}

			printf(_GREEN_CLR"[UDP Client]"_DEF_CLR" received packet %2d: %s\n", i, packet);

			sleep(1);
		}

		close(sockfd);

		printf(_GREEN_CLR"[UDP Client]"_DEF_CLR" waiting..\n");
/*
			bytes = sendto(sockfd, "q", 1, 0, (struct sockaddr *) &serv_addr, serv_len);
			if (bytes < 0) {
				fprintf(stderr, _RED_CLR"[System] "_DEF_CLR);
				perror("sendto");
				exit(EXIT_FAILURE);
			}
*/
		int r = 13 + rand() % 7;

		sleep(r);
	}

	return 0;
}

void __attribute__ ((noreturn))
killproc(void)
{
	close(sockfd);
	printf(_GREEN_CLR"[UDP Client]"_DEF_CLR" quit.\n");
	exit(EXIT_SUCCESS);
}
