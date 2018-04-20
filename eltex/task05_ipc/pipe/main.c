#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

// implement 'ls -la | cut -c 48-' bash cmd

#define P_RD 0
#define P_WR 1

int
main(void)
{
	int fd[2];

	if (pipe(fd) == -1) {
		fprintf(stderr, "Error pipe creation.\n");
		exit(EXIT_FAILURE);
	}

	puts("\n\033[1;33mTest bash output:\033[0m");
	system("ls -la | cut -c 48-");
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
		// pipe: [BACK, FRNT] <-
		if (dup2(fd[P_RD], STDIN_FILENO) == -1) {
			fprintf(stderr, "Error fd duplication.\n");
			exit(EXIT_FAILURE);
		}

		close(fd[P_RD]);
		close(fd[P_WR]);

		execlp("cut", "cut", "-c", "48-", (char *) NULL);
		exit(EXIT_SUCCESS);
	default:
		break;
	}

	pid = fork();

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
		close(fd[P_RD]);
		close(fd[P_WR]);
	}

	puts("\n\033[1;33mDone!\033[0m");

	return 0;
}
