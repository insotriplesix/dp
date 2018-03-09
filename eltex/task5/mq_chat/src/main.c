#include "chat.h"
#include "init.h"
#include "readmsg.h"

int
main(int argc, char *argv[])
{
	int rc = OK;

	initialize(argc, argv);

	while (0x1) {
		update_gui();
//		sem_lock(id_sem, usr1_sem);
		rc = readmsg();
//		sem_unlock(id_sem, usr2_sem);
		if (rc == ERR) break;
	}

	finalize();

	return rc;
}
