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
#include <unistd.h>

#define BUFSIZE 1024

#define DEFPOS_X 1
#define DEFPOS_Y 1
#define NICKNAME_MAX 24
#define NWINDOWS 3

WINDOW *win[NWINDOWS];

enum usr_t { USR0, USR1, USR2 };
enum win_t { LEFT_W, RITE_W, BOTM_W };

char current_theme;
int current_line_left;
int current_line_rite;
int id_sem, id_shm;
int usr1, usr2;

int qid;
key_t key;
pthread_t msg_recv_thr;

struct user_t {
	int id;
	char nickname[NICKNAME_MAX];
};

struct user_t user;

struct msg_t {
	long type;
	char text[BUFSIZE];
};

int open_queue(key_t key);
int send_message(int qid, struct msg_t *message);
int recv_message(int qid, long type, struct msg_t *message);
int remove_queue(int qid);

#endif
