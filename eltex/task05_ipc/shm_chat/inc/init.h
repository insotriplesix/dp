#ifndef __INIT_H__
#define __INIT_H__

#include "chat.h"

void initialize(int argc, char *argv[]);
void finalize(void);

int init_colors(void);
int init_content(void);
int init_gui(void);
int init_ncurses(void);
int init_windows(void);

int init_user(int argc, char *argv[]);

#endif
