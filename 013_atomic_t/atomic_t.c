/***********************************************
 * module : atomic_t 
 * 
 * datawolf (wanglong@cse.buaa.edu.cn)
 **********************************************/
#include <linux/module.h>
#include <linux/types.h>
#include <linux/init.h>

atomic_t at;
static int __init atomic_t_init(void)
{
	int i;
	int ret;
	int num;

	printk(KERN_ALERT "[Hello] atomic_t \n");

	printk(KERN_ALERT "************ TEST atomic_add *******************\n");
	atomic_set(&at, 5);
	printk(KERN_ALERT "after atomic_set(&at, 5). at.counter = %d\n", atomic_read(&at));

	i = 3;
	atomic_add(i, &at);
	printk(KERN_ALERT "after atomic_add(3, &at). at.counter = %d\n", atomic_read(&at));

	printk(KERN_ALERT "************ TEST atomic_sub *******************\n");
	atomic_set(&at, 5);
	printk(KERN_ALERT "after atomic_set(&at, 5). at.counter = %d\n", atomic_read(&at));

	i = 3;
	atomic_sub(i, &at);
	printk(KERN_ALERT "after atomic_sub(3, &at). at.counter = %d\n", atomic_read(&at));


	printk(KERN_ALERT "******* TEST atomic_add_negative ****************\n");
	atomic_set(&at, -5);
	printk(KERN_ALERT "after atomic_set(&at, -5). at.counter = %d\n", atomic_read(&at));

	i = 3;
	ret = atomic_add_negative(i, &at);
	printk(KERN_ALERT "after atomic_add_nagative(3, &at). at.counter = %d\n", atomic_read(&at));
	printk(KERN_ALERT "ret =  %d\n", ret);

	ret = atomic_add_negative(i, &at);
	printk(KERN_ALERT "after atomic_add_nagative(3, &at). at.counter = %d\n", atomic_read(&at));
	printk(KERN_ALERT "ret =  %d\n", ret);

	printk(KERN_ALERT "\n\n******* TEST atomic_add_return ****************\n");
	atomic_set(&at, -5);
	printk(KERN_ALERT "after atomic_set(&at, -5). at.counter = %d\n", atomic_read(&at));

	i = 3;
	ret = atomic_add_return(i, &at);
	printk(KERN_ALERT "after atomic_add_return(3, &at). at.counter = %d\n", atomic_read(&at));
	printk(KERN_ALERT "ret =  %d\n", ret);

	printk(KERN_ALERT "\n\n******* TEST atomic_add_unless****************\n");
	atomic_set(&at, -5);
	printk(KERN_ALERT "after atomic_set(&at, -5). at.counter = %d\n", atomic_read(&at));

	i = 3;
	ret = atomic_add_unless(&at, i, -5);
	printk(KERN_ALERT "after  atomic_add_unless(&at, 3, -5). at.counter = %d\n", atomic_read(&at));
	printk(KERN_ALERT "ret =  %d\n", ret);

	ret = atomic_add_unless(&at, i, -4);
	printk(KERN_ALERT "after  atomic_add_unless(&at, 3, -5). at.counter = %d\n", atomic_read(&at));
	printk(KERN_ALERT "ret =  %d\n", ret);


	printk(KERN_ALERT "\n\n******* TEST atomic_cmpxchg ****************\n");
	atomic_set(&at, -4);
	printk(KERN_ALERT "after atomic_set(&at, -4). at.counter = %d\n", atomic_read(&at));

	ret = atomic_cmpxchg(&at, -5, 4);
	printk(KERN_ALERT "after atomic_cmpxchg(&at, -5, 4 ). at.counter = %d\n", atomic_read(&at));
	printk(KERN_ALERT "ret =  %d\n", ret);

	ret = atomic_cmpxchg(&at, -4, 4);
	printk(KERN_ALERT "after atomic_cmpxchg(&at, -4, 4 ). at.counter = %d\n", atomic_read(&at));
	printk(KERN_ALERT "ret =  %d\n", ret);

	printk(KERN_ALERT "\n\n******* TEST atomic_dec ****************\n");
	atomic_set(&at, -4);
	printk(KERN_ALERT "after atomic_set(&at, -4). at.counter = %d\n", atomic_read(&at));
	atomic_dec(&at);
	printk(KERN_ALERT "after atomic_dec(&at). at.counter = %d\n", atomic_read(&at));
	
	printk(KERN_ALERT "\n\n******* TEST atomic_inc ****************\n");
	atomic_set(&at, -4);
	printk(KERN_ALERT "after atomic_set(&at, -4). at.counter = %d\n", atomic_read(&at));
	atomic_inc(&at);
	printk(KERN_ALERT "after atomic_inc(&at). at.counter = %d\n", atomic_read(&at));


	printk(KERN_ALERT "\n\n******* TEST atomic_dec_and_test ****************\n");
	atomic_set(&at, 4);
	printk(KERN_ALERT "after atomic_set(&at, 4). at.counter = %d\n", atomic_read(&at));
	ret = num = 0;
	while ((ret = atomic_dec_and_test(&at)) == 0){
		num ++;
	}
	printk(KERN_ALERT "num = %d\n", num);
	

	printk(KERN_ALERT "\n\n******* TEST atomic_dec_and_test ****************\n");
	atomic_set(&at, -6);
	printk(KERN_ALERT "after atomic_set(&at, -6). at.counter = %d\n", atomic_read(&at));
	ret = num = 0;
	while ((ret = atomic_inc_and_test(&at)) == 0){
		num ++;
	}
	printk(KERN_ALERT "num = %d\n", num);


	printk(KERN_ALERT "\n\n******* TEST atomic_sub_and_test ****************\n");
	atomic_set(&at, 6);
	printk(KERN_ALERT "after atomic_set(&at, 6). at.counter = %d\n", atomic_read(&at));
	ret = atomic_sub_and_test(3, &at);
	printk(KERN_ALERT "after atomic_sub_and_test(3, &at). at.counter = %d\n", atomic_read(&at));
	printk(KERN_ALERT "ret = %d\n", ret);
	ret = atomic_sub_and_test(3, &at);
	printk(KERN_ALERT "after atomic_sub_and_test(3, &at). at.counter = %d\n", atomic_read(&at));
	printk(KERN_ALERT "ret = %d\n", ret);


	printk(KERN_ALERT "\n\n******* TEST atomic_sub_return****************\n");
	atomic_set(&at, 6);
	printk(KERN_ALERT "after atomic_set(&at, 6). at.counter = %d\n", atomic_read(&at));
	ret = atomic_sub_return(3, &at);
	printk(KERN_ALERT "after atomic_sub_return(3, &at). at.counter = %d\n", atomic_read(&at));
	printk(KERN_ALERT "ret = %d\n", ret);

	return 0;
}

static void __exit atomic_t_exit(void)
{
	printk(KERN_ALERT "[Goodbye] atomic_t\n");
}

module_init(atomic_t_init);
module_exit(atomic_t_exit);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("datawolf");
