/***********************************************
 * module : list_all_percpu_counter
 *
 * Wang Long (wanglong@laoqinren.net)
 **********************************************/
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/percpu_counter.h>
#include <linux/kallsyms.h>
#include <linux/list.h>
#include <linux/spinlock.h>

static int __init list_all_percpu_counter_init(void)
{
	struct list_head *percpu_counters = NULL;
	spinlock_t *percpu_counters_lock = NULL;
	struct percpu_counter *fbc;
	int count = 0;

	percpu_counters = (struct list_head *)kallsyms_lookup_name("percpu_counters");
	percpu_counters_lock = (spinlock_t *)kallsyms_lookup_name("percpu_counters_lock");

	printk(KERN_ALERT "[Hello] list_all_percpu_counter \n");

	spin_lock_irq(percpu_counters_lock);
	list_for_each_entry(fbc, percpu_counters, list) {
		count++;
		printk(KERN_INFO "[%d] %ld\n", count, (long)percpu_counter_sum(fbc));
	}
	spin_unlock_irq(percpu_counters_lock);

	return 0;
}

static void __exit list_all_percpu_counter_exit(void)
{
	printk(KERN_ALERT "[Goodbye] list_all_percpu_counter\n");
}

module_init(list_all_percpu_counter_init);
module_exit(list_all_percpu_counter_exit);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("datawolf");
