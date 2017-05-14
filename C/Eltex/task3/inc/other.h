#ifndef OTHER_H
#define OTHER_H

#include <panel.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void load_file(char *fname, char *buf, int *sz);
void save_file(char *fname, char *buf, int sz);

void secret_func(WINDOW *win, int h, int w);

#endif
