/*
 * hello-6_1.c - The Hello World test module (first part).
 */

#include <linux/module.h>
#include <linux/kernel.h>

int init_module(void)
{
	printk(KERN_INFO "Hello, World! (first part)\n");
	return 0;
}
