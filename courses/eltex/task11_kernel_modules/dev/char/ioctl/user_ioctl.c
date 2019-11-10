#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <unistd.h>

#define MSGSIZ 256

#define DEVICE_NAME "oblivion_ioctl"

#define MAJOR_NUM 444

#define IOCTL_SET_KBUF _IOR(MAJOR_NUM, 0, char *)
#define IOCTL_GET_KBUF _IOR(MAJOR_NUM, 1, char *)

void
ioctl_set_kbuf(int fd, char *buf)
{
	int ret = ioctl(fd, IOCTL_SET_KBUF, buf);

	if (ret < 0) {
		printf("ioctl_set_kbuf() failed with %d\n", ret);
		exit(EXIT_FAILURE);
	}
}

void
ioctl_get_kbuf(int fd)
{
	char buf[MSGSIZ];
	int ret = ioctl(fd, IOCTL_GET_KBUF, buf);

	if (ret < 0) {
		printf("ioctl_get_kbuf() failed with %d\n", ret);
		exit(EXIT_FAILURE);
	}

	printf("Message: %s\n", buf);
}

int
main(void)
{
	int fd;

	char msg[MSGSIZ] = "Hello from user space!\n";

	fd = open(DEVICE_NAME, 0);
	if (fd < 0) {
		printf("Can't open device '%s'\n", DEVICE_NAME);
		exit(EXIT_FAILURE);
	}

	ioctl_get_kbuf(fd);
	ioctl_set_kbuf(fd, msg);
	ioctl_get_kbuf(fd);

	close(fd);

	return 0;
}
