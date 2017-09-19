#include "other.h"

/* Upload content from the file */
void load_file(char *fname, char *buf, int *sz)
{
	FILE *fp;
	char ch;

	// Try to open the file
	if ((fp = fopen(fname, "rb"))) {

		// Read the file til we reach the end of it
		while ((ch = fgetc(fp)) != EOF)
			buf[(*sz)++] = ch;

		fclose(fp);
	}
}

/* Save content to the file */
void save_file(char *fname, char *buf, int sz)
{
	FILE *fp;
	int i;

	// Try to open the file
	if ((fp = fopen(fname, "wb"))) {

		// Dump buf content to the file
		for (i = 0; i < sz; ++i)
			fputc(buf[i], fp);

		fclose(fp);
	}
}

/* ??? */
void secret_func(WINDOW *win, int h, int w)
{
	int i, j;

	// For the secret things
	int secret_y = h - 10, secret_x = w, secret_d = 1;
	chtype secret_c;

	// Make some NOISE !!!!!!!
	for (i = 0; i < h; ++i) {
		for (j = 0; j < w; ++j) {
			if (secret_x < 0 || secret_x >= w)
				secret_d *= -1;

			secret_x += secret_d * 2;

			secret_c = 33 + rand() % 93;
			secret_c |= A_BLINK | A_REVERSE;
			mvwaddch(win, secret_y, secret_x, secret_c);
			usleep(1337);

			wrefresh(win);
			doupdate();
		}

		--secret_y;
	}
}
