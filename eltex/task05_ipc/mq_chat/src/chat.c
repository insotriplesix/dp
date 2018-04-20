#include "chat.h"

int
open_queue(key_t key)
{
	return msgget(key, IPC_CREAT | 0666);
}

int
send_message(int qid, struct msg_t *message)
{
	return msgsnd(qid, message, BUFSIZE, 0);
}

int
recv_message(int qid, long type, struct msg_t *message)
{
	return msgrcv(qid, message, BUFSIZE, type, IPC_NOWAIT);
}

int
remove_queue(int qid)
{
	return msgctl(qid, IPC_RMID, 0);
}
