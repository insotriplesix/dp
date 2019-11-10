#include "multicaster.h"

static int udp_sockfd;

int
main(int argc, char *argv[])
{
	int reuse = 1, rc, multicast_len;
	struct sockaddr_in multicast_addr;
	ssize_t bytes;

	multicast_len = sizeof(multicast_addr);

	if (argc < 2) {
		port = _DEF_PORT;
		printf(_RED_CLR"[System]"_DEF_CLR" using default port: %d\n", port);
	} else
		port = atoi(argv[1]);

	udp_sockfd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	if (udp_sockfd < 0) {
		fprintf(stderr, _RED_CLR"[System] "_DEF_CLR);
		perror("udp socket");
		exit(EXIT_FAILURE);
	}

	memset((char *) &multicast_addr, 0, multicast_len);
	multicast_addr.sin_family = AF_INET;
	multicast_addr.sin_addr.s_addr = inet_addr(_MULTICAST_ADDR);
	multicast_addr.sin_port = htons(port);

	rc = setsockopt(udp_sockfd, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(reuse));
	if (rc < 0) {
		fprintf(stderr, _RED_CLR"[System] "_DEF_CLR);
		perror("setsockopt");
		exit(EXIT_FAILURE);
	}

	printf(_BLUE_CLR"[Server]"_DEF_CLR" port: %d\n", ntohs(multicast_addr.sin_port));

	signal(SIGINT, (__sighandler_t) killproc);

	while (0x1) {
		char packet[PKTSIZ];

		sprintf(packet, _CYAN_CLR"{MULTICAST}"_DEF_CLR" test\n");

		// send a packet to the group
		bytes = sendto(udp_sockfd, packet, PKTSIZ, 0, (struct sockaddr *) &multicast_addr,
			multicast_len);
		if (bytes < 0) {
			fprintf(stderr, _RED_CLR"[System] "_DEF_CLR);
			perror("sendto");
			exit(EXIT_FAILURE);
		}

		sleep(2);
	}

	return 0;
}

void __attribute__ ((noreturn))
killproc(void)
{
	close(udp_sockfd);
	printf(_BLUE_CLR"[Server]"_DEF_CLR" quit.\n");
	exit(EXIT_SUCCESS);
}
