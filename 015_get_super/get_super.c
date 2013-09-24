/***********************************************
 * module : get_super 
 * 
 * datawolf (wanglong@cse.buaa.edu.cn)
 **********************************************/
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/fs_struct.h>
#include <linux/path.h>
#include <linux/sched.h>

static int __init get_super_init(void)
{
	struct super_block *sb;
	struct super_block *sb1;
	struct block_device *bdev;
	printk(KERN_ALERT "[Hello] get_super \n");

	sb = current->fs->pwd.dentry->d_sb;
	bdev = sb->s_bdev;

	printk(KERN_ALERT "the super block's dev number is %d.\n", sb->s_dev);
	sb1 = get_super(bdev);

	if (sb1 != NULL)
		printk(KERN_ALERT "After the \"get_super\", the super block's dev number is %d.\n", sb1->s_dev);
	else
		printk(KERN_ALERT "Can not be found! \n");


	return 0;
}

static void __exit get_super_exit(void)
{
	printk(KERN_ALERT "[Goodbye] get_super\n");
}

module_init(get_super_init);
module_exit(get_super_exit);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("datawolf");
