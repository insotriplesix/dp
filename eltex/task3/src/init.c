#include "init.h"

/* Init curses session */
void init_curses()
{
	// Initialize the terminal in curses mode
	initscr();

	// Clear the screen
	clear();

	// Disable line buffering
	cbreak();	// or raw() ?

	// Switch off echoing
	noecho();
}

/* Init palette */
void init_colors()
{
	// Check colouring support
	if (!has_colors()) {
		endwin();
		printf("This terminal doesn't support colouring.\n");
		exit(1);
	}

	// Start color functionality
	start_color();

	// Pair id, Foreground, Background
	init_pair(1, COLOR_BLACK, COLOR_YELLOW);	// menu components
	init_pair(2, COLOR_WHITE, COLOR_BLUE);		// edit field
	init_pair(3, COLOR_YELLOW, COLOR_BLACK);	// reversed main
	init_pair(4, COLOR_WHITE, COLOR_BLACK);		// borders
}

/* Init default windows */
void init_windows(WINDOW **win, int n, int h, int w)
{
    char *fname = " untitled ";

    // 0 -- Menu bar
    win[0] = newpad(3, w);
    wbkgd(win[0], COLOR_PAIR(4));
    box(win[0], ACS_VLINE, ACS_HLINE);
    wmove(win[0], 1, 1);

    wattron(win[0], COLOR_PAIR(1));

    mvwprintw(win[0], 1, 2, "  F4 - Open  ");
    mvwprintw(win[0], 1, 17, "  F5 - Save  ");
    mvwprintw(win[0], 1, 32, "  F6 - Extra  ");
    mvwprintw(win[0], 1, 48, "  F7 - Help  ");
    mvwprintw(win[0], 1, 63, "  F8 - Exit  ");
    mvwprintw(win[0], 1, w - 20, " made by 5aboteur ");

    prefresh(win[0], 0, 0, 0, 0, 2, w);

    // 1 -- Editing area box
    win[1] = newpad(h - 6, w);
    wbkgd(win[1], COLOR_PAIR(4));
    box(win[1], ACS_VLINE, ACS_HLINE);
    mvwaddstr(win[1], 0, w / 2 - strlen(fname) / 2, fname);
    prefresh(win[1], 0, 0, 3, 0, h - 6, w);

    // 2 -- Editing area
    win[2] = newpad(h - 8, w - 2);
    wbkgd(win[2], COLOR_PAIR(2));
    prefresh(win[2], 0, 0, 4, 1, h - 7, w - 1);

	// Enable func keys, arrows etc.
	keypad(win[2], TRUE);

    // 3 -- Info bar
    win[3] = newpad(5, w);
    wbkgd(win[3], COLOR_PAIR(1));
    box(win[3], ACS_VLINE, ACS_HLINE);
    wattron(win[3], COLOR_PAIR(1));

    mvwprintw(win[3], 2, 4, "File: ..");
    mvwprintw(win[3], 2, 16, "Size: ..");
    mvwprintw(win[3], 2, 28, "Inode: ..");
    mvwprintw(win[3], 2, 41, "Something else: ..");
    mvwprintw(win[3], 2, w - 10, "v0.9b");
    wattron(win[3], COLOR_PAIR(4));
    box(win[3], 0, 0);
    mvwprintw(win[3], 0, w / 2 - 4, "%3d :%3d ", 0, 0);
    prefresh(win[3], 0, 0, h - 5, 0, h, w);
}


