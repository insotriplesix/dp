/*
 * hello-2.c - The Hello World test module with macros.
 */

#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>

static int __init kmodule_start(void)
{
	printk(KERN_INFO "Hello, World! Start macros test..\n");
	return 0;
}

static void __exit kmodule_end(void)
{
	printk(KERN_INFO "Bye, World! End macros test..\n");
}

// Macros

module_init(kmodule_start);
module_exit(kmodule_end);
