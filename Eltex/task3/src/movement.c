#include "movement.h"

/* Left arrow */
void move_left(WINDOW *win, int *y, int *x, int b)
{
	if (*x - 1 > b) wmove(win, *y, --(*x));
}

/* Right arrow */
void move_right(WINDOW *win, int *y, int *x, int b)
{
	if (*x + 1 < b) wmove(win, *y, ++(*x));
}

/* Up arrow */
void move_up(WINDOW *win, int *y, int *x, int b)
{
	if (*y - 1 > b) wmove(win, --(*y), *x);
}

/* Down arrow */
void move_down(WINDOW *win, int *y, int *x, int b)
{
	if (*y + 1 < b) wmove(win, ++(*y), *x);
}
