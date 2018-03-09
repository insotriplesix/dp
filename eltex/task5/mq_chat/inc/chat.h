#ifndef __MQ_CHAT__
#define __MQ_CHAT__

#include <assert.h>
#include <ctype.h>
#include <pthread.h>
#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <unistd.h>

#define BUFSIZE 1024

#define DEFPOS_X 1
#define DEFPOS_Y 1
#define NICKNAME_MAX 24
#define NWINDOWS 3

#if defined(__GNU_LIBRARY__) || defined(_SEM_SEMUN_UNDEFINED)

union semun {
	int val;
	struct semid_ds *buf;
	unsigned short *array;
	struct seminfo *__buf;
};

#endif

WINDOW *win[NWINDOWS];

enum usr_t { USR0, USR1, USR2 };
//enum sem_t { USR1_SEM, USR2_SEM };
enum win_t { LEFT_W, RITE_W, BOTM_W };

char current_theme;
int current_line_left;
int current_line_rite;
int id_sem, id_shm;
//int uid;
int usr1, usr2;
//char *chat_buf;

int qid;
key_t key;
pthread_t msg_recv_thr;

//int message_arrived;

struct user_t {
	int id;
	char nickname[NICKNAME_MAX];
};

struct user_t user;

struct msg_t {
	long type;
	char text[BUFSIZE];
//	int user_id;
//	char user_nickname[NICKNAME_MAX];
//	struct user_t *user;
};

int shmem_alloc(int n);
void *shmem_map(int id);

int sem_create(int n, unsigned short *vals);
void sem_free(int id);
void sem_lock(int id, int i);
void sem_unlock(int id, int i);

int open_queue(key_t key);
int send_message(int qid, struct msg_t *message);
int recv_message(int qid, long type, struct msg_t *message);
int remove_queue(int qid);

#endif
