#ifndef __SHM_CHAT__
#define __SHM_CHAT__

#include <assert.h>
#include <ctype.h>
#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <unistd.h>

#include "list.h"

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

enum sem_t { USR1_SEM, USR2_SEM };
enum win_t { LEFT_W, RITE_W, BOTM_W };

char current_theme;
int current_line_left;
int current_line_rite;
int id_sem, id_shm;
int usr1_sem, usr2_sem;
char *chat_buf;

struct user_t {
	int id;
	char nickname[NICKNAME_MAX];
};

struct user_t user;

//struct list_t users;

int shmem_alloc(int n);
void *shmem_map(int id);

int sem_create(int n, unsigned short *vals);
void sem_free(int id);
void sem_lock(int id, int i);
void sem_unlock(int id, int i);

#endif
