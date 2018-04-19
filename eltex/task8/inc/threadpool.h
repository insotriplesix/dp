#ifndef __THREADPOOL_H__
#define __THREADPOOL_H__

#include "tcp_udp_server.h"

#define POOLSIZ 3

typedef void *(*CALLBACK)(int);

struct worker_t {
	short m_id;
	short m_busy;
	int m_val;	// sockfd for TCP, npkts for UDP
	pthread_t m_thread;

	CALLBACK m_job;
};

struct threadpool_t {
	int m_size;
	pthread_mutex_t m_lock;
	pthread_cond_t m_cond;
	struct worker_t m_worker[POOLSIZ];
};

struct threadpool_t pool;

void *tp_wait(void *unused);
void tp_init(void);

#endif
