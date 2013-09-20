/***********************************************
 * module : hello 
 * 
 * datawolf (wanglong@cse.buaa.edu.cn)
 **********************************************/
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>

static int __init hello_init(void)
{
	printk(KERN_ALERT "[Hello] hello \n");
	return 0;
}

static void __exit hello_exit(void)
{
	printk(KERN_ALERT "[Goodbye] hello\n");
}

module_init(hello_init);
module_exit(hello_exit);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("datawolf");
