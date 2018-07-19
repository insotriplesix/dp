/*
 * sys666.c - A simple sys fs module with R/W capabilities.
 */

#include <linux/fs.h>
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/kobject.h>
#include <linux/module.h>
#include <linux/sysfs.h>
#include <linux/uaccess.h>

#include "sys666.h"

#define MODULE_NAME "sys666"

static struct kobject *sys666_kobj;
static struct kobj_attribute sys666_attr =
	__ATTR(sys666, (S_IWUSR | S_IRUGO), sys666_show, sys666_store);

// entry & exit funcs

static int __init
kmodule_start(void)
{
	int ret;

	printk(KERN_INFO "Initialize 'sys666' module\n");

	sys666_kobj = kobject_create_and_add(MODULE_NAME, NULL);
	if (sys666_kobj == NULL) {
		printk(KERN_ALERT "kobject_create_and_add() failed\n");
		return -ENOMEM;
	}

	ret = sysfs_create_file(sys666_kobj, &sys666_attr.attr);
	if (ret != 0) {
		printk(KERN_ALERT "sysfs_create_file() failed with %d\n", ret);
		return ret;
	}

	return 0;
}

static void __exit
kmodule_end(void)
{
	kobject_put(sys666_kobj);
	printk(KERN_INFO "Module successfully unloaded\n");
}

/* ---------------------------------------------------------------------- */

#define MSGSIZ 256

static char kbuf[MSGSIZ] =
	"Isa sysfs w/ 666 stuff in it.. u alive & not crashd?\n";

// R/W handling

static ssize_t
sys666_show(struct kobject *kobj, struct kobj_attribute *attr, char *ubuf)
{
	ssize_t rbytes;

	if (ubuf == NULL) {
		printk(KERN_ALERT " 'ubuf' is NULL\n");
		return -EBADMSG;
	}

	rbytes = sprintf(ubuf, "%s", kbuf);

	printk(KERN_INFO " %zu bytes read;\n returned message from <%s>: %s\n",
		rbytes, MODULE_NAME, kbuf);

	return rbytes;
}

static ssize_t
sys666_store(struct kobject *kobj, struct kobj_attribute *attr, const char *ubuf, size_t count)
{
	ssize_t wbytes;

	// nothing to do
	if (count == 0)
		return 0;

	if (ubuf == NULL) {
		printk(KERN_ALERT " 'ubuf' is NULL\n");
		return -EBADMSG;
	}

	if (count > MSGSIZ) {
		printk(KERN_ALERT " input message too long\n");
		return -EMSGSIZE;
	}

	wbytes = sprintf(kbuf, "%s", ubuf);

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
