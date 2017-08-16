#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/list.h>

static char *fs = "ext4";
module_param(fs, charp, 0);
static int __init list_super_block_init(void)
{
	struct super_block *sb;
	//找到ext4的文件系统类型描述结构体
	struct file_system_type *fst = get_fs_type(fs);

	printk(KERN_ALERT "The filesystem's name is : %s\n", fst->name);
	
	printk(KERN_ALERT "******************************************");
	//遍历所有的ext4超级快
	hlist_for_each_entry(sb, &fst->fs_supers, s_instances)
	{
		printk(KERN_ALERT "The %s filesystem  is : %s\n", fs, sb->s_id);
	}
	return 0;
}

static void __exit list_super_block_exit(void)
{
	printk(KERN_ALERT "Goodbye list_super_block\n");
}

module_init(list_super_block_init);
module_exit(list_super_block_exit);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("datawolf");
