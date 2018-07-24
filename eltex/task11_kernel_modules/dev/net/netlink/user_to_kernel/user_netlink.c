#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <linux/netlink.h>
#include <sys/socket.h>

#define MSGSIZ 256
#define NETLINK_USER 31

#define MODULE_NAME "netlink3000"

int main(void)
{
	struct sockaddr_nl src_addr, dest_addr;
	struct iovec iov;
	struct nlmsghdr *nlh;
	struct msghdr mhdr;

	int pid, ret, sock_fd;

	pid = getpid();						// pid of cur proc

	sock_fd = socket(PF_NETLINK, SOCK_RAW, NETLINK_USER);
	if (sock_fd < 0) {
		fprintf(stderr, "Cannot create socket for '%s'\n", MODULE_NAME);
		return -1;
	}

	size_t src_len = sizeof(src_addr);

	memset(&src_addr, 0, src_len);
	src_addr.nl_family = AF_NETLINK;
	src_addr.nl_pid = pid;
	src_addr.nl_groups = 0;				// non-multicast

	ret = bind(sock_fd, (struct sockaddr *) &src_addr, src_len);
	if (ret < 0) {
		fprintf(stderr, "Cannot bind address, ret value: %d\n", ret);
		return ret;
	}

	size_t dest_len = sizeof(dest_len);

	memset(&dest_addr, 0, dest_len);
	dest_addr.nl_family = AF_NETLINK;
	dest_addr.nl_pid = 0;				// kernel pid
	dest_addr.nl_groups = 0;			// non-multicast

	size_t msg_len = NLMSG_SPACE(MSGSIZ);

	nlh = (struct nlmsghdr *) malloc(msg_len);

	memset(nlh, 0, msg_len);
	nlh->nlmsg_len = msg_len;
	nlh->nlmsg_pid = pid;
	nlh->nlmsg_flags = 0;

	char msg[MSGSIZ] = "Hello from user space\n";

	strcpy(NLMSG_DATA(nlh), msg);

	iov.iov_base = (void *) nlh;		// ptr to the msg data
	iov.iov_len = nlh->nlmsg_len;

	size_t mhdr_len = sizeof(mhdr);

	memset(&mhdr, 0, mhdr_len);
	mhdr.msg_name = (void *) &dest_addr;
	mhdr.msg_namelen = dest_len;
	mhdr.msg_iov = &iov;
	mhdr.msg_iovlen = 1;				// array dimension

	ret = sendmsg(sock_fd, &mhdr, 0);
	if (ret < 0) {
		fprintf(stderr, "Failed to send the message to the kernel. Err: %s\n",
			strerror(errno));
		return ret;
	}

	printf("Message sent, waiting for response..\n");

	ret = recvmsg(sock_fd, &mhdr, 0);
	if (ret < 0) {
		fprintf(stderr, "Failed to receive the message from the kernel. Err: %s\n",
			strerror(errno));
		return ret;
	}

	printf("Reply: %s\n", (char *) NLMSG_DATA(nlh));

	close(sock_fd);

	return 0;
}
