/***********************************************
 * module : list_all_process
 *
 * Wang Long (wanglong@laoqinren.net)
 **********************************************/
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/list.h>
#include <linux/sched.h>

static int __init list_all_process_init(void)
{
	struct task_struct *pos;
	struct list_head *current_head;
	int count = 0;

	printk(KERN_ALERT "[Hello] list_all_process \n");
	current_head = &(current->tasks);
	list_for_each_entry(pos, current_head, tasks)
	{
		count++;
		printk(KERN_INFO "[process %d]: %s's pid is %d\n",
			count, pos->comm, pos->pid);
	}
	printk(KERN_INFO "The number of process is %d\n", count);
	return 0;
}

static void __exit list_all_process_exit(void)
{
	printk(KERN_ALERT "[Goodbye] list_all_process\n");
}

module_init(list_all_process_init);
module_exit(list_all_process_exit);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("datawolf");
