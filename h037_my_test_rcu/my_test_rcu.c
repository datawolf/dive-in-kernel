/***********************************************
 * module : my_test_rcu
 *
 * Wang Long (w@laoqinren.net)
 **********************************************/
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/kthread.h>
#include <linux/delay.h>
#include <linux/slab.h>

struct foo {
	int a;
	struct rcu_head rcu;
};
static int exit = 0;
static struct foo *g_ptr;

static int myrcu_reader_thread1(void *data) {
	struct foo *p1 = NULL;

	while(!exit) {
		msleep(20);
		rcu_read_lock();
		msleep(200);
		p1 = rcu_dereference(g_ptr);
		if (p1)
			printk("%s: read a = %d\n", __func__, p1->a);
		rcu_read_unlock();
	}

	return 0;
}

static int myrcu_reader_thread2(void *data) {
	struct foo *p2 = NULL;

	while(!exit) {
		msleep(30);
		rcu_read_lock();
		msleep(100);
		p2 = rcu_dereference(g_ptr);
		if (p2)
			printk("%s: read a = %d\n", __func__, p2->a);
		rcu_read_unlock();
	}

	return 0;
}

static void myrcu_del(struct rcu_head *rh) {
	struct foo *p = container_of(rh, struct foo, rcu);

	printk("%s: a = %d\n", __func__, p->a);
	kfree(p);
}

static int myrcu_writer_thread(void *data) {
	struct foo *old;
	struct foo *new_ptr;

	int value = (unsigned long)data;

	while(!exit) {
		msleep(250);
		new_ptr = kmalloc(sizeof(struct foo), GFP_KERNEL);

		old = g_ptr;
		*new_ptr = *old;
		new_ptr->a = value;

		rcu_assign_pointer(g_ptr, new_ptr);
		call_rcu(&old->rcu, myrcu_del);
		printk("%s: write to new %d\n", __func__, value);
		value ++;
	}

	return 0;
}


static int __init my_test_rcu_init(void)
{

	struct task_struct *reader_thread1;
	struct task_struct *reader_thread2;
	struct task_struct *writer_thread;
	int value = 5;
	printk(KERN_ALERT "[Hello] my_test_rcu \n");

	g_ptr = kzalloc(sizeof(struct foo), GFP_KERNEL);

	reader_thread1 = kthread_run(myrcu_reader_thread1, NULL, "rcu_reader1");
	reader_thread2 = kthread_run(myrcu_reader_thread2, NULL, "rcu_reader2");
	writer_thread = kthread_run(myrcu_writer_thread, (void *)(unsigned long)value, "rcu_writer");

	return 0;
}

static void __exit my_test_rcu_exit(void)
{
	printk(KERN_ALERT "[Goodbye] my_test_rcu\n");
	exit = 1;

	msleep(2000);
	if (g_ptr)
		kfree(g_ptr);
}

module_init(my_test_rcu_init);
module_exit(my_test_rcu_exit);
MODULE_LICENSE("GPL");
