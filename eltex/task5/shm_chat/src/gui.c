#include "gui.h"

void
draw_window(enum win_t wtype)
{
	wclear(win[wtype]);

	wattron(win[wtype], BORDER_CLR);
	box(win[wtype], ACS_VLINE, ACS_HLINE);
	wattroff(win[wtype], BORDER_CLR);

	switch (wtype) {
		case LEFT_W:
			draw_left(wtype);
			break;
		case RITE_W:
			draw_rite(wtype);
			break;
		case BOTM_W:
			draw_botm(wtype);
			break;
		default:
			break;
	}

	wrefresh(win[wtype]);
}

void
draw_left(enum win_t wtype)
{
	wbkgd(win[wtype], CHAT_CLR);
}

void
draw_rite(enum win_t wtype)
{
	wbkgd(win[wtype], CHAT_CLR);
}

void
draw_botm(enum win_t wtype)
{
	wbkgd(win[wtype], BOTM_CLR);
}

int
input_nickname(void)
{
	WINDOW *win;

	int win_height = 3;
	int win_width = 42;

	int offset_y = LINES / 2;
	int offset_x = COLS / 2;

	win = newwin(win_height, win_width,
		offset_y - win_height / 2,
		offset_x - win_width / 2);

	if (win == NULL) {
		perror("newwin");
		return ERR;
	}

	wattron(win, BORDER_CLR);
	box(win, ACS_VLINE, ACS_HLINE);
	wattroff(win, BORDER_CLR);
	wbkgd(win, POPUP_CLR);

	mvwaddstr(win, 1, 1, " Input nickname: ");
	wrefresh(win);

	curs_set(TRUE);
	mvwgetstr(win, 1, 18, user.nickname);
	curs_set(FALSE);

	user.id = getpid();

	wclear(win);
	wrefresh(win);
	delwin(win);

	return OK;
}
