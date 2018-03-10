#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// implement 'ls -l | cut -c 48-' routine

#define BUFSIZE 1024

int
main(void)
{
	int fd[2];
	char data[BUFSIZE];
	ssize_t nbytes;

	if (pipe(fd) == -1) {
		fprintf(stderr, "Error pipe creation.\n");
		exit(EXIT_FAILURE);
	}

	pid_t pid = fork();

	switch (pid) {
	case -1:
		fprintf(stderr, "Cannot create child process.\n");
		exit(EXIT_FAILURE);
	case 0:
		close(fd[1]);
		nbytes = read(fd[0], data, BUFSIZE);
		close(fd[0]);
		printf("\nBytes received: 0x%zx\nOutput:\n----------\n%s\n",
			nbytes, data);
		break;
	default:
		close(fd[0]);
		if (dup2(fd[1], STDOUT_FILENO) == -1) {
			fprintf(stderr, "Error fd duplication.\n");
			exit(EXIT_FAILURE);
		}
		close(fd[1]);
		execlp("ls", "ls", "-la", (char *) NULL);
		exit(EXIT_SUCCESS);
	}

	return 0;
}
