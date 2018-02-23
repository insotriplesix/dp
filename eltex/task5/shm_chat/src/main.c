#include "chat.h"
#include "init.h"
#include "readmsg.h"

//enum { USR1_SEM, USR2_SEM };

int
main(int argc, char *argv[])
{
	int rc = OK;

	initialize(argc, argv);

//	int id_shm;
//	int id_sem;

//	char *buf;

//	unsigned short vals[2];
//	int usr1_sem;
//	int usr2_sem;

//	printf("LETS Chat!!!\n");

//	input_nickname_popup();
/*
	if (argc < 2) {
		id_shm = shmem_alloc(BUFSIZ);
		buf = shmem_map(id_shm);

		vals[USR1_SEM] = 0;
		vals[USR2_SEM] = 0;
		id_sem = sem_create(2, vals);

		*((int *) buf) = id_sem;

		usr1_sem = USR1_SEM;
		usr2_sem = USR2_SEM;

		mvwprintw(win[LEFT_W], 0, 5, "ROOM ID: %d", id_shm);
//		printf("U`r usr1. Shmem id is: %d\n",
//			id_shm);
//		printf("Wait 4 usr2.\n");
	} else {
		id_shm = atoi(argv[1]);
		buf = shmem_map(id_shm);

		id_sem = *((int *) buf);

		usr1_sem = USR2_SEM;
		usr2_sem = USR1_SEM;

		sprintf(buf, " ");

//		printf("U`r usr2. Signal to usr1.\n");
		sem_unlock(id_sem, usr2_sem);
	}
*/
//	while (0x1) {
//		sem_lock(id_sem, usr1_sem);

//		if (strcmp(buf, "\\quit\n") == 0)
//			break;

//		if (strlen(buf) > 0)
//			printf("reply: %s\n", buf);

//		printf("> ");
//		fgets(buf, BUFSIZ, stdin);

//		sem_unlock(id_sem, usr2_sem);

//		if (strcmp(buf, "\\quit\n") == 0)
//			break;
//	}


	while (0x1) {
		update_gui();
		sem_lock(id_sem, usr1_sem);
//		update_gui();
		rc = readmsg();
		sem_unlock(id_sem, usr2_sem);
		if (rc == ERR) break;
	}

//	if (usr1_sem == USR1_SEM)
//		sem_free(id_sem);

	finalize();

	return rc;
}
