/*
 * oblivion.h
 */

#ifndef __OBLIVION_H__
#define __OBLIVION_H__

#include <linux/fs.h>
#include <linux/kernel.h>
#include <linux/module.h>

static int __init kmodule_start(void);
static void __exit kmodule_end(void);

static int device_open(struct inode *, struct file *);
static int device_release(struct inode *, struct file *);
static ssize_t device_read(struct file *, char *, size_t, loff_t *);
static ssize_t device_write(struct file *, const char *, size_t, loff_t *);

#endif
