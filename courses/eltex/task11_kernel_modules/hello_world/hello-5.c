/*
 * hello-5.c - The Hello World module, test cmd line argument passing to it.
 */

#include <linux/module.h>
#include <linux/moduleparam.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/stat.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("5aboteur");
MODULE_DESCRIPTION("test driver");
MODULE_SUPPORTED_DEVICE("test device");

// vars

static short myshort = 42;
static int myint = 1337;
static long mylong = 0x66666L;

// arrays

static char *mystring = "C is the best programming language in the World!";
static int myarray[3] = { -1, 1, 0 };
static int arr_cnt = 3;

// enable passing thru cmd line

module_param(myshort, short, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP);
MODULE_PARM_DESC(myshort, "A short integer");
module_param(myint, int, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP);
MODULE_PARM_DESC(myshort, "An integer");
module_param(mylong, long, S_IRUSR | S_IRGRP);
MODULE_PARM_DESC(mylong, "A long integer");
module_param(mystring, charp, 0000);
MODULE_PARM_DESC(mystring, "A character string");
module_param_array(myarray, int, &arr_cnt, 0000);
MODULE_PARM_DESC(myarray, "An array of integers");

static int __init kmodule_start(void)
{
	int i;
	int arr_sz = sizeof(myarray) / sizeof(myarray[0]);

	printk(KERN_INFO "Hello, World! Arguments test..\n");
	printk(KERN_INFO "myshort: %hd\n", myshort);
	printk(KERN_INFO "myint: %d\n", myint);
	printk(KERN_INFO "mylong: %ld\n", mylong);
	printk(KERN_INFO "mystring: %s\n", mystring);

	printk(KERN_INFO "myarray: {\n");
	for (i = 0; i < arr_sz; i++)
		printk(KERN_INFO "%d ", myarray[i]);
	printk(KERN_INFO "} [%d]\n", i);

	printk(KERN_INFO "Init done!\n");

	return 0;
}

static void __exit kmodule_end(void)
{
	printk(KERN_INFO "Bye, World! End arguments test..\n");
}

// Macros

module_init(kmodule_start);
module_exit(kmodule_end);
