/*
 * proc666.h
 */

#ifndef __PROC666_H__
#define __PROC666_H__

#include <linux/fs.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/seq_file.h>

static int __init kmodule_start(void);
static void __exit kmodule_end(void);

static int proc666_show(struct seq_file *s, void *v);
static int proc666_open(struct inode *, struct file *);
static int proc666_release(struct inode *, struct file *);

static ssize_t proc666_read(struct file *, char *, size_t, loff_t *);
static ssize_t proc666_write(struct file *, const char *, size_t, loff_t *);

#endif
