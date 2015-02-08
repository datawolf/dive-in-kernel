/***********************************************
 * module : list_module 
 * 
 * datawolf (wanglong@cse.buaa.edu.cn)
 **********************************************/
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/list.h>

struct module *m = &__this_module;

static void list_module_test(void)
{
        struct module *mod;
        list_for_each_entry(mod, m->list.prev, list)
                printk ("%s\n", mod->name);

}

static int __init list_module_init(void)
{
	printk(KERN_ALERT "[Hello] list_module \n");
	list_module_test();
	return 0;
}

static void __exit list_module_exit(void)
{
	printk(KERN_ALERT "[Goodbye] list_module\n");
}

module_init(list_module_init);
module_exit(list_module_exit);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("datawolf");
