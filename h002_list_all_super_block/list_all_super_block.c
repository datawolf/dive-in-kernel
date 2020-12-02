/***********************************************
 * module : list_all_super_block
 *
 * Wang Long (wanglong@laoqinren.net)
 **********************************************/
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/kallsyms.h>
#include <linux/kdev_t.h>
#include <linux/fs.h>

static int __init list_all_super_block_init(void)
{
	struct super_block *sb;
	struct list_head *super_blocks = (struct list_head *)kallsyms_lookup_name("super_blocks");

	printk(KERN_ALERT "[Hello] list_all_super_block %lx\n", super_blocks);
	list_for_each_entry(sb, super_blocks, s_list) {
		printk(KERN_INFO "dev_t: %d,%d fs_name: %s name: %s",
			MAJOR(sb->s_dev),
			MINOR(sb->s_dev),
			sb->s_type->name,
			sb->s_id);
	}
	return 0;
}

static void __exit list_all_super_block_exit(void)
{
	printk(KERN_ALERT "[Goodbye] list_all_super_block\n");
}

module_init(list_all_super_block_init);
module_exit(list_all_super_block_exit);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("datawolf");
