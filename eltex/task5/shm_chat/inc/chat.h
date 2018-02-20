#ifndef __SHM_CHAT__
#define __SHM_CHAT__

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <unistd.h>

int shmem_alloc(int n);
void *shmem_map(int id);

int sem_create(int n, unsigned short *vals);
void sem_free(int id);
void sem_lock(int id, int i);
void sem_unlock(int id, int i);

#endif

#if defined(__GNU_LIBRARY__) || defined(_SEM_SEMUN_UNDEFINED)

union semun {
	int val;
	struct semid_ds *buf;
	unsigned short *array;
	struct seminfo *__buf;
};

#endif
