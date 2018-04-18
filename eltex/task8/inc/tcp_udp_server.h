#define _GNU_SOURCE
#ifndef __TCP_UDP_SERVER_H__
#define __TCP_UDP_SERVER_H__

#include <arpa/inet.h>
#include <netdb.h>
#include <netinet/in.h>
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

#define PKTSIZ 64
#define POOLSIZ 3

#define _DEF_PORT 6666

#define _DEF_CLR "\033[0m"
#define _BLACK_CLR "\033[1;30m"
#define _RED_CLR "\033[1;31m"
#define _GREEN_CLR "\033[1;32m"
#define _YELLOW_CLR "\033[1;33m"
#define _BLUE_CLR "\033[1;34m"
#define _MAGENTA_CLR "\033[1;35m"
#define _CYAN_CLR "\033[1;36m"
#define _WHITE_CLR "\033[1;37m"

pthread_mutex_t pool_lock = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t pool_cond = PTHREAD_COND_INITIALIZER;

enum state_t {
	INIT,
	IDLE,
	RESPONSE,
	ERROR
};

typedef void *(*CALLBACK)(int);

struct worker_t {
	short m_id;
	int m_busy;
	int m_val;	// sockfd for TCP, npkts for UDP
	pthread_t m_thread;

	CALLBACK m_job;
};

int port;
int server_state;

void init(int argc, char *argv[]);
void idle(int *nfds, struct epoll_event *efds);
void response(int nfds, struct epoll_event *efds);
void choose_worker(int sock);

void *tcp_routine(int _sfd);
void *udp_routine(int _sfd);
int is_active_udp_client(unsigned short client);
char *current_time(void);
void killthr(void);
void __attribute__ ((noreturn)) killproc(void);
void tcp_pkt_gen(char *pkt);
void udp_pkt_gen(char *pkt);

#endif
