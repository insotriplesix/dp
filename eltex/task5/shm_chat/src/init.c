#include "gui.h"
#include "init.h"

void
finalize(void)
{
//	list_mem_free(&users);

	sprintf(chat_buf, "* : %s left", user.nickname);

	if (usr1_sem == USR1_SEM) {
		sem_free(id_sem);
		memset(chat_buf + BUFSIZ, '\0',
			sizeof(char) * NICKNAME_MAX);
	} else {
		memset(chat_buf + BUFSIZ + NICKNAME_MAX, '\0',
			sizeof(char) * NICKNAME_MAX);
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

	init_user(argc, argv);
	current_line_left = 1;
	current_line_rite = 1;
//	list_init(&users);
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
	return (initscr() != NULL) & clear() & cbreak()/* & noecho()*/;
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
//	char name[NICKNAME_MAX];
	unsigned short vals[2];

	input_nickname();

	if (argc < 2) {
		id_shm = shmem_alloc(BUFSIZ + NICKNAME_MAX * 2);
		chat_buf = shmem_map(id_shm);

		vals[USR1_SEM] = 0;
		vals[USR2_SEM] = 0;

		id_sem = sem_create(2, vals);
		*((int *) chat_buf) = id_sem;

		usr1_sem = USR1_SEM;
		usr2_sem = USR2_SEM;

		wattron(win[RITE_W], NOTIFY_CLR);
		mvwprintw(win[RITE_W], ++current_line_rite, 1,
			"* : Welcome to the yet another leet chat!");
		wattroff(win[RITE_W], NOTIFY_CLR);

		memcpy(chat_buf + BUFSIZ, user.nickname,
			sizeof(char) * NICKNAME_MAX);
	} else {
		id_shm = atoi(argv[1]);
		chat_buf = shmem_map(id_shm);

		id_sem = *((int *) chat_buf);

		usr1_sem = USR2_SEM;
		usr2_sem = USR1_SEM;

		sprintf(chat_buf, "* : %s joined", user.nickname);
		memcpy(chat_buf + BUFSIZ + NICKNAME_MAX, user.nickname,
			sizeof(char) * NICKNAME_MAX);

		wattron(win[RITE_W], NOTIFY_CLR);
		mvwprintw(win[RITE_W], ++current_line_rite, 1,
			"%s", chat_buf);
		wattroff(win[RITE_W], NOTIFY_CLR);

		sem_unlock(id_sem, usr2_sem);
	}

	wattron(win[LEFT_W], BORDER_CLR);
	mvwprintw(win[LEFT_W], 0, 3, "| ROOM ID: %d |", id_shm);
	wattroff(win[LEFT_W], BORDER_CLR);

	for (int i = 0; i < 2; ++i) {
		mvwprintw(win[LEFT_W], ++current_line_left, 1, "%s",
			chat_buf + BUFSIZ + i * NICKNAME_MAX);
	}

	return OK;
}
