#include <panel.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define NPANELS 3
#define NWINS 3

void init_curses();
void init_colors();
void init_windows(WINDOW **win, int n, int h, int w);
void init_panels(PANEL **pan, WINDOW **win, int n);

WINDOW *create_window(int h, int w, int y, int x);
void destroy_window(WINDOW *win);
void print_editor(int h, int w);

void move_left(WINDOW *w, int *y, int *x, int b);
void move_right(WINDOW *w, int *y, int *x, int b);
void move_up(WINDOW *w, int *y, int *x, int b);
void move_down(WINDOW *w, int *y, int *x, int b);

int main(int argc, char *argv[])
{
	static char *fbuf = NULL;
	static int fbuf_cnt = 0;

	// File pointer
	FILE *fp;

	WINDOW *windows[NWINS];
	PANEL *panels[NPANELS];

	int ch, i, j, width, height;

	// Init curses session
	init_curses();

	// Init palette
	init_colors();

	// Get the terminal size
	getmaxyx(stdscr, height, width);

	// Init default windows
	init_windows(windows, NWINS, height, width);

	// Attach panels to them
	init_panels(panels, windows, NPANELS);

	// Set default attributes
//	wattron(windows[0], COLOR_PAIR(1));
//	wattron(windows[1], COLOR_PAIR(2));
//	wattron(windows[2], COLOR_PAIR(2));

	// Update the stacking order
	update_panels();

	// Display the content
	doupdate();

	char filename[32];

	fbuf = (char *)malloc(BUFSIZ * sizeof(char));

	// Default position of the cursor
	int def_y = 1, def_x = 1;

	// Current position of the cursor
	int curr_y = def_y, curr_x = def_x;

	// For the secret things
	int secret_y = height - 10, secret_x = width, secret_d = 1;
	chtype secret_c;

	// Set this pos in the window
	wmove(windows[0], 1, 1);

	// Display the content
	wrefresh(windows[0]);

	// F8 - To quit that!
	while ((ch = getch()) != KEY_F(8)) {
		switch (ch) {
			case KEY_LEFT:	// left
				move_left(windows[0], &curr_y, &curr_x, 0);
				break;
			case KEY_RIGHT:	// right
				move_right(windows[0], &curr_y, &curr_x, width - 4);
				break;
			case KEY_UP:	// up
				move_up(windows[0], &curr_y, &curr_x, 0);
				break;
			case KEY_DOWN:	// down
				move_down(windows[0], &curr_y, &curr_x, height - 10);
				break;
			case KEY_DC:
			case 127:
			case KEY_BACKSPACE:	// remove
				move_left(windows[0], &curr_y, &curr_x, 0);
				waddch(windows[0], ' ');
				wmove(windows[0], curr_y, curr_x);

				if (fbuf_cnt && (curr_x > 1))
					fbuf[fbuf_cnt--] = ' ';
				break;
			case '\n':
			case KEY_ENTER:
				waddch(windows[0], '\n');
				curr_x = def_x;
				wmove(windows[0], ++curr_y, curr_x);
				fbuf[fbuf_cnt++] = '\n';
				break;
			case '\t':
				for (i = 0; i < 4; ++i) {
					move_right(windows[0], &curr_y, &curr_x, width - 4);
					waddch(windows[0], ' ');
					wmove(windows[0], curr_y, curr_x);
					fbuf[fbuf_cnt++] = ' ';
				}
				break;
			case KEY_F(5):	// Open
				mvwprintw(windows[2], 1, 1, "File you want to open: ");
				echo();
				wgetstr(windows[2], filename);
				noecho();

				// Try to open the file
				if ((fp = fopen(filename, "r"))) {

					// Go to the default position of the editor
					wmove(windows[0], def_y, def_x);

					// Read the file til we reach the end of it
					while ((ch = fgetc(fp)) != EOF)
						fbuf[fbuf_cnt++] = ch;

					// Insert the whole buffer into the editor field
					winsstr(windows[0], fbuf);

					fclose(fp);

				} else
					mvwprintw(windows[2], 2, 1, "Cannot open the file.");
				break;
			case KEY_F(6):	// Save
				printw("File you want to store the text: ");
				echo();
				getstr(filename);
				noecho();
				break;
			case KEY_F(7):
				// Set secret attrs
				wattron(windows[0], COLOR_PAIR(4) | A_REVERSE | A_BLINK);

				// Make some NOISE !!!!!!!
				for (i = 0; i < height; ++i) {
					for (j = 0; j < width; ++j) {
						if (secret_x < 0 || secret_x >= width)
							secret_d *= -1;

						secret_x += secret_d * 2;

						secret_c = 33 + rand() % 93;
						secret_c |= A_BLINK | A_REVERSE;
						mvwaddch(windows[0], secret_y, secret_x, secret_c);
						usleep(1337);

						wrefresh(windows[0]);
						doupdate();
					}

					--secret_y;
				}
				break;
			default:
				if (curr_x + 1 < width - 4) {
					waddch(windows[0], ch);
					move_right(windows[0], &curr_y, &curr_x, width);
				} else {
					++curr_y;
					curr_x = def_x - 1;
					waddch(windows[0], ch);
					move_right(windows[0], &curr_y, &curr_x, width);
				}
		}

		// Dump the changed content on the screen
		wrefresh(windows[0]);
//		update_panels();
//		doupdate();
	}

	// Deallocate memory for panels
	for (i = 0; i < NPANELS; ++i)
		del_panel(panels[i]);

	// Deallocate memory for windows
	for (i = 0; i < NWINS; ++i)
		delwin(windows[i]);

	// Set terminal in normal mode
	endwin();

	return 0;
}

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

/* Left arrow */
void move_left(WINDOW *w, int *y, int *x, int b)
{
	if (*x - 1 > b) wmove(w, *y, --(*x));
}

/* Right arrow */
void move_right(WINDOW *w, int *y, int *x, int b)
{
	if (*x + 1 < b) wmove(w, *y, ++(*x));
}

/* Up arrow */
void move_up(WINDOW *w, int *y, int *x, int b)
{
	if (*y - 1 > b) wmove(w, --(*y), *x);
}

/* Down arrow */
void move_down(WINDOW *w, int *y, int *x, int b)
{
	if (*y + 1 < b) wmove(w, ++(*y), *x);
}
