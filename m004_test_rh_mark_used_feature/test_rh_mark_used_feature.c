/***********************************************
 * module : test_rh_mark_used_feature
 *
 * Wang Long (w@laoqinren.net)
 **********************************************/
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/rh_features.h>

static int __init test_rh_mark_used_feature_init(void)
{
	printk(KERN_ALERT "[Hello] test_rh_mark_used_feature \n");
	printk(KERN_ALERT "%ld", rh_mark_used_feature("Feature/three"));
	printk(KERN_ALERT "%ld", rh_mark_used_feature("Feature/three"));
	return 0;
}

static void __exit test_rh_mark_used_feature_exit(void)
{
	printk(KERN_ALERT "[Goodbye] test_rh_mark_used_feature\n");
}

module_init(test_rh_mark_used_feature_init);
module_exit(test_rh_mark_used_feature_exit);
MODULE_LICENSE("GPL");
