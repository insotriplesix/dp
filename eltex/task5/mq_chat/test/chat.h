#ifndef __MQ_CHAT__
#define __MQ_CHAT__

#include <ctype.h>
#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <unistd.h>

#define DEFPOS_X 1
#define DEFPOS_Y 1
#define NICKNAME_MAX 24
#define NWINDOWS 3

WINDOW *win[NWINDOWS];

enum win_t { LEFT_W, RITE_W, BOTM_W };

char current_theme;
int current_line_left;
int current_line_rite;
//char *chat_buf;

int qid;
key_t key;

struct msg {
	long type;
	char text[BUFSIZ];
};

struct user_t {
	int id;
	char nickname[NICKNAME_MAX];
};

struct user_t user;

inline int __attribute__ ((always_inline))
open_queue(key_t key)
{
    return msgget(key, IPC_CREAT | 0666);
}

inline int __attribute__ ((always_inline))
send_message(int qid, struct msg *message)
{
    return msgsnd(qid, message, BUFSIZ, 0);
}

inline int __attribute__ ((always_inline))
recv_message(int qid, long type, struct msg *message)
{
    return msgrcv(qid, message, BUFSIZ, type, 0);
}

inline int __attribute__ ((always_inline))
remove_queue(int qid)
{
    return msgctl(qid, IPC_RMID, 0);
}


#endif
