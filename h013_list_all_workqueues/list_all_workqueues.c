/***********************************************
 * module : list_all_workqueues
 *
 * Wang Long (wanglong@laoqinren.net)
 **********************************************/
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/list.h>
#include <linux/workqueue.h>
#include <linux/kallsyms.h>

// 由于workqueue_struct 结构体没有导出，所以只能打印出队列的个数
struct workqueue_struct_x {
        struct list_head        pwqs;           /* WR: all pwqs of this wq */
        struct list_head        list;           /* PL: list of all workqueues */ // 将系统上所有的workqueue串到一起
};

static int __init list_all_workqueues_init(void)
{
	struct workqueue_struct_x *wqx;
	int count = 0;
	struct list_head *workqueues = (struct list_head *)kallsyms_lookup_name("workqueues");

	printk(KERN_ALERT "[Hello] list_all_workqueues \n");
	list_for_each_entry(wqx, workqueues, list) {
		count++;
		printk(KERN_INFO "[workqueue %d]: name\n",
			count);
	}
	return 0;
}

static void __exit list_all_workqueues_exit(void)
{
	printk(KERN_ALERT "[Goodbye] list_all_workqueues\n");
}

module_init(list_all_workqueues_init);
module_exit(list_all_workqueues_exit);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("datawolf");
