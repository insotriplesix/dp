#include "threadpool.h"

void
tp_init(void)
{
	int rc;

	pool.m_size = POOLSIZ;
	pthread_mutex_init(&pool.m_lock, NULL);
	pthread_cond_init(&pool.m_cond, NULL);

	for (int i = 0; i < POOLSIZ; ++i) {
		pool.m_worker[i].m_id = i + 1;
		pool.m_worker[i].m_busy = 0;
		pool.m_worker[i].m_val = 0;
		pool.m_worker[i].m_job = NULL;

		rc = pthread_create(&pool.m_worker[i].m_thread, NULL, &tp_wait, NULL);
		if (rc != 0) {
			fprintf(stderr, _RED_CLR"[System] "_DEF_CLR);
			perror("tp pthread_create");
			exit(EXIT_FAILURE);
		}
	}
}

void *
tp_wait(void *unused)
{
	while (0x1) {
		pthread_cond_wait(&pool.m_cond, &pool.m_lock);
		pthread_t thr = pthread_self();

		// !!!!!!! use map to get rid of for loop
		// & move this to tp_action func
		for (int i = 0; i < POOLSIZ; ++i) {
			if (pool.m_worker[i].m_thread == thr) {
				if (pool.m_worker[i].m_busy) {
					int val = pool.m_worker[i].m_val;
					pool.m_worker[i].m_job(val);
					pool.m_worker[i].m_busy = 0;
				} else
					break;
			}
		}
	}

	return unused; // NULL
}
