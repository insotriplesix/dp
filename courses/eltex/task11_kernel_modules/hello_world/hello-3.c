/*
 * hello-3.c - The Hello World test module with macros & data init.
 */

#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>

static int some_data __initdata = 42;

static int __init kmodule_start(void)
{
	printk(KERN_INFO "Hello, World! Data test: %d\n", some_data);
	return 0;
}

static void __exit kmodule_end(void)
{
	printk(KERN_INFO "Bye, World! End data test..\n");
}

// Macros

module_init(kmodule_start);
module_exit(kmodule_end);
