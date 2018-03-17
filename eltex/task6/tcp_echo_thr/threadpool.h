#include "tcp_echo.h"

/* Pool is not threadsafe :P */

struct threadpool_t {
	int m_cursize;
	int m_curpos;
	pthread_t m_threads[MAX_THREADS];
};

inline void __attribute__ ((always_inline))
tp_init(struct threadpool_t *_pool)
{
	_pool->m_cursize = 0;
	_pool->m_curpos = 0;
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
