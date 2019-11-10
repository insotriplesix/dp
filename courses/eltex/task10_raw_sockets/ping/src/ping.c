#include "icmp_ping.h"

/* Interface name */

#define CLI_ADDR "192.168.0.101"
#define SERV_ADDR "5.255.255.60"

static int icmp_sockfd;

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

	icmp_sockfd = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP);
	if (icmp_sockfd < 0) {
		fprintf(stderr, _RED_CLR"[System] "_DEF_CLR);
		perror("socket");
		exit(EXIT_FAILURE);
	}

	memset((char *) &serv_addr, 0, serv_len);
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = inet_addr(SERV_ADDR);
//	serv_addr.sin_port = htons(port_serv);

	int hdrincl = 1;

	// tell kernel not to generate ip header
	rc = setsockopt(icmp_sockfd, IPPROTO_IP, IP_HDRINCL, &hdrincl, sizeof(hdrincl));
	if (rc < 0) {
		fprintf(stderr, _RED_CLR"[System] "_DEF_CLR);
		perror("setsockopt");
		exit(EXIT_FAILURE);
	}

	signal(SIGINT, (__sighandler_t) killproc);
	srand((unsigned) time(NULL));

	printf(_MAGENTA_CLR"[ICMP Client]"_DEF_CLR" ping %s\n", SERV_ADDR);

	while (0x1) {
		char *send_pkt = calloc(PKTSIZ, sizeof(char));

		pktgen(send_pkt);

		bytes = sendto(icmp_sockfd, send_pkt, PKTSIZ, 0,
			(struct sockaddr *) &serv_addr, serv_len);
		if (bytes < 0) {
			fprintf(stderr, _RED_CLR"[System] "_DEF_CLR);
			perror("sendto");
			exit(EXIT_FAILURE);
		}

		printf(_GREEN_CLR" snd"_DEF_CLR" %zu bytes\n", bytes);

		char *recv_pkt = calloc(PKTSIZ, sizeof(char));

		bytes = recvfrom(icmp_sockfd, recv_pkt, PKTSIZ, 0, NULL, NULL);
		if (bytes < 0) {
			fprintf(stderr, _RED_CLR"[System] "_DEF_CLR);
			perror("recvfrom");
			exit(EXIT_FAILURE);
		}

		printf(_GREEN_CLR" rcv"_DEF_CLR" %zu bytes\n", bytes);

		free(send_pkt);
		free(recv_pkt);

		sleep(2);
	}

	return 0;
}

void __attribute__ ((noreturn))
killproc(void)
{
	close(icmp_sockfd);
	printf(_MAGENTA_CLR"[ICMP Client]"_DEF_CLR" quit\n");
	exit(EXIT_SUCCESS);
}

void
pktgen(char *pkt)
{
	int rc;

	/* IP header init */

	struct iphdr *iph = (struct iphdr *) pkt;

	iph->version = 4;
	iph->ihl = sizeof(struct iphdr) / sizeof(uint32_t);
	iph->tos = 0;
//	iph->tot_len = 0;
	iph->tot_len = htons(PKTSIZ);
	iph->id = htons(0x666);
	iph->frag_off = 0;
	iph->ttl = 0x40;
	iph->protocol = IPPROTO_ICMP;
//	iph->check = htons(0x0);
	iph->saddr = inet_addr(CLI_ADDR);
	iph->daddr = inet_addr(SERV_ADDR);
	iph->check = ipv4_checksum((uint16_t *) iph, IP_HDRSZ);

	/* ICMP header init */

	struct icmphdr *icmph = (struct icmphdr *) (pkt + IP_HDRSZ);

	icmph->type = ICMP_ECHO;
	icmph->code = 0;
//	icmph->checksum = htons(0x0);

	icmph->un.echo.id = 0;
	icmph->un.echo.sequence = 0;

	icmph->checksum = ipv4_checksum((uint16_t *) icmph, ICMP_HDRSZ);
}

// RFC 1071, Computing the Internet Checksum, September 1988
// https://tools.ietf.org/html/rfc1071
uint16_t
ipv4_checksum(uint16_t *addr, int count)
{
	long sum = 0;

	while (count > 1) {
		sum += *(addr++);
		count -= 2;
	}

	if (count > 0)
		sum += *addr;

	while (sum >> 16L)
		sum = (sum & 0xffff) + (sum >> 16L);

	sum = ~sum;

	return (uint16_t) sum;
}
