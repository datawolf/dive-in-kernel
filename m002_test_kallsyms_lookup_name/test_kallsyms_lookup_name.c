/***********************************************
 * module : test_kallsyms_lookup_name
 *
 * Wang Long (w@laoqinren.net)
 **********************************************/
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/kallsyms.h>


static int __init test_kallsyms_lookup_name_init(void)
{
	struct list_head *super_blocks;
	unsigned long *sys_call_table;

	printk(KERN_ALERT "[Hello] test_kallsyms_lookup_name \n");

	super_blocks = (struct list_head *)kallsyms_lookup_name("super_blocks");
	printk(KERN_ALERT "The address of super_blocks is 0x%lx\n", super_blocks);
	printk(KERN_ALERT "The address of super_blocks is 0x%p\n", super_blocks);
	printk(KERN_ALERT "The address of super_blocks is 0x%px\n", super_blocks);


	sys_call_table = (unsigned long *)kallsyms_lookup_name("sys_call_table");
	printk(KERN_ALERT "The address of sys_call_table is 0x%lx\n", sys_call_table);
	printk(KERN_ALERT "The address of sys_call_table is 0x%p\n", sys_call_table);
	printk(KERN_ALERT "The address of sys_call_table is 0x%px\n", sys_call_table);

	return 0;
}

static void __exit test_kallsyms_lookup_name_exit(void)
{
	printk(KERN_ALERT "[Goodbye] test_kallsyms_lookup_name\n");
}

module_init(test_kallsyms_lookup_name_init);
module_exit(test_kallsyms_lookup_name_exit);
MODULE_LICENSE("GPL");
