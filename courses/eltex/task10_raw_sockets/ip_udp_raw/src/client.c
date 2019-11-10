#include "udp_echo_server.h"

#define SERV_ADDR "127.0.0.1"

static int udp_sockfd;

int
main(void)
{
	int serv_len, rc;
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
	serv_addr.sin_addr.s_addr = inet_addr(SERV_ADDR);
	serv_addr.sin_port = htons(port_serv);

	int hdrincl = 1;

	// tell kernel not to generate ip header
	rc = setsockopt(udp_sockfd, IPPROTO_IP, IP_HDRINCL, &hdrincl, sizeof(hdrincl));
	if (rc < 0) {
		fprintf(stderr, _RED_CLR"[System] "_DEF_CLR);
		perror("setsockopt");
		exit(EXIT_FAILURE);
	}

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
//		print_iphdr((struct iphdr *) send_pkt);
		print_udphdr((struct udphdr *) (send_pkt + IP_HDRSZ));
		printf(_LMAGENTA_CLR"%s "_LBLUE_CLR"%d%d%d%d"_DEF_CLR
			" (%zu bytes)\n", send_pkt + HDRSIZ,
			(int) send_pkt[HDRSIZ + DATASIZ],
			(int) send_pkt[HDRSIZ + DATASIZ + 1],
			(int) send_pkt[HDRSIZ + DATASIZ + 2],
			(int) send_pkt[HDRSIZ + DATASIZ + 3],
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
//		print_iphdr((struct iphdr *) recv_pkt);
		print_udphdr((struct udphdr *) (recv_pkt + IP_HDRSZ));
		printf(_LMAGENTA_CLR"%s "_LBLUE_CLR"%d%d%d%d"_DEF_CLR
			" (%zu bytes)\n", recv_pkt + HDRSIZ,
			(int) recv_pkt[HDRSIZ + DATASIZ],
			(int) recv_pkt[HDRSIZ + DATASIZ + 1],
			(int) recv_pkt[HDRSIZ + DATASIZ + 2],
			(int) recv_pkt[HDRSIZ + DATASIZ + 3],
			bytes);

		printf("    %s\n", strncmp(send_pkt + HDRSIZ,
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
	/* IP header init */

	struct iphdr *iph = (struct iphdr *) pkt;

	iph->version = 4;
	iph->ihl = sizeof(struct iphdr) / sizeof(uint32_t);
	iph->tos = 0;
	iph->tot_len = 0;
	iph->id = htons(0x666);
	iph->frag_off = 0;
	iph->ttl = 0x40;
	iph->protocol = IPPROTO_UDP;
	iph->check = htons(0x0);
	iph->saddr = htonl(INADDR_ANY);
	iph->daddr = inet_addr(SERV_ADDR);

	/* UDP header init */

	struct udphdr *udph = (struct udphdr *) (pkt + IP_HDRSZ);

	udph->uh_sport = htons(port_clnt);
	udph->uh_dport = htons(port_serv);
	udph->uh_ulen = htons(PKTSIZ - IP_HDRSZ);
	udph->uh_sum = htons(0x0);

	/* Datagen */

	char data[DATASIZ];

	int start = (int)' ';
	int end = (int)'~';
	int i = 0;

	for (; i < DATASIZ - 1; ++i)
		data[i] = (char)(start + rand() % (end - start));

	data[i] = '\0';

	memcpy(pkt + HDRSIZ, data, DATASIZ);
	memset(pkt + HDRSIZ + DATASIZ, 0, PADDING);
}
