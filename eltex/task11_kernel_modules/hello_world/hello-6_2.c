/*
 * hello-6_2.c - The Hello World test module (second part).
 */

#include <linux/module.h>
#include <linux/kernel.h>

void cleanup_module(void)
{
	printk(KERN_INFO "Bye, World! (second part)\n");
}
