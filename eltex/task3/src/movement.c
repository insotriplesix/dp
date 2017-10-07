#include "movement.h"

/* Cursor movement */

void move_left(WINDOW *win, int *y, int *x, int b)
{
	if (*x - 1 > b) wmove(win, *y, --(*x));
}

void move_right(WINDOW *win, int *y, int *x, int b)
{
	if (*x + 1 < b) wmove(win, *y, ++(*x));
}

void move_up(WINDOW *win, int *y, int *x, int b)
{
	if (*y - 1 > b) wmove(win, --(*y), *x);
}

void move_down(WINDOW *win, int *y, int *x, int b)
{
	if (*y + 1 < b) wmove(win, ++(*y), *x);
}
