/***********************************************
 * module : workqueue
 *
 * Wang Long (wanglong@laoqinren.net)
 **********************************************/
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/workqueue.h>

static struct delayed_work dwork;
static struct workqueue_struct *wq = NULL;

static void work_handler(struct work_struct *data)
{
	printk(KERN_ALERT "work handler for work_item in queue helloworkqueue\n");
	queue_delayed_work(wq, &dwork, 3*HZ);
}

static int __init workqueue_init(void)
{
	printk(KERN_ALERT "[Hello] workqueue \n");

	wq = create_singlethread_workqueue("helloworkqueue");

	if (!wq)
		goto err;
	INIT_DELAYED_WORK(&dwork, work_handler);
	queue_delayed_work(wq, &dwork, 3*HZ);

	return 0;
err:
	return -1;
}

static void __exit workqueue_exit(void)
{
	cancel_delayed_work(&dwork);
	destroy_workqueue(wq);
	printk(KERN_ALERT "[Goodbye] workqueue\n");
}

module_init(workqueue_init);
module_exit(workqueue_exit);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("datawolf");
