/***********************************************
 * module : test_module 
 * 
 * datawolf (wanglong@cse.buaa.edu.cn)
 **********************************************/
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>

static int __init test_module_init(void)
{
	printk(KERN_ALERT "[Hello] test_module \n");
	return 0;
}

static void __exit test_module_exit(void)
{
	printk(KERN_ALERT "[Goodbye] test_module\n");
}

module_init(test_module_init);
module_exit(test_module_exit);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("datawolf");
