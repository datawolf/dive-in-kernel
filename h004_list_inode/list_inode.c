#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/list.h>
#include <linux/kallsyms.h>
#include <linux/kdev_t.h>
#include <linux/spinlock.h>

static char *fs = "ext4";
module_param(fs, charp, 0);
static int __init list_inode_init(void)
{
	struct super_block *sb;
	struct inode *pinode;
	struct dentry *pdentry;
	//找到ext4的文件系统类型描述结构体
	struct file_system_type *fst = get_fs_type(fs);
	spinlock_t * lock = (spinlock_t *)kallsyms_lookup_name("sb_lock");

	printk(KERN_INFO "The filesystem's name is : %s\n", fst->name);
	
	printk(KERN_INFO "******************************************");
	//遍历所有的ext4超级快
	spin_lock(lock);
	hlist_for_each_entry(sb, &fst->fs_supers, s_instances)
	{
		printk(KERN_INFO "The %s filesystem  is : %s(%d:%d)\n", fs, sb->s_id,
				MAJOR(sb->s_dev), MINOR(sb->s_dev));
		list_for_each_entry(pinode, &sb->s_inodes, i_sb_list) {
			printk("%lu [", pinode->i_ino);
			hlist_for_each_entry(pdentry, &pinode->i_dentry, d_u.d_alias) {
				printk("%s->", pdentry->d_name.name);
			}
			printk("]\n");
		}
		
		printk("\n");
	}
	spin_unlock(lock);
	return 0;
}

static void __exit list_inode_exit(void)
{
	printk(KERN_ALERT "Goodbye list_inode\n");
}

module_init(list_inode_init);
module_exit(list_inode_exit);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("datawolf");
