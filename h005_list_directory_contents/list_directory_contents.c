/***********************************************
 * module : list_directory_contents
 *
 * Wang Long (wanglong@laoqinren.net)
 **********************************************/
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

static unsigned int major = 0;
module_param(major, uint, 0);

static unsigned int minor = 0;
module_param(minor, uint, 0);

static unsigned long inode = 0;
module_param(inode, ulong, 0);

static int __init list_directory_contents_init(void)
{
	struct super_block *sb;
	struct inode *pinode;
	struct dentry *pdentry;
	struct dentry *subdirs;
	//找到ext4的文件系统类型描述结构体
	struct file_system_type *fst = get_fs_type(fs);
	spinlock_t * lock = (spinlock_t *)kallsyms_lookup_name("sb_lock");

	printk(KERN_INFO "The module params: inode = %ld, major = %d, minor = %d, fs = %s\n",
			inode, major, minor, fs);
	printk(KERN_INFO "The filesystem's name is : %s\n", fst->name);
	printk(KERN_INFO "******************************************");
	//遍历特定的ext4超级快
	spin_lock(lock);
	hlist_for_each_entry(sb, &fst->fs_supers, s_instances)
	{
		// 只遍历特定的设备
		if (sb->s_dev == MKDEV(major, minor)) {
			printk(KERN_INFO "The %s filesystem is : %s(%d:%d)\n", fs, sb->s_id,
				MAJOR(sb->s_dev), MINOR(sb->s_dev));
			list_for_each_entry(pinode, &sb->s_inodes, i_sb_list) {
				// 只遍历特定的inode节点
				if (inode == pinode->i_ino) {
					printk("%lu ", pinode->i_ino);
					hlist_for_each_entry(pdentry, &pinode->i_dentry, d_u.d_alias) {
						printk("[%s] parent = %s", pdentry->d_name.name,
							pdentry->d_parent->d_name.name);
						list_for_each_entry(subdirs, &pdentry->d_subdirs, d_child) {
							printk("\n\t\tfile = %s", subdirs->d_name.name);
						}
					}
				}
			}
			
			printk("\n");
		} else
			printk(KERN_INFO "Skip the %s filesystem is : %s(%d:%d)\n", fs, sb->s_id,
				MAJOR(sb->s_dev), MINOR(sb->s_dev));
	}
	spin_unlock(lock);
	return 0;
}

static void __exit list_directory_contents_exit(void)
{
	printk(KERN_ALERT "[Goodbye] list_directory_contents\n");
}

module_init(list_directory_contents_init);
module_exit(list_directory_contents_exit);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("datawolf");
