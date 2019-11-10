/*
 * proc666.c - A simple proc fs module with R/W capabilities.
 */

#include <linux/fs.h>
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/proc_fs.h>
#include <linux/seq_file.h>
#include <linux/uaccess.h>

#include "proc666.h"

#define MODULE_NAME "proc666"

static struct file_operations proc666_fops = {
	.owner = THIS_MODULE,
	.open = proc666_open,
	.release = proc666_release,
	.read = proc666_read,
	.write = proc666_write
};

// entry & exit funcs

static int __init
kmodule_start(void)
{
	printk(KERN_INFO "Initialize 'proc666' module\n");
	proc_create(MODULE_NAME, S_IFREG | S_IRUSR | S_IWUSR, NULL, &proc666_fops);
	return 0;
}

static void __exit
kmodule_end(void)
{
	remove_proc_entry(MODULE_NAME, NULL);
	printk(KERN_INFO "Module successfully unloaded\n");
}

/* ---------------------------------------------------------------------- */

#define MSGSIZ 256

static char kbuf[MSGSIZ] =
	"You`re in some proc things w/ 666 dark stuff inside.. will u survive & not crash?\n";

// R/W handling

static int
proc666_show(struct seq_file *s, void *v)
{
	seq_puts(s, " * * * WELCOME TO PROC 666 * * *\n\n");
	seq_puts(s, " 2: 0b1010011010\n 8: 0o1232\n 10: 666\n 16: 0x29A\n\n");
	seq_puts(s, "\t * * * FAREWELL * * *\n");
	return 0;
}

static int
proc666_open(struct inode *inod, struct file *filp)
{
	printk(KERN_INFO " >>> in\n");
	return single_open(filp, proc666_show, NULL);
}

static int
proc666_release(struct inode *inod, struct file *filp)
{
	printk(KERN_INFO " <<< out\n");
	return single_release(inod, filp);
}

static ssize_t
proc666_read(struct file *filp, char __user *ubuf, size_t count, loff_t *offp)
{
	ssize_t rbytes, ret;
	size_t kbuf_len;

	// nothing to do
	if (count == 0 || *offp != 0)
		return 0;

	if (ubuf == NULL) {
		printk(KERN_ALERT " 'ubuf' is NULL\n");
		return -EBADMSG;
	}

	kbuf_len = strlen(kbuf);
	rbytes = (kbuf_len < count) ? kbuf_len : count;

	ret = copy_to_user(ubuf, kbuf, rbytes);
	if (ret > 0) {
		printk(KERN_ALERT " failed to copy data to userspace\n");
		return -EFAULT;
	}

	*offp = rbytes;

	printk(KERN_INFO " %zu bytes read;\n returned message from <%s>: %s\n",
		rbytes, MODULE_NAME, kbuf);

	return rbytes;
}

static ssize_t
proc666_write(struct file *filp, const char __user *ubuf, size_t count, loff_t *offp)
{
	ssize_t wbytes, ret;

	// nothing to do
	if (count == 0 || *offp != 0)
		return 0;

	if (ubuf == NULL) {
		printk(KERN_ALERT " 'ubuf' is NULL\n");
		return -EBADMSG;
	}

	wbytes = (MSGSIZ < count) ? MSGSIZ : count;

	ret = copy_from_user(kbuf, ubuf, wbytes);
	if (ret > 0) {
		printk(KERN_ALERT " failed to copy data from userspace\n");
		return -EFAULT;
	}

	// make sure that string actually ends
	kbuf[((wbytes == MSGSIZ) ? wbytes - 1 : wbytes)] = '\0';

	printk(KERN_INFO " %zu bytes written;\n returned message from <%s>: %s\n",
		wbytes, MODULE_NAME, kbuf);

	return wbytes;
}

/* ---------------------------------------------------------------------- */

module_init(kmodule_start);
module_exit(kmodule_end);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("5aboteur");
