#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <error.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>

#define SERVERPORT 6666

int
main(int argc, char *argv[])
{
	int sockfd, rc;
	struct sockaddr_in their_addr;
	struct hostent *he;

	ssize_t numbytes;
	int broadcast = 1;

	if (argc != 3) {
		fprintf(stderr, "usage: broadcaster hostname msg.\n");
		exit(EXIT_FAILURE);
	}

	he = gethostbyname(argv[1]);
	if (he == NULL) {
		perror("gethostbyname");
		exit(EXIT_FAILURE);
	}

	sockfd = socket(PF_INET, SOCK_DGRAM, 0);
	if (sockfd < 0) {
		perror("socket");
		exit(EXIT_FAILURE);
	}

	rc = setsockopt(sockfd, SOL_SOCKET, SO_BROADCAST, &broadcast,
		sizeof(broadcast));
	if (rc < 0) {
		perror("setsockopt");
		exit(EXIT_FAILURE);
	}

	their_addr.sin_family = AF_INET;
	their_addr.sin_port = htons(SERVERPORT);
	their_addr.sin_addr = *((struct in_addr *) he->h_addr);
	memset(their_addr.sin_zero, '\0', sizeof(their_addr.sin_zero));

	numbytes = sendto(sockfd, argv[2], strlen(argv[2]), 0,
		(struct sockaddr *) &their_addr, sizeof(their_addr));
	if (numbytes < 0) {
		perror("sendto");
		exit(EXIT_FAILURE);
	}

	printf("sent %d bytes to %s\n", numbytes, inet_ntoa(their_addr.sin_addr));

	close(sockfd);

	return 0;
}
