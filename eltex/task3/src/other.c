#include "other.h"

void change_theme(WINDOW **win, int h, int w)
{
	char choice = change_theme_popup(h, w);

	int fg_field, bg_field, fg_menu,
		bg_menu, fg_popup, bg_popup;

	switch (choice) {
		case '0': // default
			fg_menu = COLOR_BLACK, bg_menu = COLOR_YELLOW;
			fg_field = COLOR_WHITE, bg_field = COLOR_BLUE;
			fg_popup = COLOR_YELLOW, bg_popup = COLOR_BLACK;
			break;
		case '1': // leet
			fg_menu = COLOR_BLACK, bg_menu = COLOR_GREEN;
			fg_field = COLOR_GREEN, bg_field = COLOR_BLACK;
			fg_popup = COLOR_GREEN, bg_popup = COLOR_BLACK;
			break;
		case '2': // sexy
			fg_menu = COLOR_CYAN, bg_menu = COLOR_BLACK;
			fg_field = COLOR_MAGENTA, bg_field = COLOR_CYAN;
			fg_popup = COLOR_CYAN, bg_popup = COLOR_BLACK;
			break;
		case '3': // hell
			fg_menu = COLOR_BLACK, bg_menu = COLOR_RED;
			fg_field = COLOR_RED, bg_field = COLOR_BLACK;
			fg_popup = COLOR_BLACK, bg_popup = COLOR_RED;
			break;
		default:
			return;
	}

	init_pair(1, fg_menu, bg_menu);
	wattrset(win[0], COLOR_PAIR(1));

	init_pair(2, fg_field, bg_field);
	wattrset(win[2], COLOR_PAIR(2));

	init_pair(3, fg_popup, bg_popup);
	wattrset(win[3], COLOR_PAIR(3));

//	wbkgd(win, COLOR_PAIR(2));
}

/* Editor information */
void get_help(int h, int w)
{
	help_popup(h, w);
}

/* Upload content from the file */
void open_file(char *buf, int *sz, int h, int w)
{
	FILE *fp;

	char *fname = open_file_popup(h, w);
	char ch;

	// Try to open the file
	if ((fp = fopen(fname, "r"))) {

		// Read the file til we reach the end of it
		while ((ch = fgetc(fp)) != EOF)
			buf[(*sz)++] = ch;

		fclose(fp);
	}
//	strcpy
	free(fname);
}

/* Save content to the file */
void save_file(char *buf, int sz, int h, int w)
{
	FILE *fp;

	char *fname = save_file_popup(h, w);
	int i;

	// Try to open the file
	if ((fp = fopen(fname, "w"))) {

		// Dump buf content to the file
		for (i = 0; i < sz; ++i)
			fputc(buf[i], fp);

		fclose(fp);
	}

	free(fname);
}

char change_theme_popup(int h, int w)
{
	WINDOW *win;

	int win_height = 6;
	int win_width = 13;
	int line = 1;

	win = newpad(win_height, win_width);
	wbkgd(win, COLOR_PAIR(3));
	box(win, ACS_VLINE, ACS_HLINE);
	curs_set(0);

	wmove(win, line++, 1);
	waddstr(win, " [0] def  ");
	wmove(win, line++, 1);
	waddstr(win, " [1] leet ");
	wmove(win, line++, 1);
	waddstr(win, " [2] sexy ");
	wmove(win, line++, 1);
	waddstr(win, " [3] hell ");

	prefresh(win, 0, 0, h / 2 - win_height / 2, w / 2 - win_width / 2,
		h / 2 + win_height / 2, w / 2 + win_width / 2);

	char choice = wgetch(win);

	wclear(win);
	curs_set(1);

	return choice;
}

void help_popup(int h, int w)
{
	WINDOW *win;

	int win_height = 15;
	int win_width = 30;
	int line = 1;

	win = newpad(win_height, win_width);
	wbkgd(win, COLOR_PAIR(3));
	box(win, ACS_VLINE, ACS_HLINE);
	curs_set(0);

	wmove(win, line++, win_width / 4);
	waddstr(win, "5aboteditor v1.0");
	wmove(win, line++, 1);
	waddstr(win, "");
	wmove(win, line++, 1);
	waddstr(win, "--- cmd --------------------");
	wmove(win, line++, 1);
	waddstr(win, " F4, ^O - open file");
	wmove(win, line++, 1);
	waddstr(win, " F5, ^K - save to file");
	wmove(win, line++, 1);
	waddstr(win, " F6, ^X - extra options");
	wmove(win, line++, 1);
	waddstr(win, " F7, ^H - get help");
	wmove(win, line++, 1);
	waddstr(win, " F8, ^E - exit");
	wmove(win, line++, 1);
	waddstr(win, "");
	wmove(win, line++, 1);
	waddstr(win, "--- ext --------------------");
	wmove(win, line++, 1);
	waddstr(win, " ^G - change editor theme");
	wmove(win, line++, 1);
	waddstr(win, " ^W - (en/de)crypt text");
	wmove(win, line++, 1);
	waddstr(win, " ^? - . . . ");

	prefresh(win, 0, 0, h / 2 - win_height / 2, w / 2 - win_width / 2,
		h / 2 + win_height / 2, w / 2 + win_width / 2);

	wgetch(win);
	wclear(win);

	curs_set(1);
}

char *open_file_popup(int h, int w)
{
	WINDOW *win;

	char *fname = (char *) malloc(sizeof(char) * FNAME_MAX_SIZE);

	int win_height = 3;
	int win_width = 42;

	echo();

	win = newwin(win_height, win_width,
		h/2 - win_height/2, w/2 - win_width/2);

	wbkgd(win, COLOR_PAIR(3));
	box(win, ACS_VLINE, ACS_HLINE);
	mvwaddstr(win, 1, 1, " Enter file name: ");
	wrefresh(win);
	mvwgetstr(win, 1, 19, fname);

	noecho();

	delwin(win);

	return fname;
}

char *save_file_popup(int h, int w)
{
	WINDOW *win;

	char *fname = (char *) malloc(sizeof(char) * FNAME_MAX_SIZE);

	int win_height = 3;
	int win_width = 42;

	echo();

	win = newwin(win_height, win_width,
		h/2 - win_height/2, w/2 - win_width/2);

	wbkgd(win, COLOR_PAIR(3));
	box(win, ACS_VLINE, ACS_HLINE);
	mvwaddstr(win, 1, 1, " Enter file name: ");
	wrefresh(win);
	mvwgetstr(win, 1, 19, fname);

	noecho();

	delwin(win);

	return fname;
}
