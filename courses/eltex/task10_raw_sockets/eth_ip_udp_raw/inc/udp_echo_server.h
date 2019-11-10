#define _GNU_SOURCE
#ifndef __UDP_ECHO_SERVER_H__
#define __UDP_ECHO_SERVER_H__

#include <arpa/inet.h>
#include <ctype.h>
#include <linux/if.h>
#include <linux/if_ether.h>
#include <linux/if_packet.h>
#include <netdb.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <netinet/udp.h>
#include <pthread.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/epoll.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>
#include <unistd.h>

#define ETH_HDRSZ sizeof(struct ethhdr)
#define IP_HDRSZ sizeof(struct iphdr)
#define UDP_HDRSZ sizeof(struct udphdr)
#define HDRSIZ (ETH_HDRSZ + IP_HDRSZ + UDP_HDRSZ)
#define DATASIZ 64 - HDRSIZ
#define PKTSIZ (HDRSIZ + DATASIZ)
#define _DEF_PORT_CLNT 9696
#define _DEF_PORT_SERV 6969

#define _DEF_CLR "\033[0m"
#define _BLACK_CLR "\033[1;30m"
#define _RED_CLR "\033[1;31m"
#define _GREEN_CLR "\033[1;32m"
#define _YELLOW_CLR "\033[1;33m"
#define _BLUE_CLR "\033[1;34m"
#define _LBLUE_CLR "\033[0;34m"
#define _MAGENTA_CLR "\033[1;35m"
#define _LMAGENTA_CLR "\033[0;35m"
#define _CYAN_CLR "\033[1;36m"
#define _LCYAN_CLR "\033[0;36m"
#define _WHITE_CLR "\033[1;37m"

unsigned short port_clnt, port_serv;

void __attribute__ ((noreturn)) killproc(void);
void pktgen(char *pkt);
uint16_t ipv4_checksum(uint16_t *addr, int count);

inline void __attribute__ ((always_inline))
print_ethhdr(struct ethhdr *hdr)
{
    printf(_LCYAN_CLR"%.2X:%.2X:%.2X:%.2X:%.2X:%.2x,"
		"%.2X:%.2X:%.2X:%.2X:%.2X:%.2X,%d "_DEF_CLR,
		hdr->h_source[0], hdr->h_source[1], hdr->h_source[2],
		hdr->h_source[3], hdr->h_source[4], hdr->h_source[5],
		hdr->h_dest[0], hdr->h_dest[1], hdr->h_dest[2],
		hdr->h_dest[3], hdr->h_dest[4], hdr->h_dest[5],
		hdr->h_proto);
}

inline void __attribute__ ((always_inline))
print_iphdr(struct iphdr *hdr)
{
    printf(_LCYAN_CLR"%u,%u,%u,%hu,%hu,%hu,%u,%u,%hu,%u,%u "_DEF_CLR,
		hdr->ihl, hdr->version, hdr->tos, ntohs(hdr->tot_len),
		ntohs(hdr->id), ntohs(hdr->frag_off), hdr->ttl, hdr->protocol,
		ntohs(hdr->check), hdr->saddr, hdr->daddr);
}

inline void __attribute__ ((always_inline))
print_udphdr(struct udphdr *hdr)
{
    printf(_LCYAN_CLR"%hu,%hu,%hu,%hu "_DEF_CLR,
		ntohs(hdr->uh_sport), ntohs(hdr->uh_dport),
		ntohs(hdr->uh_ulen), ntohs(hdr->uh_sum));
}

#endif
