/***********************************************
 * module : dynamic_printk
 *
 * Wang Long (w@laoqinren.net)
 **********************************************/
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/kthread.h>
#include <linux/delay.h>

static struct task_struct *mythread;
static int exit = 0;
static int my_function(void *unused)
{
	while(!exit) {
		pr_debug("just print this message\n");
		msleep(2000);
	}

	return 0;
}
static int __init dynamic_printk_init(void)
{
	printk(KERN_ALERT "[Hello] dynamic_printk \n");

	// Create the kernel thread with name "MyThread"
	mythread = kthread_create(my_function, NULL, "MyThread");
	if (mythread) {
		printk(KERN_ALERT "Thread created successfully\n");
		wake_up_process(mythread);
	} else {
		printk(KERN_ALERT "Thread creation failed\n");
	}

	return 0;
}

static void __exit dynamic_printk_exit(void)
{
	exit = 1;
	msleep(3000);
	printk(KERN_ALERT "[Goodbye] dynamic_printk\n");
}

module_init(dynamic_printk_init);
module_exit(dynamic_printk_exit);
MODULE_LICENSE("GPL");
