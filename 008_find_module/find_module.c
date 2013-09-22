/***********************************************
 * module : find_module 
 * 
 * datawolf (wanglong@cse.buaa.edu.cn)
 **********************************************/
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>

static int __init find_module_init(void)
{
	const char *name = "ext3";
	struct module * fmodule = find_module(name);

	printk(KERN_ALERT "[Hello] find_module \n");

	if (fmodule != 	NULL){
		printk(KERN_ALERT "fmodule->name: %s\n", fmodule->name);
		printk(KERN_ALERT "fmodule->state: %d\n", fmodule->state);
		printk(KERN_ALERT "fmodule->core_size: %d\n", fmodule->core_size);
		printk(KERN_ALERT "module_refcount(fmodule): %d\n", module_refcount(fmodule));
	}

	name = "ext4";
	fmodule = find_module(name);

	if (fmodule != 	NULL){
		printk(KERN_ALERT "fmodule->name: %s\n", fmodule->name);
		printk(KERN_ALERT "fmodule->state: %d\n", fmodule->state);
		printk(KERN_ALERT "fmodule->core_size: %d\n", fmodule->core_size);
		printk(KERN_ALERT "module_refcount(fmodule): %d\n", module_refcount(fmodule));
	}

	return 0;
}

static void __exit find_module_exit(void)
{
	printk(KERN_ALERT "[Goodbye] find_module\n");
}

module_init(find_module_init);
module_exit(find_module_exit);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("datawolf");
