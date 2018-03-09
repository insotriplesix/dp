#include "readmsg.h"

void *
msg_recv_func(void *arg)
{
	user_left = 0;

	struct msg_t msg_recv;

	while (!user_left) {
		// usr1 -> 1, usr2 -> 0
		if ((recv_message(qid, usr2, &msg_recv)) != ERR) {
			if ((strncmp(msg_recv.text + BUFSIZE - NICKNAME_MAX, "*", 1)) == 0) {
				wattron(win[RITE_W], NOTIFY_CLR);
				mvwprintw(win[RITE_W], ++current_line_rite, 1, "%s : %s",
					msg_recv.text + BUFSIZE - NICKNAME_MAX, msg_recv.text);
				wattroff(win[RITE_W], NOTIFY_CLR);
			} else {
				mvwprintw(win[RITE_W], ++current_line_rite, 1, "%s : %s",
					msg_recv.text + BUFSIZE - NICKNAME_MAX, msg_recv.text);
			}

			wrefresh(win[RITE_W]);
			wmove(win[BOTM_W], DEFPOS_Y, DEFPOS_X);
		}
	}

	return arg;
}


int
readmsg(void)
{
	int rc = OK;
	struct msg_t msg_send;

	strcpy(msg_send.text + BUFSIZE - NICKNAME_MAX, user.nickname);

	// usr1 -> 0, usr2 -> 1
	msg_send.type = usr1;

	curs_set(TRUE);
	wgetstr(win[BOTM_W], msg_send.text);
	curs_set(FALSE);

	if ((send_message(qid, &msg_send)) == ERR) {
		// errhndl
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
