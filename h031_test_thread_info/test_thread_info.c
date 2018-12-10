/***********************************************
 * module : test_thread_info
 *
 * Wang Long (w@laoqinren.net)
 **********************************************/
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/sched.h>

static int __init test_thread_info_init(void)
{
	struct thread_info *ti = NULL;
	struct task_struct *head = NULL;
	struct task_struct *tmp = NULL;

	printk(KERN_ALERT "[Hello] test_thread_info \n");
	ti = (struct thread_info*)((unsigned long)&ti & ~(THREAD_SIZE - 1));
	head = ti->task;
	tmp = head;

	printk("kernel stack size = %lx\n", THREAD_SIZE);
	do {
		printk("name is %s\n", tmp->comm);
		tmp = container_of(tmp->tasks.next, struct task_struct, tasks);
	}while(tmp != head);

	return 0;
}

static void __exit test_thread_info_exit(void)
{
	printk(KERN_ALERT "[Goodbye] test_thread_info\n");
}

module_init(test_thread_info_init);
module_exit(test_thread_info_exit);
MODULE_LICENSE("GPL");
