#include "broadcaster.h"

static int udp_sockfd;

int
main(int argc, char *argv[])
{
	int rc, reuse = 1, serv_len;
	struct sockaddr_in serv_addr;
	ssize_t bytes;

	serv_len = sizeof(serv_addr);

	if (argc < 2) {
		port = _DEF_PORT;
		printf(_RED_CLR"[System]"_DEF_CLR" using default port: %d\n", port);
	} else
		port = atoi(argv[1]);

	udp_sockfd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	if (udp_sockfd < 0) {
		fprintf(stderr, _RED_CLR"[System] "_DEF_CLR);
		perror("socket");
		exit(EXIT_FAILURE);
	}

	memset((char *) &serv_addr, 0, serv_len);
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	serv_addr.sin_port = htons(port);

	rc = setsockopt(udp_sockfd, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(reuse));
	if (rc < 0) {
		fprintf(stderr, _RED_CLR"[System] "_DEF_CLR);
		perror("setsockopt");
		exit(EXIT_FAILURE);
	}

	rc = bind(udp_sockfd, (struct sockaddr *) &serv_addr, serv_len);
	if (rc < 0) {
		fprintf(stderr, _RED_CLR"[System] "_DEF_CLR);
		perror("bind");
		exit(EXIT_FAILURE);
	}

	signal(SIGINT, (__sighandler_t) killproc);

	printf(_GREEN_CLR"[UDP Client]"_DEF_CLR" connected!\n");
/*
	bytes = sendto(udp_sockfd, "h", 1, 0, (struct sockaddr *) &serv_addr, serv_len);
	if (bytes < 0) {
		fprintf(stderr, _RED_CLR"[System] "_DEF_CLR);
		perror("sendto");
		exit(EXIT_FAILURE);
	}
*/
	while (0x1) {
		char packet[PKTSIZ];

		bytes = recvfrom(udp_sockfd, packet, PKTSIZ, 0, NULL, NULL);
		if (bytes < 0) {
			fprintf(stderr, _RED_CLR"[System] "_DEF_CLR);
			perror("recvfrom");
			exit(EXIT_FAILURE);
		}

		printf("%s", packet);
	}

	return 0;
}

void __attribute__ ((noreturn))
killproc(void)
{
	close(udp_sockfd);
	printf(_GREEN_CLR"[UDP Client]"_DEF_CLR" quit.\n");
	exit(EXIT_SUCCESS);
}
