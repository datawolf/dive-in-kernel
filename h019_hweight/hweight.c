/***********************************************
 * module : hweight
 *
 * Wang Long (wanglong@laoqinren.net)
 **********************************************/
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>

static int __init hweight_init(void)
{
	printk(KERN_ALERT "[Hello] hweight \n");
	printk(KERN_INFO "hweight_long(33) = %ld\n", hweight_long(33));
	printk(KERN_INFO "hweight_long(32) = %ld\n", hweight_long(32));
	printk(KERN_INFO "hweight_long(52) = %ld\n", hweight_long(52));
	return 0;
}

static void __exit hweight_exit(void)
{
	printk(KERN_ALERT "[Goodbye] hweight\n");
}

module_init(hweight_init);
module_exit(hweight_exit);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("datawolf");
