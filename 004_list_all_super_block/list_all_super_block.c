#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/list.h>


static int __init list_all_super_block_init(void)
{
	const	char *name = "ext4";

	struct file_system_type *fst = get_fs_type(name);

	struct super_block *sb, *first_sb;

	first_sb = list_entry(fst->fs_supers.next, struct super_block, s_instances);

	printk(KERN_ALERT "The filesystem's name is : %s\n", fst->name);
	
	printk(KERN_ALERT "The super_block filesystem name is  : %s\n", first_sb->s_type->name);
	
	list_for_each_entry(sb, &first_sb->s_list, s_list)
	{
		printk(KERN_ALERT "The registered filesystem is : %s\n", sb->s_type->name);
	}
	return 0;
}

static void __exit list_all_super_block_exit(void)
{
	printk(KERN_ALERT "Goodbye list_all_super_block\n");
}

module_init(list_all_super_block_init);
module_exit(list_all_super_block_exit);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("datawolf");
