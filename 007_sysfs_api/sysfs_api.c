/***********************************************
 * module : sysfs_api 
 * 
 * datawolf (wanglong@cse.buaa.edu.cn)
 **********************************************/
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/unistd.h>

static int __init sysfs_api_init(void)
{
	printk(KERN_ALERT "[Hello] sysfs_api \n");
	printk(KERN_ALERT "the number of file system in the kernel is %d", sysfs(3));
	return 0;
}

static void __exit sysfs_api_exit(void)
{
	printk(KERN_ALERT "[Goodbye] sysfs_api\n");
}

module_init(sysfs_api_init);
module_exit(sysfs_api_exit);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("datawolf");
