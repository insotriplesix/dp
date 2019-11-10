/*
 * netlink3000.h
 */

#ifndef __NETLINK3000_H__
#define __NETLINK3000_H__

#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/skbuff.h>

static int __init kmodule_start(void);
static void __exit kmodule_end(void);

static void nl3000_msg_hndl(struct sk_buff *sbuf);

#endif
