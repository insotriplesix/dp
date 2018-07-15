/*
 * oblivion.c - A simple character device driver with R/W capabilities.
 */

#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/sched.h>
#include <asm/uaccess.h>

// auxiliary

MODULE_LICENSE("GPL");
MODULE_AUTHOR("5aboteur");
MODULE_DESCRIPTION("test character device driver");
MODULE_SUPPORTED_DEVICE("test character device");

// prototypes

static int __init kmodule_start(void);
static void __exit kmodule_end(void);

static int device_open(struct inode *, struct file *);
static int device_release(struct inode *, struct file *);
static ssize_t device_read(struct file *, char *, size_t, loff_t *);
static ssize_t device_write(struct file *, const char *, size_t, loff_t *);

// vars

#define DEVICE_NAME "oblivion"

static int processes_use_dev = 0;
static int major;
static int minor = 0;

static struct file_operations fops = {
	.owner = THIS_MODULE,
	.open = device_open,
	.release = device_release,
	.read = device_read,
	.write = device_write
};

// entry & exit funcs

static int __init kmodule_start(void)
{
	printk(KERN_INFO "Initialize the test character device driver.\n");

	// registering our device
	major = register_chrdev(0, DEVICE_NAME, &fops);

	if (major < 0) {
		printk(KERN_ALERT "Registering char device failed with %d\n", major);
		return major;
	}

	printk(KERN_INFO " ~> Device name: %s\n", DEVICE_NAME);
	printk(KERN_INFO " ~> Major number: %d\n", major);
	printk(KERN_INFO " ~> Minor number: %d\n", minor);

	return 0;
}

static void __exit kmodule_end(void)
{
	// unregistering our device
	unregister_chrdev(major, DEVICE_NAME);

	printk(KERN_INFO "Module successfully unloaded!\n");
}

module_init(kmodule_start);
module_exit(kmodule_end);

/* ============================ */

#define MSGSIZ 256

static char msg[MSGSIZ] = "'TES IV: Oblivion' is the greatest game of our century!";
static char *msgptr;

// R/W handling

static int device_open(struct inode *inod, struct file *filp)
{
	if (processes_use_dev > 0)
		return -EBUSY;

	processes_use_dev++;
	printk(KERN_INFO "Open (%d)\n", processes_use_dev);
//	try_module_get(THIS_MODULE);

	return 0;
}

static int device_release(struct inode *inod, struct file *filp)
{
	processes_use_dev--;
//	module_put(THIS_MODULE);
	printk(KERN_INFO "Closed (%d)\n", processes_use_dev);
	return 0;
}

static ssize_t device_read(struct file *filp, char *buf, size_t len, loff_t *off)
{
	int rbytes, total;

	msgptr = msg;

	if (*msgptr == 0)
		return 0;

	total = (len > MSGSIZ) ? MSGSIZ : len;

	for (rbytes = 0; rbytes < total; rbytes++)
		// send msg data from kernel to the buffer in user space
		put_user(*(msgptr++), buf++);

	printk(KERN_INFO "%d bytes sent, returned message from <%s>: %s\n",
		rbytes, DEVICE_NAME, msg);

	return rbytes;
}

static ssize_t device_write(struct file *filp, const char *buf, size_t len, loff_t *off)
{
	int wbytes, total;

	msgptr = msg;

	if (*msgptr == 0)
		return 0;

	total = (len > MSGSIZ) ? MSGSIZ : len;

	for (wbytes = 0; wbytes < total; wbytes++)
		// get value from user buffer & copy it to the kernel space
		get_user(*(msgptr++), buf++);

	printk(KERN_INFO "%d bytes was written\n", wbytes);

	return wbytes;
}
