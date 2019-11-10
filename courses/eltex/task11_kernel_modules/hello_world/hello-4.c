/*
 * hello-4.c - The Hello World test module with macros & LICENSE stuff.
 */

#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>

#define DRIVER_AUTHOR "5aboteur"
#define DRIVER_DESC "HelloWorld driver"

static int __init kmodule_start(void)
{
	printk(KERN_INFO "Hello, World! License test..\n");
	return 0;
}

static void __exit kmodule_end(void)
{
	printk(KERN_INFO "Bye, World! End license test..\n");
}

// Macros

module_init(kmodule_start);
module_exit(kmodule_end);

MODULE_LICENSE("GPL");
MODULE_AUTHOR(DRIVER_AUTHOR);
MODULE_DESCRIPTION(DRIVER_DESC);
MODULE_SUPPORTED_DEVICE("testdevice");
