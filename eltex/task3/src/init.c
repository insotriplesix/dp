#include "init.h"

char filename[FNAME_MAX_SIZE];

void init_curses()
{
	initscr();
	clear();
	cbreak();	// or raw() ?
	noecho();
}

void init_colors()
{
	if (!has_colors()) {
		endwin();
		printf("This terminal doesn't support colouring.\n");
		exit(1);
	}

	start_color();

	// Pair id, Foreground, Background
	init_pair(1, COLOR_BLACK, COLOR_YELLOW);	// menu components
	init_pair(2, COLOR_WHITE, COLOR_BLUE);		// edit field
	init_pair(3, COLOR_YELLOW, COLOR_BLACK);	// pop-ups
	init_pair(4, COLOR_WHITE, COLOR_BLACK);		// borders
}

/* Init default windows */
void init_windows(WINDOW **win, int n, int h, int w)
{
	// 0 -- Menu bar
	win[0] = newpad(3, w);
	wbkgd(win[0], COLOR_PAIR(4));
	box(win[0], ACS_VLINE, ACS_HLINE);

	wattron(win[0], COLOR_PAIR(1));

	int offset = 2;

	mvwprintw(win[0], 1, offset, "  F4 - Open  ");
	offset += 15;
	mvwprintw(win[0], 1, offset, "  F5 - Save  ");
	offset += 15;
	mvwprintw(win[0], 1, offset, "  F6 - Extra  ");
	offset += 16;
	mvwprintw(win[0], 1, offset, "  F7 - Help  ");
	offset += 15;
	mvwprintw(win[0], 1, offset, "  F8 - Exit  ");
	mvwprintw(win[0], 1, w - 20, " made by 5aboteur ");

	prefresh(win[0], 0, 0, 0, 0, 2, w);

	strcpy(filename, "untitled");

	// 1 -- Editing area box
	win[1] = newpad(h - 6, w);
	wbkgd(win[1], COLOR_PAIR(4));
	box(win[1], ACS_VLINE, ACS_HLINE);
	mvwaddstr(win[1], 0, w / 2 - strlen(filename) / 2, filename);
	prefresh(win[1], 0, 0, 3, 0, h - 6, w);

	// 2 -- Editing area
	win[2] = newpad(h - 7, w - 2);
	wbkgd(win[2], COLOR_PAIR(2));
	prefresh(win[2], 0, 0, 4, 1, h - 7, w - 2);

	// 3 -- Info bar
	win[3] = newpad(5, w);
	wbkgd(win[3], COLOR_PAIR(1));
	box(win[3], ACS_VLINE, ACS_HLINE);
	wattron(win[3], COLOR_PAIR(1));

	offset = 4;

	mvwprintw(win[3], 2, offset, "FILE: %s", filename);
	offset += 10 + strlen(filename);
	mvwprintw(win[3], 2, offset, "SIZE: %3d b", 0);
	offset += 15;
	mvwprintw(win[3], 2, offset, "TYPE: %c", 'r');
	offset += 11;
	mvwprintw(win[3], 2, offset, "ENCRYPT: %c", 'n');
	offset += 14;
	mvwprintw(win[3], 2, offset, "STATUS: %c", 'n');
	mvwprintw(win[3], 2, w - 10, "v0.9b");

	wattron(win[3], COLOR_PAIR(4));
	box(win[3], 0, 0);

	mvwprintw(win[3], 0, w / 2 - 4, " %3d : %3d ", 0, 0);

	prefresh(win[3], 0, 0, h - 5, 0, h, w);

	// Enable func keys, arrows etc.
	keypad(win[2], TRUE);
	wmove(win[2], 0, 0);
	prefresh(win[2], 0, 0, 4, 1, h - 7, w - 1);
}


