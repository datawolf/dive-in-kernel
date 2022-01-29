/***********************************************
 * module : spin_lock_irq_test
 *
 * Wang Long (wanglong@laoqinren.net)
 **********************************************/
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>

static inline unsigned long get_flag(void)
{
        unsigned long flags;

        /*
         * "=rm" is safe here, because "pop" adjusts the stack before
         * it evaluates its effective address -- this is part of the
         * documented behavior of the "pop" instruction.
         */
        asm volatile("# __raw_save_flags\n\t"
                     "pushf ; pop %0"
                     : "=rm" (flags)
                     : /* no input */
                     : "memory");

        return flags;
}

spinlock_t mytest1_spinlock;
spinlock_t mytest2_spinlock;
unsigned long  flag1;
unsigned long  flag2;

static int __init spin_lock_irq_test_init(void)
{
	printk(KERN_ALERT "[Hello] spin_lock_irq_test \n");

	spin_lock_init(&mytest1_spinlock);
	spin_lock_init(&mytest2_spinlock);

	printk(KERN_ALERT "begin\n");
	printk(KERN_ALERT  "mytest1 0x%x,  flag1 = 0x%lx\n",mytest1_spinlock.rlock.raw_lock.val.counter, flag1);
	printk(KERN_ALERT  "mytest2 0x%x,  flag2 = 0x%lx\n",mytest2_spinlock.rlock.raw_lock.val.counter, flag2);
	printk(KERN_ALERT  "flag = 0x%lx\n", get_flag());
	spin_lock_irqsave(&mytest1_spinlock, flag1);
	printk(KERN_ALERT  "lock mytest1 0x%x,  flag1 = 0x%lx\n",mytest1_spinlock.rlock.raw_lock.val.counter, flag1);
	printk(KERN_ALERT  "flag = 0x%lx\n", get_flag());
//	spin_lock_irqsave(&mytest2_spinlock, flag2);
	spin_lock_irq(&mytest2_spinlock);
	printk(KERN_ALERT  "lock mytest2 0x%x,  flag2 = 0x%lx\n",mytest2_spinlock.rlock.raw_lock.val.counter, flag2);
	printk(KERN_ALERT  "flag = 0x%lx\n", get_flag());
//	spin_unlock_irqrestore(&mytest2_spinlock, flag2);
	spin_unlock_irq(&mytest2_spinlock);
	printk(KERN_ALERT  "unlock mytest2 0x%x,  flag2 = 0x%lx\n",mytest2_spinlock.rlock.raw_lock.val.counter, flag2);
	printk(KERN_ALERT  "flag = 0x%lx\n", get_flag());
	spin_unlock_irqrestore(&mytest1_spinlock, flag1);
	printk(KERN_ALERT  "unlock mytest1 0x%x,  flag1 = 0x%lx\n",mytest1_spinlock.rlock.raw_lock.val.counter, flag1);
	printk(KERN_ALERT  "flag = 0x%lx\n", get_flag());

	return 0;
}

static void __exit spin_lock_irq_test_exit(void)
{
	printk(KERN_ALERT "[Goodbye] spin_lock_irq_test\n");
}

module_init(spin_lock_irq_test_init);
module_exit(spin_lock_irq_test_exit);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("datawolf");

