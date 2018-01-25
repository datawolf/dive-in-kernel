/***********************************************
 * module : semaphore_test
 *
 * Wang Long (wanglong@laoqinren.net)
 **********************************************/
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/rwsem.h>
#include <linux/atomic.h>

static int __init semaphore_test_init(void)
{
	DECLARE_RWSEM(rwsem);
	int ret;

	printk(KERN_ALERT "[Hello] semaphore_test \n");

	printk(KERN_ALERT "init:      rwsem.count = 0x%016lx\n", atomic_long_read(&rwsem.count));

	down_read(&rwsem);
	printk(KERN_ALERT "down_read: rwsem.count = 0x%016lx\n", atomic_long_read(&rwsem.count));

	down_read(&rwsem);
	printk(KERN_ALERT "down_read: rwsem.count = 0x%016lx\n", atomic_long_read(&rwsem.count));

	down_read(&rwsem);
	printk(KERN_ALERT "down_read: rwsem.count = 0x%016lx\n", atomic_long_read(&rwsem.count));

	up_read(&rwsem);
	printk(KERN_ALERT "up_read:   rwsem.count = 0x%016lx\n", atomic_long_read(&rwsem.count));

	up_read(&rwsem);
	printk(KERN_ALERT "up_read:   rwsem.count = 0x%016lx\n", atomic_long_read(&rwsem.count));

	up_read(&rwsem);
	printk(KERN_ALERT "up_read:   rwsem.count = 0x%016lx\n", atomic_long_read(&rwsem.count));

	down_write(&rwsem);
	printk(KERN_ALERT "down_write:rwsem.count = 0x%016lx\n", atomic_long_read(&rwsem.count));

	up_write(&rwsem);
	printk(KERN_ALERT "up_write:  rwsem.count = 0x%016lx\n", atomic_long_read(&rwsem.count));

	ret = down_read_trylock(&rwsem);
	if (ret == 1) {
		printk(KERN_ALERT "down_read_trylock: rwsem.count = 0x%016lx\n", atomic_long_read(&rwsem.count));
		up_read(&rwsem);
		printk(KERN_ALERT "up_read:           rwsem.count = 0x%016lx\n", atomic_long_read(&rwsem.count));
	}

	ret = down_write_trylock(&rwsem);
	if (ret == 1) {
		printk(KERN_ALERT "down_write_trylock:rwsem.count = 0x%016lx\n", atomic_long_read(&rwsem.count));
		up_write(&rwsem);
		printk(KERN_ALERT "up_write:          rwsem.count = 0x%016lx\n", atomic_long_read(&rwsem.count));
	}


	down_read(&rwsem);
	printk(KERN_ALERT "down_read: rwsem.count = 0x%016lx\n", atomic_long_read(&rwsem.count));

	down_read(&rwsem);
	printk(KERN_ALERT "down_read: rwsem.count = 0x%016lx\n", atomic_long_read(&rwsem.count));

	down_read(&rwsem);
	printk(KERN_ALERT "down_read: rwsem.count = 0x%016lx\n", atomic_long_read(&rwsem.count));

	ret = down_write_trylock(&rwsem);
	if (ret == 1) {
		printk(KERN_ALERT "down_write_trylock:rwsem.count = 0x%016lx\n", atomic_long_read(&rwsem.count));
		up_write(&rwsem);
		printk(KERN_ALERT "up_write:          rwsem.count = 0x%016lx\n", atomic_long_read(&rwsem.count));
	} else {
		printk(KERN_ALERT "down_write_trylock failed: rwsem.count = 0x%016lx\n", atomic_long_read(&rwsem.count));
	}


	return 0;
}

static void __exit semaphore_test_exit(void)
{
	printk(KERN_ALERT "[Goodbye] semaphore_test\n");
}

module_init(semaphore_test_init);
module_exit(semaphore_test_exit);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("datawolf");
