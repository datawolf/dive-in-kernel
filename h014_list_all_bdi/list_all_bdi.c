/***********************************************
 * module : list_all_bdi
 *
 * Wang Long (wanglong@laoqinren.net)
 **********************************************/
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/list.h>
#include <linux/kallsyms.h>
#include <linux/backing-dev.h>
#include <linux/device.h>
#include <linux/atomic.h>

#define K(x) ((x) << ( 12 - 10))

static int __init list_all_bdi_init(void)
{
	struct list_head *list_bdi;
	struct backing_dev_info *bdi;
	atomic_long_t *num;

	spinlock_t * lock = (spinlock_t *)kallsyms_lookup_name("bdi_lock");
	list_bdi = (struct list_head *)kallsyms_lookup_name("bdi_list");
	num = (atomic_long_t *)kallsyms_lookup_name("bdi_seq");

	printk(KERN_ALERT "[Hello] list_all_bdi \n");
	printk(KERN_ALERT "The number of bdi is %ld\n", atomic_long_read(num)); //一般为0
	spin_lock(lock);
	list_for_each_entry(bdi, list_bdi, bdi_list) {
		// device id
		printk(KERN_INFO "%s\n", bdi->name);
		printk(KERN_INFO "\tra_pages = %lu\n", bdi->ra_pages);
		printk(KERN_INFO "\tstate = 0x%lx\n", bdi->state);
		printk(KERN_INFO "\tbandwith = %lu kBps\n", (unsigned long) K(bdi->write_bandwidth));
	}
	spin_unlock(lock);
	return 0;
}

static void __exit list_all_bdi_exit(void)
{
	printk(KERN_ALERT "[Goodbye] list_all_bdi\n");
}

module_init(list_all_bdi_init);
module_exit(list_all_bdi_exit);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("datawolf");
