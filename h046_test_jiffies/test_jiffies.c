/***********************************************
 * module : test_jiffies
 *
 * Wang Long (w@laoqinren.net)
 **********************************************/
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>

static int __init test_jiffies_init(void)
{
	printk(KERN_ALERT "[Hello] test_jiffies \n");

	printk(KERN_ALERT "msecs_to_jiffies(10) = %ld\n", msecs_to_jiffies(10));
	return 0;
}

static void __exit test_jiffies_exit(void)
{
	printk(KERN_ALERT "[Goodbye] test_jiffies\n");
}

module_init(test_jiffies_init);
module_exit(test_jiffies_exit);
MODULE_LICENSE("GPL");
