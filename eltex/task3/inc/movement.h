#ifndef MOVEMENT_H
#define MOVEMENT_H

#include <panel.h>

void move_left(WINDOW *win, int *y, int *x, int b);
void move_right(WINDOW *win, int *y, int *x, int b);
void move_up(WINDOW *win, int *y, int *x, int b);
void move_down(WINDOW *win, int *y, int *x, int b);

#endif
