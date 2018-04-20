#include "chat.h"

int
shmem_alloc(int n)
{
	return shmget(IPC_PRIVATE, n, IPC_CREAT | SHM_R | SHM_W);
}

void *
shmem_map(int id)
{
	void *addr = shmat(id, NULL, 0);
	shmctl(id, IPC_RMID, NULL);
	return addr;
}

int
sem_create(int n, unsigned short *vals)
{
	int id = semget(IPC_PRIVATE, n, SHM_R | SHM_W);
	union semun arg;
	arg.array = vals;
	semctl(id, 0, SETALL, arg);
	return id;
}

void
sem_free(int id)
{
	if (semctl(id, 0, IPC_RMID, NULL) == -1) {
		perror("semctl");
		exit(EXIT_FAILURE);
	}
}

void
sem_lock(int id, int i)
{
	struct sembuf sb;
	sb.sem_num = i;
	sb.sem_op = -1;
	sb.sem_flg = SEM_UNDO;
	semop(id, &sb, 1);
}

void
sem_unlock(int id, int i)
{
	struct sembuf sb;
	sb.sem_num = i;
	sb.sem_op = 1;
	sb.sem_flg = SEM_UNDO;
	semop(id, &sb, 1);
}
