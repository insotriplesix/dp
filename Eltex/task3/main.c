#include "init.h"
#include "movement.h"
#include "other.h"

int main(int argc, char *argv[])
{
	static char *fbuf = NULL;
	static int fbuf_cnt = 0;

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
			case KEY_F(5):	// load
				mvwprintw(windows[2], 1, 1, "File you want to open: ");
				echo();
				wgetstr(windows[2], filename);
				noecho();

				// Load the file
				load_file(filename, fbuf, &fbuf_cnt);

				// Insert the whole buffer into the editor field
				mvwinsstr(windows[0], def_y, def_x, fbuf);
				break;
			case KEY_F(6):	// Save
				mvwprintw(windows[2], 1, 1, "File you want to store the text: ");
				echo();
				wgetstr(windows[2], filename);
				noecho();

				// Save to the file
				save_file(filename, fbuf, fbuf_cnt);
				break;
			case KEY_F(7):
				// Set secret attrs
				wattron(windows[0], COLOR_PAIR(4) | A_REVERSE | A_BLINK);

				// ?
				secret_func(windows[0], height, width);
				break;
			default:
				// Add input symbol to the buffer
				fbuf[fbuf_cnt++] = (char)ch;

				// Display it on the edit field
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
	}

	// Deallocate memory for panels
	for (i = 0; i < NPANELS; ++i)
		del_panel(panels[i]);

	// Deallocate memory for windows
	for (j = 0; j < NWINS; ++j)
		delwin(windows[j]);

	// Free text buffer
	free(fbuf);

	// Set terminal in normal mode
	endwin();

	return 0;
}
