/***********************************************
 * module : show_max_fds
 *
 * Wang Long (w@laoqinren.net)
 **********************************************/
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/list.h>
#include <linux/sched.h>
#include <linux/sched/task.h>
#include <linux/sched/signal.h>
#include <linux/fdtable.h>

static int __init show_max_fds_init(void)
{
	struct task_struct *pos;
	struct task_struct *leader;
	struct list_head *current_head;
	int count = 0;
	unsigned long fds = 0;
	struct files_struct *files = NULL;

	printk(KERN_ALERT "[Hello] show_max_fds \n");
	current_head = &(current->tasks);
	list_for_each_entry(pos, current_head, tasks)
	{
		rcu_read_lock();
		leader = pos;
		do {
			count++;
			spin_lock(&pos->alloc_lock); 
			files = pos->files;
			if (files) {
				struct fdtable *fdt = files_fdtable(files);
				printk(KERN_INFO "[process %d]: %s's max_fds = %d\n",
					count, pos->comm, fdt->max_fds);
				fds += fdt->max_fds;
			}
			spin_unlock(&pos->alloc_lock);
		} while_each_thread(leader, pos);
		rcu_read_unlock();
	}
	printk(KERN_INFO "The number of process is %d\n", count);
	printk(KERN_INFO "The number of total fds is %ld\n", fds);
	return 0;
}

static void __exit show_max_fds_exit(void)
{
	printk(KERN_ALERT "[Goodbye] show_max_fds\n");
}

module_init(show_max_fds_init);
module_exit(show_max_fds_exit);
MODULE_LICENSE("GPL");
