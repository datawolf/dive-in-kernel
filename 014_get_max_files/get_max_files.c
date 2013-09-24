/***********************************************
 * module : get_max_files 
 * 
 * datawolf (wanglong@cse.buaa.edu.cn)
 **********************************************/
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/fs.h>

static int __init get_max_files_init(void)
{
	int num_of_max_files;
	printk(KERN_ALERT "[Hello] get_max_files \n");
	num_of_max_files = get_max_files();
	printk(KERN_ALERT "the return value of the get_max_files is %d. \n", num_of_max_files);

	return 0;
}

static void __exit get_max_files_exit(void)
{
	printk(KERN_ALERT "[Goodbye] get_max_files\n");
}

module_init(get_max_files_init);
module_exit(get_max_files_exit);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("datawolf");
