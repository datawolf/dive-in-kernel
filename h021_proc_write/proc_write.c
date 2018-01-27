/***********************************************
 * module : proc_write
 *
 * Wang Long (wanglong@laoqinren.net)
 **********************************************/
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/proc_fs.h>
#include <linux/init.h>
#include <linux/seq_file.h>
#include <linux/uaccess.h>
#include <linux/string.h>

#define PROC_FILE  "proc_write"

char cmd[20];

static int cmd_show(struct seq_file *m, void *v)
{
	seq_printf(m, "%s(%zu)\n", cmd, strlen(cmd));
	return 0;
}

static ssize_t cmd_write(struct file *file, const char __user *buf,
			size_t count, loff_t *offs)
{
	// count 的值为输入字符串的长度+1，即字符串后面会添加一个`\n`
	if (count < 1 || count > 20 || *offs)
		return -EINVAL;

	if (copy_from_user(cmd, buf, count))
		return -EFAULT;

	// 在处理字符串时，需要将`\n`替换成`\0`
	cmd[count-1] = '\0';

	printk(KERN_ALERT "count = %zu\n", count);
	return count;
}

static int cmd_open(struct inode *inode, struct file *filp)
{
	return single_open(filp, cmd_show, NULL);
}

static const struct file_operations cmd_fops = {
	.open		= cmd_open,
	.read		= seq_read,
	.write		= cmd_write,
	.llseek		= seq_lseek,
	.release	= single_release,
};

static int __init proc_write_init(void)
{
	struct proc_dir_entry *pe;
	printk(KERN_ALERT "[Hello] proc_write \n");

	pe = proc_create(PROC_FILE, 0644, NULL, &cmd_fops);
	if (!pe)
		return -ENOMEM;

	return 0;
}

static void __exit proc_write_exit(void)
{
	printk(KERN_ALERT "[Goodbye] proc_write\n");
	remove_proc_entry(PROC_FILE, NULL);
}

module_init(proc_write_init);
module_exit(proc_write_exit);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("datawolf");
