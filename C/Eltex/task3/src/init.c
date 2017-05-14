#include "init.h"

/* Init curses session */
void init_curses()
{
	// Initialize the terminal in curses mode
	initscr();

	// Clear the screen
	clear();

	// Disable line buffering
	raw();	// or cbreak() ?

	// Switch off echoing
	noecho();

	// Enable func keys, arrows etc.
	keypad(stdscr, TRUE);
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
/*
	// Check color changing support
	if (!can_change_color()) {
		endwin();
		printf("This terminal doesn't support color changing.\n");
	}
*/
	// Start color functionality
	start_color();

	// Pair id, Foreground, Background
	init_pair(1, COLOR_WHITE, COLOR_BLUE);		// edit field
	init_pair(2, COLOR_BLACK, COLOR_YELLOW);	// tab & aux
	init_pair(3, COLOR_YELLOW, COLOR_YELLOW);	// secret
	init_pair(4, COLOR_BLACK, COLOR_RED);		// something else
}

/* Init default windows */
void init_windows(WINDOW **win, int n, int h, int w)
{
	// Editor field
	win[0] = create_window(h - 9, w - 3, 4, 2);

	// Turn off previous atrributes and set bg color
	wbkgdset(win[0], COLOR_PAIR(0));	// mustbe 1

	// Options field
	win[1] = create_window(3, w - 3, 1, 2);

	// Set options attrs
	wattron(win[1], COLOR_PAIR(2));

	// Place the option buttons
	mvwprintw(win[1], 1, 3, " F5 - Open ");
	mvwprintw(win[1], 1, 15, " F6 - Save ");
	mvwprintw(win[1], 1, 27, " F8 - Quit ");
	mvwprintw(win[1], 1, 39, "    - Secret key ");
	mvwprintw(win[1], 1, w - 24, " made by 5aboteur ");

	// Set secret attrs
	wattron(win[1], COLOR_PAIR(3));

	mvwprintw(win[1], 1, 41, "F7");

	// Aux field
	win[2] = create_window(5, w - 3, h - 5, 2);
	wbkgdset(win[2], COLOR_PAIR(0));	// mustbe 2
}

/* Init panels */
void init_panels(PANEL **pan, WINDOW **win, int n)
{
	int i;

	// Attach panels
	for (i = 0; i < n; ++i)
		pan[i] = new_panel(win[i]);

	// Update the stacking order
	update_panels();

	// Display the content
	doupdate();
}

/* Create new window */
WINDOW *create_window(int h, int w, int y, int x)
{
	// Allocate memory
	WINDOW *win = newwin(h, w, y, x);

	// Draw a border around the window
	box(win, 0, 0);

	// Display the content
	wrefresh(win);

	return win;
}
