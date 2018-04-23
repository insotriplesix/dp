#include "udp_echo_server.h"

static int udp_sockfd;

int
main(void)
{
	int rc, serv_len, clnt_len;
	struct sockaddr_in serv_addr, clnt_addr;
	ssize_t bytes;

	serv_len = sizeof(serv_addr);
	clnt_len = sizeof(clnt_addr);

	port_serv = _DEF_PORT_SERV;
	printf(_RED_CLR"[System]"_DEF_CLR" using default port: %d\n",
		port_serv);

	udp_sockfd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	if (udp_sockfd < 0) {
		fprintf(stderr, _RED_CLR"[System] "_DEF_CLR);
		perror("udp socket");
		exit(EXIT_FAILURE);
	}

	memset((char *) &serv_addr, 0, serv_len);
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	serv_addr.sin_port = htons(port_serv);

	rc = bind(udp_sockfd, (struct sockaddr *) &serv_addr, serv_len);
	if (rc < 0) {
		fprintf(stderr, _RED_CLR"[System] "_DEF_CLR);
		perror("bind");
		exit(EXIT_FAILURE);
	}

	signal(SIGINT, (__sighandler_t) killproc);

	while (0x1) {
		char packet[PKTSIZ];

		bytes = recvfrom(udp_sockfd, packet, PKTSIZ, 0,
			(struct sockaddr *) &clnt_addr, (socklen_t *) &clnt_len);
		if (bytes < 0) {
			fprintf(stderr, _RED_CLR"[System] "_DEF_CLR);
			perror("recvfrom");
			exit(EXIT_FAILURE);
		}

		printf(_BLUE_CLR"[Server]"_DEF_CLR" got %zu (+ %zu) bytes, send them back\n",
			bytes, UDP_HDRSZ);

		bytes = sendto(udp_sockfd, packet, PKTSIZ, 0,
			(struct sockaddr *) &clnt_addr, clnt_len);
		if (bytes < 0) {
			fprintf(stderr, _RED_CLR"[System] "_DEF_CLR);
			perror("sendto");
			exit(EXIT_FAILURE);
		}
	}

	return 0;
}

void __attribute__ ((noreturn))
killproc(void)
{
	close(udp_sockfd);
	printf(_BLUE_CLR"[Server]"_DEF_CLR" quit\n");
	exit(EXIT_SUCCESS);
}
