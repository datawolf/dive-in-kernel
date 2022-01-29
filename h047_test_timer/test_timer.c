/***********************************************
 * module : test_timer
 *
 * Wang Long (w@laoqinren.net)
 **********************************************/
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/timer.h>
#include <linux/kthread.h>
#include <linux/delay.h>


static void print_timer(const char *str, struct timer_list *t, int count) {
        printk(KERN_ALERT "\n");
        printk(KERN_ALERT "####%s: %d\n", str, count);
	printk(KERN_ALERT "timer->entry.next = %lx\n", (unsigned long )t->entry.next);
	printk(KERN_ALERT "timer->entry.pprev = %lx\n", (unsigned long )t->entry.pprev);
}

static void timer_callback(struct timer_list *t) {
	int i = 0;
	int j = 0;
	int n = 0;

        t = t;
	for(i = 0; i< 10000; i++) {
		for(j = 0; j < 100000; j++)
			n = i*j;
	}
        printk(KERN_ALERT "XXXXXXXXXXcallback called \n");
}

static int kthread_add_timer(void *arg){
	struct timer_list *t = (struct timer_list *)arg;
	unsigned long expire;
	int count = 0;

	while(!kthread_should_stop()) {
		expire = jiffies + 10;
		if (expire % 2 == 0) {
			mod_timer(t, expire);
			print_timer("mod_timer", t, count);
		}
		else {
			mod_timer_pending(t, expire);
			print_timer("mod_timer_pending", t, count);
		}

		count++;
		msleep(1);
	}

	return 0;
}

static int kthread_del_timer(void *arg){
	int count = 0;
	struct timer_list *t = (struct timer_list *)arg;

	while(!kthread_should_stop()) {
		del_timer(t);
		print_timer("del_timer", t, count);
		count++;
		mod_timer(t, jiffies + 1);
		msleep(1);
	}
	return 0;
}

struct timer_list timer;
struct task_struct *kt;
struct task_struct *kt1;
//struct task_struct *kt2;
//struct task_struct *kt3;

static int __init test_timer_init(void)
{
	printk(KERN_ALERT "[Hello] test_timer \n");
	//timer_setup(&timer, timer_callback, TIMER_PINNED);
	timer_setup(&timer, timer_callback, 0);

	kt = kthread_run(kthread_add_timer, (void *)&timer, "add_timer");
	if (IS_ERR(kt)) {
		printk(KERN_ALERT "create add_timer thread failed\n");
		return -1;
	}

//	kt2 = kthread_run(kthread_add_timer, (void *)&timer, "add_timer");
//	if (IS_ERR(kt)) {
//		printk(KERN_ALERT "create add_timer thread failed\n");
//		return -1;
//	}

	kt1 = kthread_run(kthread_del_timer, (void*)&timer, "del_timer");
	if (IS_ERR(kt1)) {
		printk(KERN_ALERT "create del_timer thread failed\n");
		return -1;
	}

//	kt3 = kthread_run(kthread_del_timer, (void*)&timer, "del_timer");
//	if (IS_ERR(kt1)) {
//		printk(KERN_ALERT "create del_timer thread failed\n");
//		return -1;
//	}
	return 0;
}

static void __exit test_timer_exit(void)
{
	printk(KERN_ALERT "[Goodbye] test_timer\n");
	del_timer_sync(&timer);
	kthread_stop(kt);
	kthread_stop(kt1);
//	kthread_stop(kt2);
//	kthread_stop(kt3);
}

module_init(test_timer_init);
module_exit(test_timer_exit);
MODULE_LICENSE("GPL");
