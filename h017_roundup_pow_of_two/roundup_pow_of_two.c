/***********************************************
 * module : roundup_pow_of_two
 *
 * Wang Long (wanglong@laoqinren.net)
 **********************************************/
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/log2.h>

static int __init roundup_pow_of_two_init(void)
{
	const unsigned long period = roundup_pow_of_two(3 * HZ);

	printk(KERN_ALERT "[Hello] roundup_pow_of_two \n");
	printk(KERN_INFO "HZ = %d\n", HZ);
	printk(KERN_INFO "roundup_pow_of_two(3 * HZ) = %lu\n", period);
	printk(KERN_INFO "rounddown_pow_of_two(3 * HZ) = %lu\n", rounddown_pow_of_two(3 * HZ));
	printk(KERN_INFO "ilog2(period) = %d\n", ilog2(period));
	return 0;
}

static void __exit roundup_pow_of_two_exit(void)
{
	printk(KERN_ALERT "[Goodbye] roundup_pow_of_two\n");
}

module_init(roundup_pow_of_two_init);
module_exit(roundup_pow_of_two_exit);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("datawolf");
