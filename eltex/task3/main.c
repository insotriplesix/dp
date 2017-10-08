#include "init.h"
#include "movement.h"
#include "other.h"

int main(int argc, char *argv[])
{
	static char *filebuf = NULL;
	static int filebuf_len = 0;

	WINDOW *windows[NWINS];

	int ch, i, width, height;

	init_curses();
	init_colors();

	// Get the terminal size
	getmaxyx(stdscr, height, width);

	init_windows(windows, NWINS, height, width);

	filebuf = (char *) malloc(BUFSIZ * sizeof(char));

	int default_pos_y = 0, default_pos_x = 0;
	int current_pos_y = default_pos_y,
		 current_pos_x = default_pos_x;

	int is_exit = FALSE;
	int encryption = FALSE;

	ch = wgetch(windows[2]);	// <~~ enable this and magic '~Z' disappear

	do {
		ch = wgetch(windows[2]);

		switch (ch) {
			case KEY_LEFT:
				move_left(windows[2], &current_pos_y, &current_pos_x, -1);
				break;
			case KEY_RIGHT:
				move_right(windows[2], &current_pos_y, &current_pos_x, width - 1);
				break;
			case KEY_UP:
				move_up(windows[2], &current_pos_y, &current_pos_x, -1);
				break;
			case KEY_DOWN:
				move_down(windows[2], &current_pos_y, &current_pos_x, height - 10);
				break;
			case KEY_DC:
			case KEY_BACKSPACE:
				move_left(windows[2], &current_pos_y, &current_pos_x, -1);
				pechochar(windows[2], ' ');
				wmove(windows[2], current_pos_y, current_pos_x);

				if (filebuf_len && (current_pos_x > 1))
					filebuf[filebuf_len--] = ' ';
				break;
			case KEY_ENTER:
			case KEY_NL:
				pechochar(windows[2], '\n');
				current_pos_x = default_pos_x;
				wmove(windows[2], ++current_pos_y, current_pos_x);
				filebuf[filebuf_len++] = '\n';
				break;
			case KEY_TAB:
				for (i = 0; i < 4; ++i) {
					move_right(windows[2], &current_pos_y, &current_pos_x, width - 1);
					pechochar(windows[2], ' ');
					wmove(windows[2], current_pos_y, current_pos_x);
					filebuf[filebuf_len++] = ' ';
				}
				break;
			// Open file
			case CTRL_O:
			case KEY_F(4):
				open_file(filebuf, &filebuf_len, height, width);
				wclear(windows[2]);
				// Insert whole buffer into the editor field
				box(windows[1], ACS_VLINE, ACS_HLINE);
			    mvwaddstr(windows[1], 0, width/2 - strlen(filename)/2, filename);
				prefresh(windows[1], 0, 0, 3, 0, height - 6, width);
				mvwinsstr(windows[2], 0, 0, filebuf);
				break;
			// Save to file
			case CTRL_K:
			case KEY_F(5):
				save_file(filebuf, filebuf_len, height, width);
				break;
			// Extra options
			case CTRL_E:
			case KEY_F(6):
			case CTRL_G:
				change_theme(windows, height, width);
				//extra_options();
				break;
			case CTRL_Y:
				encryption = (encryption == FALSE) ? TRUE : FALSE;
				break;
			// Help
			case CTRL_H:
			case KEY_F(7):
				get_help(height, width);
				break;
			// Exit
			case CTRL_X:
			case KEY_F(8):
				is_exit = TRUE;
				break;
			default:
				if (encryption == TRUE) {
					ch ^= 1;
					filebuf[filebuf_len++] = (char) ch;
				}
				else
					filebuf[filebuf_len++] = (char) ch;

				if (current_pos_x + 1 < width - 1) {
					pechochar(windows[2], ch);
					move_right(windows[2], &current_pos_y, &current_pos_x, width);
				} else {
					++current_pos_y;
					current_pos_x = default_pos_x;
					wmove(windows[2], current_pos_y, current_pos_x);
					pechochar(windows[2], ch);
					move_right(windows[2], &current_pos_y, &current_pos_x, width);
				}
		}

		// Dump the changed content on the screen
		mvwprintw(windows[3], 0, width/2 - 4, " %3d : %3d ", current_pos_y + 1, current_pos_x + 1);
		prefresh(windows[3], 0, 0, height - 5, 0, height, width);
		prefresh(windows[2], 0, 0, 4, 1, height - 7, width - 2);

	} while (is_exit == FALSE);

	free(filebuf);

	endwin();

	return 0;
}
