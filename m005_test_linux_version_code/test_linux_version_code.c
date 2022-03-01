/***********************************************
 * module : test_linux_version_code
 *
 * Wang Long (w@laoqinren.net)
 **********************************************/
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/version.h>
#include <linux/vermagic.h>

static int __init test_linux_version_code_init(void)
{
	printk(KERN_ALERT "[Hello] test_linux_version_code \n");
	printk(KERN_ALERT "[Hello] LINUX_VERSION_CODE= %d\n", LINUX_VERSION_CODE);
	printk(KERN_ALERT "[Hello] UTS_RELEASE= %s\n", UTS_RELEASE);
	return 0;
}

static void __exit test_linux_version_code_exit(void)
{
	printk(KERN_ALERT "[Goodbye] test_linux_version_code\n");
}

module_init(test_linux_version_code_init);
module_exit(test_linux_version_code_exit);
MODULE_LICENSE("GPL");
