#ifndef INIT_H
#define INIT_H

#include "editor.h"

void init_curses();
void init_colors();
void init_windows(WINDOW **win, int n, int h, int w);

#endif
