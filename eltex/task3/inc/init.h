#ifndef INIT_H
#define INIT_H

#include <panel.h>
#include <stdlib.h>
#include <string.h>

#define NWINS 4

void init_curses();
void init_colors();
void init_windows(WINDOW **win, int n, int h, int w);

#endif
