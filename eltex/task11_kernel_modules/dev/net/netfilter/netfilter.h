/*
 * netfilter.h
 */

#ifndef __NETFILTER_H__
#define __NETFILTER_H__

#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/netfilter.h>
#include <linux/skbuff.h>

static int __init kmodule_start(void);
static void __exit kmodule_end(void);

static unsigned int nf_hook_func(void *priv, struct sk_buff *skb,
	const struct nf_hook_state *state);


#endif
