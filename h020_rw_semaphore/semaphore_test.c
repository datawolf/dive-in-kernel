/***********************************************
 * module : semaphore_test
 *
 * Wang Long (wanglong@laoqinren.net)
 **********************************************/
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/rwsem.h>
#include <linux/atomic.h>
#include <linux/proc_fs.h>
#include <linux/seq_file.h>
#include <linux/uaccess.h>
#include <linux/string.h>
#include <linux/list.h>
#include <linux/kthread.h>
#include <linux/sched.h>
#include <linux/delay.h>

static DECLARE_RWSEM(rwsem);
#define PROC_FILE  "rwsem_test"

enum rwsem_waiter_type {
	RWSEM_WAITING_FOR_WRITE,
	RWSEM_WAITING_FOR_READ
};

struct rwsem_waiter {
	struct list_head list;
	struct task_struct *task;
	enum rwsem_waiter_type type;
};

static int rwsem_show(struct seq_file *m, void *v)
{
	struct rwsem_waiter *waiter;
	seq_printf(m, "semaphore.count: 0x%016lx\n", atomic_long_read(&rwsem.count));

	if (!slist_empty(&rwsem.wait_list)) {
		// The first waiter
		waiter = list_entry(rwsem.wait_list.next, struct rwsem_waiter, list);
		seq_printf(m, "\twait list: comm = %s, type = %s\n",
					waiter->task->comm,
					waiter->type == 0 ? "RWSEM_WAITING_FOR_WRITE" : "RWSEM_WAITING_FOR_READ");

		// The rest waiter if have
		list_for_each_entry(waiter, rwsem.wait_list.next, list) {
			seq_printf(m, "\twait list: comm = %s, type = %s\n",
					waiter->task->comm,
					waiter->type == 0 ? "RWSEM_WAITING_FOR_WRITE" : "RWSEM_WAITING_FOR_READ");
		}
	}
	return 0;
}

int downread(void *data) {
//	char *name = (char *)data;
	down_read(&rwsem);
	do_exit(0);
}
int upread(void *data) {
//	char *name = (char *)data;
	up_read(&rwsem);
	do_exit(0);
}

int downwrite(void *data) {
//	char *name = (char *)data;
	down_write(&rwsem);
	do_exit(0);
}

int upwrite(void *data) {
//	char *name = (char *)data;
	up_write(&rwsem);
	do_exit(0);
}

static ssize_t rwsem_write(struct file *file, const char __user *buf,
			size_t count, loff_t *offs)
{
	struct task_struct *task = NULL;
	char cmd[40];

	// up_read 8
	// down_read 10
	// up_write 9
	// down write 11
	if (*offs)
		return -EINVAL;

	if (copy_from_user(cmd, buf, count))
		return -EFAULT;

	cmd[count-1] = '\0';

	if (strncmp(cmd, "down_read", 9) == 0) {
		task = kthread_create(downread, cmd+10, cmd+10);
		if (IS_ERR(task)) {
			return -EFAULT;
		}
		wake_up_process(task);
	}
	else if (strncmp(cmd, "up_read", 7) == 0) {
		task = kthread_create(upread, cmd+8, cmd+8);
		if (IS_ERR(task)) {
			return -EFAULT;
		}
		wake_up_process(task);
	}
	else if (strncmp(cmd, "down_write", 10) == 0) {
		task = kthread_create(downwrite, cmd+11, cmd+11);
		if (IS_ERR(task)) {
			return -EFAULT;
		}
		wake_up_process(task);
	}
	else if (strncmp(cmd, "up_write", 8) == 0) {
		task = kthread_create(upwrite, cmd+9, cmd+9);
		if (IS_ERR(task)) {
			return -EFAULT;
		}
		wake_up_process(task);
	}

	return count;
}

static int rwsem_open(struct inode *inode, struct file *filp)
{
	return single_open(filp, rwsem_show, NULL);
}

static const struct file_operations rwsem_fops = {
	.open		= rwsem_open,
	.read		= seq_read,
	.write		= rwsem_write,
	.llseek		= seq_lseek,
	.release	= single_release,
};

static int __init semaphore_test_init(void)
{
	struct proc_dir_entry *pe;

	pe = proc_create(PROC_FILE, 0644, NULL, &rwsem_fops);
	if (!pe)
		return -ENOMEM;

	return 0;
}

static void __exit semaphore_test_exit(void)
{
	printk(KERN_ALERT "[Goodbye] semaphore_test\n");
	remove_proc_entry(PROC_FILE, NULL);
}

module_init(semaphore_test_init);
module_exit(semaphore_test_exit);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("datawolf");
