#include "udp_echo_server.h"

static int udp_sockfd;

int
main(void)
{
	int serv_len;
	struct sockaddr_in serv_addr;
	ssize_t bytes;

	serv_len = sizeof(serv_addr);

	port_clnt = _DEF_PORT_CLNT;
	port_serv = _DEF_PORT_SERV;
	printf(_RED_CLR"[System]"_DEF_CLR" using default port: %d\n",
		port_clnt);

	udp_sockfd = socket(AF_INET, SOCK_RAW, IPPROTO_UDP);
	if (udp_sockfd < 0) {
		fprintf(stderr, _RED_CLR"[System] "_DEF_CLR);
		perror("socket");
		exit(EXIT_FAILURE);
	}

	memset((char *) &serv_addr, 0, serv_len);
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	serv_addr.sin_port = htons(port_serv);

	signal(SIGINT, (__sighandler_t) killproc);
	srand((unsigned) time(NULL));

	while (0x1) {
		char *send_pkt = calloc(PKTSIZ, sizeof(char));

		pktgen(send_pkt);

		bytes = sendto(udp_sockfd, send_pkt, PKTSIZ, 0,
			(struct sockaddr *) &serv_addr, serv_len);
		if (bytes < 0) {
			fprintf(stderr, _RED_CLR"[System] "_DEF_CLR);
			perror("sendto");
			exit(EXIT_FAILURE);
		}

		printf(_GREEN_CLR"[UDP Client]"_DEF_CLR" send: ");
		print_udphdr((struct udphdr *) (send_pkt));
		printf(_LMAGENTA_CLR"%s "_LBLUE_CLR"%d%d%d%d"_DEF_CLR
			" (%zu bytes)\n", send_pkt + UDP_HDRSZ,
			(int) send_pkt[UDP_HDRSZ + DATASIZ],
			(int) send_pkt[UDP_HDRSZ + DATASIZ + 1],
			(int) send_pkt[UDP_HDRSZ + DATASIZ + 2],
			(int) send_pkt[UDP_HDRSZ + DATASIZ + 3],
			bytes);

		char *recv_pkt = calloc(PKTSIZ, sizeof(char));

		// skip 1 recv from itself
		for (int i = 0; i < 2; ++i) {
			bytes = recvfrom(udp_sockfd, recv_pkt, PKTSIZ, 0, NULL, NULL);
			if (bytes < 0) {
				fprintf(stderr, _RED_CLR"[System] "_DEF_CLR);
				perror("recvfrom");
				exit(EXIT_FAILURE);
			}
		}

		printf(_GREEN_CLR"[UDP Client]"_DEF_CLR" recv: ");
		print_udphdr((struct udphdr *) (recv_pkt + IP_HDRSZ));
		printf(_LMAGENTA_CLR"%s "_LBLUE_CLR"%d%d%d%d"_DEF_CLR
			" (%zu bytes)\n", recv_pkt + HDRSIZ,
			(int) recv_pkt[HDRSIZ + DATASIZ],
			(int) recv_pkt[HDRSIZ + DATASIZ + 1],
			(int) recv_pkt[HDRSIZ + DATASIZ + 2],
			(int) recv_pkt[HDRSIZ + DATASIZ + 3],
			bytes);

		printf("    %s\n", strncmp(send_pkt + UDP_HDRSZ,
			recv_pkt + HDRSIZ, DATASIZ)
			? _RED_CLR"wrong"_DEF_CLR
			: _GREEN_CLR"correct"_DEF_CLR);

		free(send_pkt);
		free(recv_pkt);

		sleep(2);
	}

	return 0;
}

void __attribute__ ((noreturn))
killproc(void)
{
	close(udp_sockfd);
	printf(_GREEN_CLR"[UDP Client]"_DEF_CLR" quit\n");
	exit(EXIT_SUCCESS);
}

void
pktgen(char *pkt)
{
	/* UDP header init */

	struct udphdr *hdr = (struct udphdr *) pkt;

	hdr->uh_sport = htons(port_clnt);
	hdr->uh_dport = htons(port_serv);
	hdr->uh_ulen = htons(PKTSIZ - IP_HDRSZ);
	hdr->uh_sum = htons(0x0);

	/* Datagen */

	char data[DATASIZ];

	int start = (int)' ';
	int end = (int)'~';
	int i = 0;

	for (; i < DATASIZ - 1; ++i)
		data[i] = (char)(start + rand() % (end - start));

	data[i] = '\0';

//	memcpy(pkt, hdr, UDP_HDRSZ);
	memcpy(pkt + UDP_HDRSZ, data, DATASIZ);
	memset(pkt + UDP_HDRSZ + DATASIZ, 0, PADDING);
}
