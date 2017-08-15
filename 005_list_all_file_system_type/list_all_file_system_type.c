/***********************************************
 * module : list_all_file_system_type 
 * 
 * datawolf (wanglong@cse.buaa.edu.cn)
 **********************************************/
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/kallsyms.h>
#include <linux/fs.h>

static int __init list_all_file_system_type_init(void)
{
	struct file_system_type **fs = (struct file_system_type **)kallsyms_lookup_name("file_systems");
	while (*fs){
		printk(KERN_ALERT "file system type : %s\n", (*fs)->name);
		fs = &(*fs)->next;
	}

	return 0;
}

static void __exit list_all_file_system_type_exit(void)
{
	printk(KERN_ALERT "[goodbye] list_all_file_system_type\n");
}

module_init(list_all_file_system_type_init);
module_exit(list_all_file_system_type_exit);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("datawolf");
