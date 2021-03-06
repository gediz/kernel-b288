#include <linux/fs.h>
#include <linux/init.h>
#include <linux/proc_fs.h>
#include <linux/seq_file.h>

static const char *kernel_history = 
#include "history.inc"
;

static int cmdline_proc_show(struct seq_file *m, void *v)
{
	seq_printf(m, "%s\n", kernel_history);
	return 0;
}

static int cmdline_proc_open(struct inode *inode, struct file *file)
{
	return single_open(file, cmdline_proc_show, NULL);
}

static const struct file_operations cmdline_proc_fops = {
	.open		= cmdline_proc_open,
	.read		= seq_read,
	.llseek		= seq_lseek,
	.release	= single_release,
};

static int __init proc_history_init(void)
{
	proc_create("history", 0, NULL, &cmdline_proc_fops);
	return 0;
}
module_init(proc_history_init);
