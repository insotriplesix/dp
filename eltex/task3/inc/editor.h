#ifndef EDITOR_H
#define EDITOR_H

#include <ncurses.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define FNAME_MAX_SIZE 128
#define NWINS 4

#define KEY_NL '\n'
#define KEY_TAB '\t'

#define CTRL_E 5
#define CTRL_G 7
#define CTRL_H 8
#define CTRL_K 11
#define CTRL_O 15
#define CTRL_X 24
#define CTRL_Y 25

extern char filename[FNAME_MAX_SIZE];

#endif
