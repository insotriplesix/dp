#include <panel.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define NPANELS 1
#define NWINS 1

void init_curses();
void init_colors();
void print_editor(int h, int w);
void print_windows(WINDOW **win, int n, int h, int w);

int main(int argc, char **argv)
{
	WINDOW *wins[NPANELS];
	PANEL *panels[NPANELS];
//	PANEL *top;

	int ch, i, j;

	// Init ncurses lib
	init_curses();

	// Init palette
	init_colors();

	// Get terminal size
	int width = getmaxx(stdscr);
	int height = getmaxy(stdscr);

	// Print editor structure
	print_editor(height, width);

	// Print edit window
	print_windows(wins, NWINS, height, width);

	panels[0] = new_panel(wins[0]);

//	set_panel_userptr(panels[0], panels[1]);
//	set_panel_userptr(panels[1], panels[0]);

	update_panels();
	doupdate();

//	top = panels[1];

	attron(COLOR_PAIR(1));

	// Default position of the cursor
	int curr_y = 4, curr_x = 2;

	// For the secret things
	int secret_y = height, secret_x = width, secret_d = 1;
	chtype secret_c;

	// Set this pos in the window
	move(curr_y, curr_x);

	// F8 - Quit program
	while ((ch = getch()) != KEY_F(8)) {
		switch (ch) {
			case KEY_ENTER:
				insch('\n');
//				insertln();
//				++curr_y, curr_x = 2;
//				move(curr_y, curr_x);
				break;
			case KEY_F(5):
				break;
			case KEY_F(6):
				break;
			case KEY_F(7):
				// Set secret attrs
				attron(COLOR_PAIR(4));

				// Make some NOISE
				for (i = 0; i < height; ++i) {
					for (j = 0; j < width; ++j) {
						if (secret_x < 0 || secret_x >= width)
							secret_d *= -1;

						secret_x += secret_d * 2;

						secret_c = 33 + rand() % 93;
						secret_c |= A_BLINK;
						mvaddch(secret_y, secret_x, secret_c);

						usleep(1337);

						refresh();
						doupdate();
					}

					--secret_y;
				}
		}

		refresh();
//		update_panels();
		doupdate();
	}

	for (i = 0; i < NPANELS; ++i) {
		del_panel(panels[i]);
		delwin(wins[i]);
	}

	endwin();

	return 0;
}

/* Init curses library */
void init_curses()
{
	initscr();
	cbreak();
//	noecho();
	keypad(stdscr, TRUE);
}

/* Init colors */
void init_colors()
{
	// Check colors
	if (!has_colors()) {
		endwin();
		printf("Colors are not supported.\n");
		exit(1);
	}

	// Init palette
	start_color();

	// Pair id, Foreground, Background
	init_pair(1, COLOR_WHITE, COLOR_BLUE);		// edit field
	init_pair(2, COLOR_BLACK, COLOR_YELLOW);	// bars
	init_pair(3, COLOR_YELLOW, COLOR_YELLOW);	// secret
	init_pair(4, COLOR_BLACK, COLOR_RED);		// something else
}

/* Display editor structure */
void print_editor(int h, int w)
{
	int i;

	// Set default attrs
	attron(COLOR_PAIR(0));

	// Left
	for (i = 2; i < h - 1; ++i)
		mvprintw(i, 1, "|");

	// Right
	for (i = 2; i < h - 1; ++i)
		mvprintw(i, w - 1, "|");

	// Top
	mvprintw(1, 1, "+");
	mvprintw(3, 1, "+");
	for (i = 2; i < w - 1; ++i) {
		mvprintw(1, i, "-");
		mvprintw(3, i, "-");
	}
	mvprintw(1, w - 1, "+");
	mvprintw(3, w - 1, "+");

	// Bottom
	mvprintw(h - 1, 1, "+");
	for (i = 2; i < w - 1; ++i)
		mvprintw(h - 1, i, "-");
	mvprintw(h - 1, w - 1, "+");

	// Set options attrs
	attron(COLOR_PAIR(2));

	mvprintw(2, 3, " F5 - Open ");
	mvprintw(2, 15, " F6 - Save ");
	mvprintw(2, 27, " F8 - Quit ");
	mvprintw(2, 39, "    - Secret key ");
	mvprintw(2, w - 20, " made by 5aboteur ");

	// Set secret attrs
	attron(COLOR_PAIR(3));

	mvprintw(2, 41, "F7");
}

/* Init windows */
void print_windows(WINDOW **win, int n, int h, int w)
{
	int x, y;

	// Initial position
	y = 4, x = 2;

	// Edit field
	win[0] = newwin(h - 5, w - 3, y, x);

	// Turn off previous atrributes and set bg color
	wbkgdset(win[0], COLOR_PAIR(1));

	// Clear position in the window
	wclear(win[0]);

	// Refresh it
	wrefresh(win[0]);

	// Bars fields
/*	for (i = 1; i < n; ++i) {
		win[i] = newwin(1, 10, y, x);
		wbkgdset(win[i], COLOR_PAIR(2));
		wclear(win[i]);
		wrefresh(win[i]);

		x += 12;
	}*/
}

