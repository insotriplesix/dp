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

	// Default position of the cursor
	int def_pos_x = 0, def_pos_y = 0;

	// Current cursor position in the edit field
	int field_y = def_pos_y, field_x = def_pos_x;

	int is_exit = FALSE;

	ch = wgetch(windows[2]);	// <~~ enable this and magic '~Z' disappear

	do {
		ch = wgetch(windows[2]);

		switch (ch) {
			case KEY_LEFT:
				move_left(windows[2], &field_y, &field_x, -1);
				break;
			case KEY_RIGHT:
				move_right(windows[2], &field_y, &field_x, width - 1);
				break;
			case KEY_UP:
				move_up(windows[2], &field_y, &field_x, -1);
				break;
			case KEY_DOWN:
				move_down(windows[2], &field_y, &field_x, height - 10);
				break;
			case KEY_DC:
			case 127:
			case KEY_BACKSPACE:
				move_left(windows[2], &field_y, &field_x, -1);
				pechochar(windows[2], ' ');
				wmove(windows[2], field_y, field_x);

				if (filebuf_len && (field_x > 1))
					filebuf[filebuf_len--] = ' ';
				break;
			case '\n':
			case KEY_ENTER:
				pechochar(windows[2], '\n');
				field_x = def_pos_x;
				wmove(windows[2], ++field_y, field_x);
				filebuf[filebuf_len++] = '\n';
				break;
			case '\t':
				for (i = 0; i < 4; ++i) {
					move_right(windows[2], &field_y, &field_x, width - 1);
					pechochar(windows[2], ' ');
					wmove(windows[2], field_y, field_x);
					filebuf[filebuf_len++] = ' ';
				}
				break;
			// Open file
			case CTRL_O:
			case KEY_F(4):
				open_file(filebuf, &filebuf_len, height, width);
//				wclear(windows[2]);
				// Insert whole buffer into the editor field
				box(windows[1], ACS_VLINE, ACS_HLINE);
			    mvwaddstr(windows[1], 0, width / 2 - strlen(filename) / 2, filename);
				prefresh(windows[1], 0, 0, 3, 0, height - 6, width);
				mvwinsstr(windows[2], 0, 0, filebuf);
				break;
			// Save to file
			case CTRL_K:
			case KEY_F(5):
				save_file(filebuf, filebuf_len, height, width);
				break;
			// Extra options
			case CTRL_X:
			case KEY_F(6):
			case CTRL_G:
				change_theme(windows, height, width);
				//extra_options();
				break;
			// Help
			case CTRL_H:
			case KEY_F(7):
				get_help(height, width);
				break;
			// Exit
			case CTRL_E:
			case KEY_F(8):
				is_exit = TRUE;
				break;
			default:
				// Add input symbol to the buffer
				filebuf[filebuf_len++] = (char) ch;

				// Display it on the edit field
				if (field_x + 1 < width - 1) {
					pechochar(windows[2], ch);
					move_right(windows[2], &field_y, &field_x, width);
				} else {
					++field_y;
					field_x = def_pos_x;
					wmove(windows[2], field_y, field_x);
					pechochar(windows[2], ch);
					move_right(windows[2], &field_y, &field_x, width);
				}
		}

		// Dump the changed content on the screen
		mvwprintw(windows[3], 0, width / 2 - 4, "%3d :%3d ", field_y + 1, field_x + 1);
		prefresh(windows[3], 0, 0, height - 5, 0, height, width);

		prefresh(windows[2], 0, 0, 4, 1, height - 7, width - 1);

	} while (is_exit == FALSE);

	free(filebuf);

	endwin();

	return 0;
}
