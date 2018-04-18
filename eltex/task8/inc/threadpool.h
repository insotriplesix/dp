#ifndef __THREADPOOL_H__
#define __THREADPOOL_H__

#include "tcp_udp_server.h"
/*
enum tp_state_t {
	INIT,
	WAIT,
	ACTION,
	ERROR
};

int tp_state;
*/
/* Pool is not threadsafe :P */

struct threadpool_t {
	int m_size;
	struct worker_t m_worker[POOLSIZ];
};

struct threadpool_t pool;

/*
void
tp_main()
{
	tp_state = INIT;

	while (0x1) {
		switch (tp_state) {
			case WAIT:
				tp_wait();
				tp_state = ACTION;
				break;
			case ACTION:
				tp_action();
				tp_state = WAIT;
				break;
			case INIT:
				tp_init();
				tp_state = WAIT;
				break;
			case ERROR:
//				error_handler();
				tp_state = WAIT;
				break;
			default:
				fprintf(stderr, "eror\n");
				perror("unknown error");
				exit(EXIT_FAILURE);
		}
	}
}
*/

void *
tp_wait(void *arg/*poolptr*/)
{
//	struct threadpool_t *pool = (struct threadpool_t *) poolptr;

	while (0x1) {
		pthread_cond_wait(&pool_cond, &pool_lock);
		pthread_t thr = pthread_self();
//		printf("0x%lx WOKE UP!\n", thr);
		for (int i = 0; i < POOLSIZ; ++i) {
			if (pool.m_worker[i].m_thread == thr) {
				if (pool.m_worker[i].m_busy) {
					int val = pool.m_worker[i].m_val;
					pool.m_worker[i].m_job(val);
					pool.m_worker[i].m_busy = 0;
				} else
					break;
			}
//				} else
//					printf("0x%lx is free\n", thr);
//			} else
//				printf("0x%lx not in threadpool\n", thr);
		}
	}

	return arg;
}

void
tp_init(/*struct threadpool_t *pool*/)
{
	int rc;

	pool.m_size = POOLSIZ;

	for (int i = 0; i < POOLSIZ; ++i) {
		pool.m_worker[i].m_id = i + 1;
		pool.m_worker[i].m_busy = 0;
		pool.m_worker[i].m_val = 0;
		pool.m_worker[i].m_job = NULL;

		rc = pthread_create(&pool.m_worker[i].m_thread, NULL, &tp_wait, NULL);
		if (rc != 0) {
			fprintf(stderr, _RED_CLR"[System] "_DEF_CLR);
			perror("pthread_create");
			exit(EXIT_FAILURE);
		}
	}
}

/*
void
tp_action()
{

}


inline int __attribute__ ((always_inline))
tp_empty(struct threadpool_t *_pool)
{
	return _pool->m_cursize > 0 ? 0 : 1;
}

inline void __attribute__ ((always_inline))
tp_push(struct threadpool_t *_pool, pthread_t _thr)
{
	if (_pool->m_cursize == MAX_THREADS)
		return;
	_pool->m_threads[_pool->m_curpos++] = _thr;
	_pool->m_cursize++;
}

inline void __attribute__ ((always_inline))
tp_shift(struct threadpool_t *_pool)
{
	for (int i = 0; i < _pool->m_cursize - 1; ++i)
		_pool->m_threads[i] = _pool->m_threads[i + 1];
	_pool->m_curpos--;
	_pool->m_cursize--;
}

inline pthread_t __attribute__ ((always_inline))
tp_pop(struct threadpool_t *_pool)
{
	pthread_t thr = _pool->m_threads[0];
	tp_shift(_pool);
	return thr;
}
*/
#endif
