/***********************************************
 * module : module_is_live 
 * 
 * datawolf (wanglong@cse.buaa.edu.cn)
 **********************************************/
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>


static int ret;

static int __init module_is_live_init(void)
{
	printk(KERN_ALERT "[Hello] module_is_live \n");

	ret = module_is_live(THIS_MODULE);	

	if (ret == 1){
		printk(KERN_ALERT "in init , state is not GOING\n");
	}else{
		printk(KERN_ALERT "in init , state is GOING \n");
	}
	return 0;
}

static void __exit module_is_live_exit(void)
{
	ret = module_is_live(THIS_MODULE);	

	if (ret == 1){
		printk(KERN_ALERT "in exit, state is not GOING\n");
	}else{
		printk(KERN_ALERT "in exit, state is GOING \n");
	}

	printk(KERN_ALERT "[Goodbye] module_is_live\n");
}

module_init(module_is_live_init);
module_exit(module_is_live_exit);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("datawolf");
