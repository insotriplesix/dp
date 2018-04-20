#define _GNU_SOURCE
#ifndef __UDP_ECHO_SERVER_H__
#define __UDP_ECHO_SERVER_H__

#include <arpa/inet.h>
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
#include <sys/socket.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>
#include <unistd.h>

#define IP_HDRSZ sizeof(struct ip)
#define UDP_HDRSZ sizeof(struct udphdr)
#define DATASIZ 32
#define PKTSIZ (IP_HDRSZ + UDP_HDRSZ + DATASIZ)
#define _DEF_PORT_CLNT 9696
#define _DEF_PORT_SERV 6969

#define _DEF_CLR "\033[0m"
#define _BLACK_CLR "\033[1;30m"
#define _RED_CLR "\033[1;31m"
#define _GREEN_CLR "\033[1;32m"
#define _YELLOW_CLR "\033[1;33m"
#define _BLUE_CLR "\033[1;34m"
#define _MAGENTA_CLR "\033[1;35m"
#define _CYAN_CLR "\033[1;36m"
#define _LCYAN_CLR "\033[0;36m"
#define _WHITE_CLR "\033[1;37m"

int port_clnt, port_serv;

void __attribute__ ((noreturn)) killproc(void);
void pktgen(char *pkt);

inline void __attribute__ ((always_inline))
print_udphdr(struct udphdr *hdr)
{
    printf(_LCYAN_CLR"%hu,%hu,%hu,%hu "_DEF_CLR,
        ntohs(hdr->uh_sport), ntohs(hdr->uh_dport),
		hdr->uh_ulen, hdr->uh_sum);
}

#endif
