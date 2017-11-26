/***********************************************
 * module : percpu_refcount
 *
 * Wang Long (wanglong@laoqinren.net)
 **********************************************/
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/percpu-refcount.h>

static void test_release(struct percpu_ref *ref)
{
	printk(KERN_INFO "percpu_refcount release called\n");
}

struct test {
	struct percpu_ref refcnt;
	int flags;
};

static struct test test;

static int __init percpu_refcount_init(void)
{
	int ret;

	ret = percpu_ref_init(&test.refcnt, test_release, 0, GFP_KERNEL);
	if (ret)
		goto out_free_ref;

	percpu_ref_get(&test.refcnt);
	percpu_ref_get(&test.refcnt);

	//percpu_ref_kill(&test.refcnt);
	//只有调用了percpu_ref_kill后，后续的percpu_ref_put才会检测是否为0
	// 只有为0时，才会调用test_release方法。
	percpu_ref_put(&test.refcnt);
	percpu_ref_put(&test.refcnt);
out_free_ref:
	printk(KERN_ALERT "[Hello] percpu_refcount \n");
	return ret;;
}

static void __exit percpu_refcount_exit(void)
{

	percpu_ref_exit(&test.refcnt);
	printk(KERN_ALERT "[Goodbye] percpu_refcount\n");
}

module_init(percpu_refcount_init);
module_exit(percpu_refcount_exit);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("datawolf");
