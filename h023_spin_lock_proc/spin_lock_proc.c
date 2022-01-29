/***********************************************
 * module : spin_lock_proc
 *
 * Wang Long (wanglong@laoqinren.net)
 **********************************************/
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/proc_fs.h>
#include <linux/uaccess.h>
#include <linux/seq_file.h>

#define PROC_FILE  "spinlock"

spinlock_t mytest_spinlock;
EXPORT_SYMBOL(mytest_spinlock);

static int spinlock_proc_show(struct seq_file *m, void *v) 
{
        seq_printf(m, "0x%x\n",mytest_spinlock.rlock.raw_lock.val.counter );
        return 0;
}

static int spinlock_proc_open(struct inode *inode, struct file *file)
{
        return single_open(file, spinlock_proc_show, NULL);
}

static const struct file_operations spinlock_proc_fops = { 
        .open           = spinlock_proc_open,
        .read           = seq_read,
        .llseek         = seq_lseek,
        .release        = single_release,
};

static int __init spin_lock_proc_init(void)
{
	struct proc_dir_entry *pe;
	printk(KERN_ALERT "[Hello] spin_lock_proc \n");

	spin_lock_init(&mytest_spinlock);
	pe = proc_create(PROC_FILE, 0644, NULL, &spinlock_proc_fops);
	if (!pe)
		return -ENOMEM;
	return 0;
}

static void __exit spin_lock_proc_exit(void)
{
	printk(KERN_ALERT "[Goodbye] spin_lock_proc\n");
	remove_proc_entry(PROC_FILE, NULL);
}

module_init(spin_lock_proc_init);
module_exit(spin_lock_proc_exit);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("datawolf");
