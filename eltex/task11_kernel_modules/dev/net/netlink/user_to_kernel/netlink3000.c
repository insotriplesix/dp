/*
 * netlink3000.c - A simple netlink module with R/W capabilities.
 */

#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/netlink.h>
#include <linux/skbuff.h>
#include <net/sock.h>

#include "netlink3000.h"

#define MODULE_NAME "netlink3000"

struct sock *nl3000_sock;

// entry & exit funcs

static int __init kmodule_start(void)
{
	struct netlink_kernel_cfg cfg = {
		.input = nl3000_msg_hndl
	};

	printk(KERN_INFO "Initialize 'netlink3000' module\n");

	nl3000_sock = netlink_kernel_create(&init_net, NETLINK_USERSOCK, &cfg);
	if (nl3000_sock == NULL) {
		printk(KERN_ALERT "Socket creation error\n");
		return -ENOMEM;
	}

	return 0;
}

static void __exit kmodule_end(void)
{
	netlink_kernel_release(nl3000_sock);
	printk(KERN_INFO "Module successfully unloaded\n");
}

/* ---------------------------------------------------------------------- */

#define MSGSIZ 256

static char kbuf[MSGSIZ] = "netlink3000 welcomes you!";

// Recv/Send handling

static void nl3000_msg_hndl(struct sk_buff *sbuf)
{
	struct nlmsghdr *nlh;
	struct sk_buff *sbuf_out;
	size_t kbuf_len, sbuf_len;
	int pid, ret;

	if (sbuf == NULL) {
		printk(KERN_ALERT " 'skbuf' is NULL\n");
		return;
	}

	nlh = (struct nlmsghdr *) sbuf->data;
	sbuf_len = nlh->nlmsg_len;
	pid = nlh->nlmsg_pid;

	printk(KERN_INFO " %zu bytes received from PID=%d;\n"
		" returned message from <%s>: %s\n",
		sbuf_len, pid, MODULE_NAME, (char *) NLMSG_DATA(nlh));

	kbuf_len = strlen(kbuf);

	sbuf_out = nlmsg_new(kbuf_len, 0);
	if (sbuf_out == NULL) {
		printk(KERN_ALERT " not enough memory for new netlink message\n");
		return;
	}

	nlh = nlmsg_put(sbuf_out, 0, 0, NLMSG_DONE, kbuf_len, 0);
	if (nlh == NULL) {
		printk(KERN_ALERT " not enough memory for add netlink message to skb\n");
		return;
	}

	strncpy(NLMSG_DATA(nlh), kbuf, kbuf_len);

	ret = nlmsg_unicast(nl3000_sock, sbuf_out, pid);
	if (ret < 0) {
		printk(KERN_ALERT " nlmsg_unicast() failed with %d\n", ret);
		return;
	}

	printk(KERN_INFO " send kernel message back to PID=%d\n", pid);
}

/* ---------------------------------------------------------------------- */

module_init(kmodule_start);
module_exit(kmodule_end);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("5aboteur");

