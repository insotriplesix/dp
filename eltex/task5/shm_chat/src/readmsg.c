#include "readmsg.h"

int
readmsg(void)
{
	int rc = OK;
	char msg[BUFSIZ - FILENAME_MAX];

	if (strncmp(chat_buf, "* :", 3) == 0) {
		repaint_window(LEFT_W);
		current_line_left = 0;

		wattron(win[LEFT_W], BORDER_CLR);
		mvwprintw(win[LEFT_W], 0, 3, "| ROOM ID: %d |", id_shm);
		wattroff(win[LEFT_W], BORDER_CLR);

		for (int i = 0; i < 2; ++i) {
			mvwprintw(win[LEFT_W], ++current_line_left, 1, "%s",
				chat_buf + BUFSIZ + i * NICKNAME_MAX);
		}

		wrefresh(win[LEFT_W]);

		wattron(win[RITE_W], NOTIFY_CLR);
		mvwprintw(win[RITE_W], ++current_line_rite, 1, "%s", chat_buf);
		wattroff(win[RITE_W], NOTIFY_CLR);
	} else if (strlen(chat_buf) > 0 && strcmp(chat_buf, " ") != 0)
		mvwprintw(win[RITE_W], ++current_line_rite, 1, "%s", chat_buf);

	wrefresh(win[RITE_W]);

	memset(chat_buf, '\0', sizeof(char) * BUFSIZ);

	curs_set(TRUE);
	wgetstr(win[BOTM_W], msg);
	curs_set(FALSE);

	if (strcmp(msg, "\\quit") == 0)
		rc = ERR;
	else
		sprintf(chat_buf, "%s : %s", user.nickname, msg);

	mvwprintw(win[RITE_W], ++current_line_rite, 1, "%s", chat_buf);

	return rc;
}
