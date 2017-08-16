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
#include <linux/kdev_t.h>


static int __init get_super_init(void)
{
	struct super_block *sb, *sb1;

	sb = current->fs->pwd.dentry->d_sb;

	printk(KERN_ALERT "[Hello] get_super \n");
	printk(KERN_ALERT "the super block's dev number is %d:%d.\n", MAJOR(sb->s_dev), MINOR(sb->s_dev));

	sb1 = get_super(sb->s_bdev);
	if (sb1 != NULL)
		printk(KERN_ALERT "After the \"get_super\", the super block's dev number is %d:%d.\n",
				MAJOR(sb1->s_dev), MINOR(sb1->s_dev));
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
