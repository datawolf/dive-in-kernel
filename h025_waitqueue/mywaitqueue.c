/***********************************************
 * module : mywaitqueue
 *
 * Wang Long (w@laoqinren.net)
 **********************************************/
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/proc_fs.h>
#include <linux/seq_file.h>
#include <linux/wait.h>
#include <linux/kthread.h>

static int read_count = 0;
static struct task_struct *wait_thread;
DECLARE_WAIT_QUEUE_HEAD(test_waitqueue);
static int wait_queue_flag = 0;

static int my_waitqueue_show(struct seq_file *m, void *v)
{
	printk(KERN_ALERT "Read function\n");
	seq_printf(m, "read_count = %d\n", read_count);
	wait_queue_flag = 1;
	wake_up_interruptible(&test_waitqueue);
	return 0;
}

static int my_waitqueue_open(struct inode *inode, struct file *filp)
{
	return single_open(filp, my_waitqueue_show, NULL);
}

static struct file_operations test_wait_queue_fops = {
	.open		= my_waitqueue_open,
	.read		= seq_read,
	.llseek		= seq_lseek,
	.release	= single_release,
};

static int wait_function(void *unused)
{
	while(1) {
		printk(KERN_ALERT "Waiting For Event...\n");
		wait_event_interruptible(test_waitqueue, wait_queue_flag != 0);
		if (wait_queue_flag == 2) {
			printk(KERN_ALERT "Event Came From Exit Function\n");
			return 0;
		}
		printk(KERN_ALERT "Event Came From Read Function - %d\n", ++read_count);
		wait_queue_flag = 0;
	}

	return 0;
}

static int __init mywaitqueue_init(void)
{
	struct proc_dir_entry *pe;

	printk(KERN_ALERT "[Hello] mywaitqueue \n");
	pe = proc_create("test_wait_queue", 0644, NULL, &test_wait_queue_fops);
	if (!pe)
		return -ENOMEM;

	// initialize wait queue
	init_waitqueue_head(&test_waitqueue);

	// Create the kernel thread with name "MyWaitThread"
	wait_thread = kthread_create(wait_function, NULL, "MyWaitThread");
	if (wait_thread) {
		printk(KERN_ALERT "Thread created successfully\n");
		wake_up_process(wait_thread);
	} else {
		printk(KERN_ALERT "Thread creation failed\n");
	}

	return 0;
}

static void __exit mywaitqueue_exit(void)
{
	wait_queue_flag = 2;
	wake_up_interruptible(&test_waitqueue);
	printk(KERN_ALERT "[Goodbye] mywaitqueue\n");
	remove_proc_entry("test_wait_queue", NULL);
}

module_init(mywaitqueue_init);
module_exit(mywaitqueue_exit);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("datawolf");


