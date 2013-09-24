/***********************************************
 * module : module_put 
 * 
 * datawolf (wanglong@cse.buaa.edu.cn)
 **********************************************/
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>

static int __init module_put_init(void)
{
	const char *name = "test_module";
	struct module *fname = find_module(name);
	printk(KERN_ALERT "[Hello] module_put \n");

	if (fname != NULL){
		printk(KERN_ALERT "before calling module_put,\n");
		printk(KERN_ALERT "refs of %s is : %d\n", name, module_refcount(fname));
		module_put(fname);
		printk(KERN_ALERT "after calling module_put,\n");
		printk(KERN_ALERT "refs of %s is : %d\n", name, module_refcount(fname));
	}
	return 0;
}

static void __exit module_put_exit(void)
{
	printk(KERN_ALERT "[Goodbye] module_put\n");
}

module_init(module_put_init);
module_exit(module_put_exit);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("datawolf");
