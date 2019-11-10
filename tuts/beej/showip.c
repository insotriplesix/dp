#include <arpa/inet.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>

int
main(int argc, char *argv[])
{
	int status;
	char ipstr[INET6_ADDRSTRLEN];
	struct addrinfo hints, *res, *p;

	if (argc != 2) {
		fprintf(stderr, "usage: ./showip hostname\n");
		exit(EXIT_FAILURE);
	}

	memset(&hints, 0, sizeof(hints));
	hints.ai_family = AF_UNSPEC;		// AF_INET or AF_INET6
	hints.ai_socktype = SOCK_STREAM;

	status = getaddrinfo(argv[1], NULL, &hints, &res);
	if (status != 0) {
		fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(status));
		exit(EXIT_FAILURE);
	}

	printf("IP addresses for %s:\n\n", argv[1]);

	for (p = res; p != NULL; p = p->ai_next) {
		void *addr;
		char *ipver;

		if (p->ai_family == AF_INET) {
			struct sockaddr_in *ipv4 = (struct sockaddr_in *) p->ai_addr;
			addr = &(ipv4->sin_addr);
			ipver = "IPv4";
		} else {
			struct sockaddr_in6 *ipv6 = (struct sockaddr_in6 *) p->ai_addr;
			addr = &(ipv6->sin6_addr);
			ipver = "IPv6";
		}

		inet_ntop(p->ai_family, addr, ipstr, sizeof(ipstr));
		printf(" %s: %s\n", ipver, ipstr);
	}

	freeaddrinfo(res);
	return 0;
}
