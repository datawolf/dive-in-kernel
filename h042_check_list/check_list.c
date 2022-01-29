/***********************************************
 * module : check_list
 *
 * Wang Long (w@laoqinren.net)
 **********************************************/
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/list.h>


LIST_HEAD(bdi_list);

struct test {
	struct list_head bdi_list;
	int flags;
};

static int __init check_list_init(void)
{
	struct test test1, test2;

	printk(KERN_ALERT "[Hello] check_list \n");

	printk(KERN_ALERT "&bdi_list = %px", &bdi_list);
	printk(KERN_ALERT "bdi_list.next = %px", bdi_list.next);
	printk(KERN_ALERT "bdi_list.prev = %px", bdi_list.prev);
	list_add(&test1.bdi_list, &bdi_list);

	printk(KERN_ALERT "add test1XXXXXXXXXXXXXXXXXX \n");
	printk(KERN_ALERT "&bdi_list = %px", &bdi_list);
	printk(KERN_ALERT "bdi_list.next = %px", bdi_list.next);
	printk(KERN_ALERT "bdi_list.prev = %px", bdi_list.prev);

	list_add(&test2.bdi_list, &bdi_list);
	printk(KERN_ALERT "add test2 XXXXXXXXXXXXXXXXXX \n");
	printk(KERN_ALERT "&bdi_list = %px", &bdi_list);
	printk(KERN_ALERT "bdi_list.next = %px", bdi_list.next);
	printk(KERN_ALERT "bdi_list.prev = %px", bdi_list.prev);

	list_del(&test1.bdi_list);
	printk(KERN_ALERT "del test1XXXXXXXXXXXXXXXXXX \n");
	printk(KERN_ALERT "&bdi_list = %px", &bdi_list);
	printk(KERN_ALERT "bdi_list.next = %px", bdi_list.next);
	printk(KERN_ALERT "bdi_list.prev = %px", bdi_list.prev);

	list_del(&test2.bdi_list);
	printk(KERN_ALERT "del test2XXXXXXXXXXXXXXXXXX \n");
	printk(KERN_ALERT "&bdi_list = %px", &bdi_list);
	printk(KERN_ALERT "bdi_list.next = %px", bdi_list.next);
	printk(KERN_ALERT "bdi_list.prev = %px", bdi_list.prev);
	return 0;
}

static void __exit check_list_exit(void)
{
	printk(KERN_ALERT "[Goodbye] check_list\n");
}

module_init(check_list_init);
module_exit(check_list_exit);
MODULE_LICENSE("GPL");
