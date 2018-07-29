/*
 * netfilter.c - A simple netfilter module with port blocking capabilities.
 */

#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/netfilter.h>
#include <linux/netfilter_ipv4.h>
#include <linux/skbuff.h>
#include <net/ip.h>
#include <net/tcp.h>

#include "netfilter.h"

#define MODULE_NAME "netfilter"

#define BLOCKED_PORT 666

static struct nf_hook_ops nfho;

// entry & exit funcs

static int __init kmodule_start(void)
{
	int ret;

	printk(KERN_INFO "Initialize 'netfilter' module\n");

	nfho.hook = nf_hook_func;
	nfho.pf = PF_INET;
	nfho.hooknum = NF_INET_PRE_ROUTING;
	nfho.priority = NF_IP_PRI_FIRST;

	ret = nf_register_net_hook(NULL, &nfho);
	if (ret < 0) {
		printk(KERN_ALERT "Can't register the net hook\n");
		return ret;
	}

	return 0;
}

static void __exit kmodule_end(void)
{
	nf_unregister_net_hook(NULL, &nfho);
	printk(KERN_INFO "Module successfully unloaded\n");
}

/* ---------------------------------------------------------------------- */

// Hookfn

static unsigned int nf_hook_func(void *priv, struct sk_buff *skb,
	const struct nf_hook_state *state)
{
//	struct iphdr *iph = (struct iphdr *) skb_network_header(skb);
	struct tcphdr *tcph = (struct tcphdr *) skb_transport_header(skb);

	if (tcph->dest == htons(BLOCKED_PORT)) {
		printk(KERN_INFO " packet [] dropped\n");
		return NF_DROP;
	}

	printk(KERN_INFO " packet [] accepted\n");

	return NF_ACCEPT;
}

/* ---------------------------------------------------------------------- */

module_init(kmodule_start);
module_exit(kmodule_end);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("5aboteur");

