#include "gui.h"
#include "init.h"

void
finalize(void)
{
//	sprintf(chat_buf, "* : %s left", user.nickname);
//	struct user_t usr_send;

	struct msg_t msg_send;
	msg_send.type = 1;
//	msg_send.user_id = user.id;
	char usr_left_msg[NICKNAME_MAX + 10];
	sprintf(usr_left_msg, "%s left", user.nickname);
	strcpy(msg_send.text + BUFSIZE - NICKNAME_MAX, "*");
	strcpy(msg_send.text, usr_left_msg);
//	msg_send.user = &usr_send;
//	msg_send.user.id = user.id;
//	strcpy(msg_send->user.nickname, user.nickname);

	if ((send_message(qid, &msg_send)) == ERR) {
		//stub
	}

	if (usr1 == USR1) {
		if (remove_queue(qid) == ERR) {
			fprintf(stderr, "Error in queue removing.\n");
			exit(EXIT_FAILURE);
		}
/*		sem_free(id_sem);
		memset(chat_buf + BUFSIZ, '\0',
			sizeof(char) * NICKNAME_MAX);
	} else {
		memset(chat_buf + BUFSIZ + NICKNAME_MAX, '\0',
			sizeof(char) * NICKNAME_MAX);
*/	}

	if (pthread_join(msg_recv_thr, NULL)) {
		fprintf(stderr, "Error in thread joining.\n");
		exit(EXIT_FAILURE);
	}

	for (int i = 0; i < NWINDOWS; ++i)
		delwin(win[i]);

	endwin();
}

void
initialize(int argc, char *argv[])
{
	if (init_ncurses() | init_colors() | init_windows() | init_gui()) {
		endwin();
		fprintf(stderr, "Initializing error.\n");
		exit(EXIT_FAILURE);
	}

	if (LINES < 6 || COLS < 98) {
		endwin();
		fprintf(stderr, "Terminal window is too small.\n"
			"Min: 6x98, your: %dx%d\n", LINES, COLS);
		exit(EXIT_FAILURE);
	}

	if ((key = ftok(argv[0], 'm')) == ERR) {
		endwin();
		fprintf(stderr, "Error in key initializing.\n");
		exit(EXIT_FAILURE);
	}

	if ((qid = open_queue(key)) == ERR) {
		endwin();
		fprintf(stderr, "Error in queue opening.\n");
		exit(EXIT_FAILURE);
	}

	init_user(argc, argv);

	current_line_left = 1;
	current_line_rite = 1;

	if (pthread_create(&msg_recv_thr, NULL, msg_recv_func, NULL)) {
		endwin();
		fprintf(stderr, "Error in thread create.\n");
		exit(EXIT_FAILURE);
	}

	// ^^^ Incorrect freeing stuff tho' ^^^
}

int
init_colors(void)
{
	if (start_color() == ERR || !has_colors()) {
		fprintf(stderr, "This terminal doesn't support colouring.\n");
		return ERR;
	}

	// Pair id, Foreground, Background
	init_pair(1, COLOR_BLACK, COLOR_YELLOW);	// menu components
	init_pair(2, COLOR_WHITE, COLOR_BLUE);		// edit field
	init_pair(3, COLOR_YELLOW, COLOR_BLACK);	// pop-up windows
	init_pair(4, COLOR_WHITE, COLOR_BLACK);		// borders
	init_pair(5, COLOR_RED, COLOR_YELLOW);		// notifications

	return OK;
}

int
init_gui(void)
{
	for (int i = 0; i < NWINDOWS; ++i)
		draw_window(i);

	return OK;
}

int
init_ncurses(void)
{
	return (initscr() != NULL) & clear() & cbreak();
}

int
init_windows(void)
{
	win[LEFT_W] = newwin(LINES - 3, NICKNAME_MAX + 2, 0, 0);
	if (win[LEFT_W] == NULL) {
		perror("newwin");
		return ERR;
	}

	win[RITE_W] = newwin(LINES - 3, COLS - NICKNAME_MAX - 2,
		0, NICKNAME_MAX + 2);
	if (win[RITE_W] == NULL) {
		perror("newwin");
		return ERR;
	}

	win[BOTM_W] = newwin(3, COLS, LINES - 3, 0);
	if (win[BOTM_W] == NULL) {
		perror("newwin");
		return ERR;
	}

	// Enable scrolling, func keys, arrows etc.
	curs_set(FALSE);
	keypad(win[BOTM_W], TRUE);

	return OK;
}

int
init_user(int argc, char *argv[])
{
//	unsigned short vals[2];

	input_nickname();

	if (argc < 2) {
		usr1 = USR1;
		usr2 = USR2;
/*		id_shm = shmem_alloc(BUFSIZ + NICKNAME_MAX * 2);
		chat_buf = shmem_map(id_shm);

		vals[USR1_SEM] = 0;
		vals[USR2_SEM] = 0;

		id_sem = sem_create(2, vals);
		*((int *) chat_buf) = id_sem;

		usr1_sem = USR1_SEM;
		usr2_sem = USR2_SEM;
*/
		wattron(win[RITE_W], NOTIFY_CLR);
		mvwprintw(win[RITE_W], ++current_line_rite, 1,
			"* : Welcome to the yet another leet chat!");
		wattroff(win[RITE_W], NOTIFY_CLR);
/*
		memcpy(chat_buf + BUFSIZ, user.nickname,
			sizeof(char) * NICKNAME_MAX);
*/	} else {
		usr1 = USR2;
		usr2 = USR1;
/*		id_shm = atoi(argv[1]);
		chat_buf = shmem_map(id_shm);

		id_sem = *((int *) chat_buf);

		usr1_sem = USR2_SEM;
		usr2_sem = USR1_SEM;
*/
// SND MSG
//		sprintf(chat_buf, "* : %s joined", user.nickname);
/*		memcpy(chat_buf + BUFSIZ + NICKNAME_MAX, user.nickname,
			sizeof(char) * NICKNAME_MAX);

		wattron(win[RITE_W], NOTIFY_CLR);
		mvwprintw(win[RITE_W], ++current_line_rite, 1,
			"%s", chat_buf);
		wattroff(win[RITE_W], NOTIFY_CLR);

		sem_unlock(id_sem, usr2_sem);
*/	}

	wattron(win[LEFT_W], BORDER_CLR);
	mvwprintw(win[LEFT_W], 0, 2, "| ROOM ID: %d |", key);
	wattroff(win[LEFT_W], BORDER_CLR);
/*
	for (int i = 0; i < 2; ++i) {
		mvwprintw(win[LEFT_W], ++current_line_left, 1, "%s",
			chat_buf + BUFSIZ + i * NICKNAME_MAX);
	}
*/
	return OK;
}
