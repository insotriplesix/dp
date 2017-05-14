#ifndef INIT_H
#define INIT_H

#include <panel.h>
#include <stdlib.h>

#define NPANELS 3
#define NWINS 3

void init_curses();
void init_colors();
void init_windows(WINDOW **win, int n, int h, int w);
void init_panels(PANEL **pan, WINDOW **win, int n);

WINDOW *create_window(int h, int w, int y, int x);

#endif
