#include "readmsg.h"

void *
msg_recv_func(void *arg)
{
	user_left = 0;

	struct msg_t msg_recv;

	while (!user_left) {
		if ((recv_message(qid, usr2, &msg_recv)) == OK) {
			mvwprintw(win[RITE_W], ++current_line_rite, 1, "%s : %s",
				msg_recv.text + BUFSIZE - NICKNAME_MAX, msg_recv.text);

			wrefresh(win[RITE_W]);
//		message_arrived = TRUE;
		}
	}

	return arg;
}


int
readmsg(void)
{
	int rc = OK;
//	char msg[BUFSIZ - FILENAME_MAX];
/*
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
*/
//	struct user_t usr_send;

	struct msg_t msg_send;
//	msg_send.user_id = user.id;
	strcpy(msg_send.text + BUFSIZE - NICKNAME_MAX, user.nickname);
	msg_send.type = usr1;

	curs_set(TRUE);
	wgetstr(win[BOTM_W], msg_send.text);
	curs_set(FALSE);

	if ((send_message(qid, &msg_send)) == ERR) {
		// stub
	}

	if (strncmp(msg_send.text, "\\quit", 5) == 0) {
		user_left = 1;
		rc = ERR;
	}
//	else
//		sprintf(chat_buf, "%s : %s", user.nickname, msg);
//		mvwprintw(win[RITE_W], ++current_line_rite, 1, "%s : %s",
//			msg_send.user.nickname, msg_send.text);

	return rc;
}
