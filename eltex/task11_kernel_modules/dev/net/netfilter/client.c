#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#define MSGSIZ 64
#define BLOCKED_PORT 666

static int sockfd;

int main(void)
{
	int bytes, serv_len;
	struct sockaddr_in serv_addr;

	serv_len = sizeof(serv_addr);

	sockfd = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP);
	if (sockfd < 0) {
		perror("socket");
		return -1;
	}

	memset((char *) &serv_addr, 0, serv_len);
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	serv_addr.sin_port = htons(BLOCKED_PORT);

	char packet[MSGSIZ] = "Hello!";

	bytes = sendto(sockfd, packet, MSGSIZ, 0, (struct sockaddr *) &serv_addr, serv_len);
	if (bytes < 0) {
		perror("recv");
		return -1;
	}

	return 0;
}
