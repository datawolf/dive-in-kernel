/***********************************************
 * module : test_current
 *
 * Wang Long (w@laoqinren.net)
 **********************************************/
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/sched.h>

static int __init test_current_init(void)
{
	printk(KERN_ERR "[err] test_current \n");
	printk(KERN_WARNING "[warnning] test_current \n");
	printk(KERN_NOTICE "[notice] test_current \n");
	printk(KERN_ALERT "[alert] test_current \n");
	printk(KERN_INFO "[info] test_current \n");
	printk(KERN_DEBUG "[debug] test_current \n");
	printk(KERN_ALERT "comm = %s \n", current->comm);
	return 0;
}

static void __exit test_current_exit(void)
{
	printk(KERN_ALERT "[Goodbye] test_current\n");
}

module_init(test_current_init);
module_exit(test_current_exit);
MODULE_LICENSE("GPL");
