/*
 * arp_table.c -- ARP table info via netlink socket.
 */

#include <arpa/inet.h>
#include <errno.h>
#include <linux/if_addr.h>
#include <linux/if_ether.h>
#include <linux/netlink.h>
#include <linux/rtnetlink.h>
#include <net/if.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#define DEBUG 0

#define HWTYPE_LEN 16
#define HWADDR_LEN 20
#define STATE_LEN 16
#define FLAGS_LEN 8
#define IFNAME_LEN 8

typedef struct Entry {
	char ipaddr[INET_ADDRSTRLEN];
	char hwtype[HWTYPE_LEN];
	char hwaddr[HWADDR_LEN];
	char state[STATE_LEN];
	char flags[FLAGS_LEN];
	char mask[INET_ADDRSTRLEN];
	char iface[IFNAME_LEN];
} ent_t;

#define MAX_ENTRIES 16

typedef struct Table {
	ent_t e[MAX_ENTRIES];
} tbl_t;

tbl_t arp_table;

void print_table(int n)
{
	puts("");
	printf(" Address\t | HWtype | HWaddress\t      | State\t   | Flags | Mask\t     | Iface\n");
	printf("----------------------------------------------------------------------------------------------\n");

	for (int i = 0; i < n; i++) {
		printf(" %-15s | %-6s | %-17s | %-10s | %-5s | %-15s | %-3s\n",
			(strcmp(arp_table.e[i].ipaddr, "")) ? arp_table.e[i].ipaddr : "N/A",
			(strcmp(arp_table.e[i].hwtype, "")) ? arp_table.e[i].hwtype : "N/A",
			(strcmp(arp_table.e[i].hwaddr, "")) ? arp_table.e[i].hwaddr : "N/A",
			(strcmp(arp_table.e[i].state, "")) ? arp_table.e[i].state : "N/A",
			(strcmp(arp_table.e[i].flags, "")) ? arp_table.e[i].flags : "N/A",
			(strcmp(arp_table.e[i].mask, "")) ? arp_table.e[i].mask : "N/A",
			(strcmp(arp_table.e[i].iface, "")) ? arp_table.e[i].iface : "N/A");
	}

	puts("");
}

void process_message(char *buf, ssize_t buf_len)
{
	struct nlmsghdr *hdr;	// header
	struct ndmsg *data;		// data

	struct rtattr *rtat;	// attributes

	int i = 0;
	ssize_t rtat_len;

#if DEBUG
	printf("Caught a message, buf_len = %lu bytes, processing it..\n",
		buf_len);

	puts("");
#endif

	for (hdr = (struct nlmsghdr *) buf; NLMSG_OK(hdr, buf_len); hdr = NLMSG_NEXT(hdr, buf_len)) {

#if DEBUG
		int msg_len = hdr->nlmsg_len;
		int hdr_len = sizeof(*hdr);

		printf("Part #%d.\n", i + 1);
		printf(" > buf_len = %ld\n", buf_len);
		printf(" > hdr_len = %ld\n", hdr_len);
		printf(" > msg_len = %d\n", msg_len);
#endif

		data = (struct ndmsg *) NLMSG_DATA(hdr);
		rtat = (struct rtattr *) RTM_RTA(data);

		rtat_len = RTM_PAYLOAD(hdr);

#if DEBUG
		printf(" > rtat_len = %ld\n", rtat_len);
#endif

		if (data->ndm_state == 0x40) // 0x40 ~> NOARP (no need them)
			continue;

		// state
		switch (data->ndm_state) {
		case 0x01:
			sprintf(arp_table.e[i].state, "INCOMPLETE");
			break;
		case 0x02:
			sprintf(arp_table.e[i].state, "REACHABLE");
			break;
		case 0x04:
			sprintf(arp_table.e[i].state, "STALE");
			break;
		case 0x08:
			sprintf(arp_table.e[i].state, "DELAY");
			break;
		case 0x10:
			sprintf(arp_table.e[i].state, "PROBE");
			break;
		case 0x20:
			sprintf(arp_table.e[i].state, "FAILED");
			break;
		case 0x80:
			sprintf(arp_table.e[i].state, "PERMANENT");
			break;
		case 0x00:
			sprintf(arp_table.e[i].state, "NONE");
			break;
		default:
			sprintf(arp_table.e[i].state, "UNKNOWN");
			break;
		}

		for (; RTA_OK(rtat, rtat_len); rtat = RTA_NEXT(rtat, rtat_len)) {
			char lladdr[ETH_ALEN];

			// ipaddr
			if (rtat->rta_type == NDA_DST) {
				inet_ntop(AF_INET, RTA_DATA(rtat), arp_table.e[i].ipaddr, INET_ADDRSTRLEN);
				if (arp_table.e[i].ipaddr == NULL) {
					fprintf(stderr, "inet_ntop() failed. Err: %s\n", strerror(errno));
						return;
				}
			}
			// hwaddr
			else if (rtat->rta_type == NDA_LLADDR) {
				memset(&lladdr, 0, ETH_ALEN);
				memcpy(lladdr, RTA_DATA(rtat), ETH_ALEN);
				sprintf(arp_table.e[i].hwaddr, "%02hhx:%02hhx:%02hhx:%02hhx:%02hhx:%02hhx",
					lladdr[0], lladdr[1], lladdr[2], lladdr[3], lladdr[4], lladdr[5]);
			}
		}

		// flags
		sprintf(arp_table.e[i].flags, "0x%x", data->ndm_flags);

		// iface
		if_indextoname(data->ndm_ifindex, arp_table.e[i].iface);
		if (arp_table.e[i].iface == NULL) {
			fprintf(stderr, "if_indextoname() failed. Err: %s\n", strerror(errno));
			return;
		}

#if DEBUG
		printf("fam: %x, if: %d, st: %x, fl: %x, type: %x\n",
			data->ndm_family,
			data->ndm_ifindex,
			data->ndm_state,
			data->ndm_flags,
			data->ndm_type);
#endif

		i++;

#if DEBUG
		puts("");
#endif
	}

	print_table(i);
}

