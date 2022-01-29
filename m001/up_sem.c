/***********************************************
 * module : up_sem
 *
 * Wang Long (wanglong@laoqinren.net)
 **********************************************/
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/rwsem.h>
#include <linux/sched.h>

// insmod up_sem.ko task_address=0xffff880119b40000

static ulong task_address;
module_param(task_address, ulong, 0400);
MODULE_PARM_DESC(mem_address, "The task_struct address to up sem");

static int __init up_sem_init(void)
{
	struct task_struct *task = (struct task_struct *)task_address;
	struct rw_semaphore *sem = &task->mm->mmap_sem;

	printk(KERN_ALERT "[Hello] up_sem \n");
	printk("task->comm = %s\n", task->comm);


	if (down_read_trylock(sem))
	{
		printk("up read for 1: %s\n", task->comm);
		up_read(sem);
		printk("up read for 2: %s\n", task->comm);
		up_read(sem);
	}
	else {
		printk("up write for: %s\n", task->comm);
		up_write(sem);
	}

	return 0;
}

static void __exit up_sem_exit(void)
{
	printk(KERN_ALERT "[Goodbye] up_sem\n");
}

module_init(up_sem_init);
module_exit(up_sem_exit);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("datawolf");
