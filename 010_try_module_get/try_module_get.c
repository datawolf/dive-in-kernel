/***********************************************
 * module : try_module_get 
 * 
 * datawolf (wanglong@cse.buaa.edu.cn)
 **********************************************/
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>

static int __init try_module_get_init(void)
{
	int ret;
	const char *name;
	struct module *fmodule;

	printk(KERN_ALERT "[Hello] try_module_get \n");

	name = "test_module";
	fmodule = find_module(name);
	
	if (fmodule != 	NULL){
		printk(KERN_ALERT "before calling try_module_get,\n");
		printk(KERN_ALERT "refs of %s is : %d\n", name, module_refcount(fmodule));
		ret = try_module_get(fmodule);
		printk(KERN_ALERT "after calling try_module_get,\n");
		printk(KERN_ALERT "ret = %d\n", ret);
		printk(KERN_ALERT "refs of %s is : %d\n", name, module_refcount(fmodule));
	}
	return 0;
}

static void __exit try_module_get_exit(void)
{
	printk(KERN_ALERT "[Goodbye] try_module_get\n");
}

module_init(try_module_get_init);
module_exit(try_module_get_exit);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("datawolf");
