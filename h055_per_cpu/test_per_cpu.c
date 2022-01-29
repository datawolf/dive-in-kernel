/***********************************************
 * module : test_per_cpu
 *
 * Wang Long (w@laoqinren.net)
 **********************************************/
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>


static DEFINE_PER_CPU(unsigned long, a);
static DEFINE_PER_CPU(unsigned long, b);


static int watchdog_should_run(void)
{
	return __this_cpu_read(a) != __this_cpu_read(b);
}

static int __init test_per_cpu_init(void)
{
	__this_cpu_write(a, 23333);
	__this_cpu_write(b, 23333);
	printk(KERN_ALERT "[Hello] test_per_cpu : \n");
	printk(KERN_ALERT "watchdog_should_run return : %d\n", watchdog_should_run());
	return 0;
}

static void __exit test_per_cpu_exit(void)
{
	printk(KERN_ALERT "[Goodbye] test_per_cpu\n");
}

module_init(test_per_cpu_init);
module_exit(test_per_cpu_exit);
MODULE_LICENSE("GPL");
