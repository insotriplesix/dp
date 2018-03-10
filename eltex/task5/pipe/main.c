#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

// implement 'ls -l | cut -c 48-' bash cmd

#define P_RD 0
#define P_WR 1
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

	puts("\n\033[1;33mTest bash output:\033[0m");
	system("ls -l | cut -c 48-");
	puts("\n\033[1;33mProgram output:\033[0m");

	/////////////////////////////////////////////////////

	pid_t pid = fork();

	switch (pid) {
	case -1:
		fprintf(stderr, "Cannot create child process.\n");
		close(fd[P_RD]);
		close(fd[P_WR]);
		exit(EXIT_FAILURE);
	case 0:
		// pipe: -> [BACK, FRNT]
		if (dup2(fd[P_WR], STDOUT_FILENO) == -1) {
			fprintf(stderr, "Error fd duplication.\n");
			exit(EXIT_FAILURE);
		}

		close(fd[P_RD]);
		close(fd[P_WR]);

		execlp("ls", "ls", "-la", (char *) NULL);
		exit(EXIT_SUCCESS);
	default:
		wait(&pid);
	}

	pid = fork();

	switch (pid) {
	case -1:
		fprintf(stderr, "Cannot create child process.\n");
		close(fd[P_RD]);
		close(fd[P_WR]);
		exit(EXIT_FAILURE);
	case 0:
		// pipe: [BACK, FRNT] <-
		if (dup2(fd[P_RD], STDIN_FILENO) == -1) {
			fprintf(stderr, "Error fd duplication.\n");
			exit(EXIT_FAILURE);
		}

		// pipe: -> [BACK, FRNT]
		if (dup2(fd[P_WR], STDOUT_FILENO) == -1) {
			fprintf(stderr, "Error fd duplication.\n");
			exit(EXIT_FAILURE);
		}

		close(fd[P_RD]);
		close(fd[P_WR]);

		nbytes = read(fd[P_RD], data, BUFSIZE);

		close(fd[P_RD]);
		close(fd[P_WR]);

		printf("\nBytes received: 0x%zx\nData:\n-----\n%s\n",
			nbytes, data);
//		execlp("cut", "cut", "-c", "48-", (char *) NULL);
		exit(EXIT_SUCCESS);
	default:
		wait(&pid);

		// pipe: [BACK, FRNT] <-
		nbytes = read(fd[P_RD], data, BUFSIZE);

		close(fd[P_RD]);
		close(fd[P_WR]);

		printf("\nBytes received: 0x%zx\nData:\n-----\n%s\n",
			nbytes, data);
		break;
	}

	return 0;
}
