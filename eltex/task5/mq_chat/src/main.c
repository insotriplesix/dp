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
		rc = readmsg();
		if (rc == ERR) break;
	}

	finalize();

	return rc;
}
