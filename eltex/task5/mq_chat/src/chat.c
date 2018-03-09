#include "chat.h"
/*
void *
msg_recv_func(void *arg)
{
	while (0x1) {
		if ((recv_message(qid, 1, &msg_recv)) == ERR) {
			// memset whole message to zero maybe ?
		}

		message_arrived = TRUE;
	}

	return arg;
}
*/
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

int
open_queue(key_t key)
{
	return msgget(key, IPC_CREAT | 0666);
}

int
send_message(int qid, struct msg_t *message)
{
//	size_t sz = BUFSIZ + NICKNAME_MAX;
	size_t sz = BUFSIZE;
	return msgsnd(qid, message, sz, 0);
}

int
recv_message(int qid, long type, struct msg_t *message)
{
//	size_t sz = BUFSIZE + NICKNAME_MAX;
	size_t sz = BUFSIZE;
	return msgrcv(qid, message, sz, type, IPC_NOWAIT);
}

int
remove_queue(int qid)
{
	return msgctl(qid, IPC_RMID, 0);
}
