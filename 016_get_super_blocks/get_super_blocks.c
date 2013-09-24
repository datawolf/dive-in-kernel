/***********************************************
 * module : get_super_blocks 
 * 
 * datawolf (wanglong@cse.buaa.edu.cn)
 **********************************************/
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/fs.h>

static int __init get_super_blocks_init(void)
{
	struct super_block *sb; 
	printk(KERN_ALERT "[Hello] get_super_blocks \n");
//super_blocks  defined in http://lxr.linux.no/linux+v2.6.35/fs/super.c
//and we can not reach it.
	list_for_each_entry(sb, &super_blocks, s_list)
	{
		printk(KERN_ALERT "The registered filesystem is : %s\n", sb->s_type->name);
		printk(KERN_ALERT "The address of file system type (%s) is : %p\n", 
				sb->s_type->name, sb->s_type);
		printk(KERN_ALERT "The address of file system type (%s) next  is : %p\n", 
				sb->s_type->name, sb->s_type->next);
		printk(KERN_ALERT "\n\n");
	}
	return 0;
}

static void __exit get_super_blocks_exit(void)
{
	printk(KERN_ALERT "[Goodbye] get_super_blocks\n");
}

module_init(get_super_blocks_init);
module_exit(get_super_blocks_exit);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("datawolf");