typedef struct Request {
	struct nlmsghdr nlmh;
	struct ndmsg ndm;
} req_t;

int main(void)
{
	struct sockaddr_nl grp_addr;
	ssize_t rbytes;
	int ret, sock_fd;

	sock_fd = socket(PF_NETLINK, SOCK_RAW, NETLINK_ROUTE);
	if (sock_fd < 0) {
		fprintf(stderr, "Failed to create a socket. Err: %s\n",
			strerror(errno));
		return -1;
	}

	// Fill the netlink client structure

	size_t grp_len = sizeof(grp_addr);

	memset(&grp_addr, 0, grp_len);
	grp_addr.nl_family = AF_NETLINK;
	grp_addr.nl_groups = RTMGRP_LINK | RTMGRP_IPV4_IFADDR | RTMGRP_IPV4_ROUTE;

	ret = bind(sock_fd, (struct sockaddr *) &grp_addr, grp_len);
	if (ret < 0) {
		fprintf(stderr, "Failed to bind the address. Err: %s\n",
			strerror(errno));
		return ret;
	}

	// Fill the request structure

	req_t req;
	size_t req_len = sizeof(req);

	memset(&req, 0, req_len);

	req.nlmh.nlmsg_len = NLMSG_LENGTH(sizeof(struct ndmsg));
	req.nlmh.nlmsg_flags = NLM_F_REQUEST | NLM_F_ROOT;
	req.nlmh.nlmsg_type = RTM_GETNEIGH;

	req.ndm.ndm_family = AF_INET;
	req.ndm.ndm_state = NUD_INCOMPLETE | NUD_REACHABLE | NUD_STALE | NUD_PERMANENT;


	rbytes = send(sock_fd, &req, req.nlmh.nlmsg_len, 0);
	if (rbytes < 0) {
		fprintf(stderr, "Failed to send the msg. Err: %s\n",
			strerror(errno));
		return -1;
	}

	char buf[BUFSIZ];

	do {
		rbytes = recv(sock_fd, buf, BUFSIZ, 0);
		if (rbytes < 0) {
			fprintf(stderr, "Failed to recv the msg. Err: %s\n",
				strerror(errno));
			return -1;
		}
		process_message(buf, rbytes);
	} while (0);

	close(sock_fd);

	return 0;
}
