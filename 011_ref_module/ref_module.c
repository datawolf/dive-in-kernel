/***********************************************
 * module : ref_module 
 * 
 * datawolf (wanglong@cse.buaa.edu.cn)
 **********************************************/
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>

static int __init ref_module_init(void)
{
	struct module *b;
	const char *name = "test_module";
	int ret;
	printk(KERN_ALERT "[Hello] ref_module \n");

	b = find_module(name);

	if (b != NULL){
		printk(KERN_ALERT "before calling ref_module,\n");
		printk(KERN_ALERT "refs of %s is : %d\n", name, module_refcount(b));
		ret = ref_module(THIS_MODULE, b);
		printk(KERN_ALERT "ret = %d\n", ret);
		printk(KERN_ALERT "after calling ref_module,\n");
		printk(KERN_ALERT "refs of %s is : %d\n", name, module_refcount(b));
	}
	return 0;
}

static void __exit ref_module_exit(void)
{
	printk(KERN_ALERT "[Goodbye] ref_module\n");
}

module_init(ref_module_init);
module_exit(ref_module_exit);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("datawolf");
