/*
 * sys666.h
 */

#ifndef __SYS666_H__
#define __SYS666_H__

#include <linux/init.h>
#include <linux/fs.h>
#include <linux/kernel.h>
#include <linux/kobject.h>
#include <linux/module.h>
#include <linux/sysfs.h>

static int __init kmodule_start(void);
static void __exit kmodule_end(void);

static ssize_t
sys666_show(struct kobject *kobj, struct kobj_attribute *attr, char *ubuf);

static ssize_t
sys666_store(struct kobject *kobj, struct kobj_attribute *attr, const char *ubuf, size_t count);

#endif
