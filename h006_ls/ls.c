/***********************************************
 * module : ls
 *
 * Wang Long (wanglong@laoqinren.net)
 **********************************************/
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/list.h>
#include <linux/fs.h>
#include <linux/path.h>

static char *dir="/root/";
module_param(dir, charp, 0);

static int __init ls_init(void)
{
	struct file *fi;
	struct dentry *thedentry, *curdentry;

	printk(KERN_ALERT "[Hello] ls \n");

	fi = filp_open(dir, O_RDONLY, 0);
	thedentry = fi->f_path.dentry;

	printk("DIR: %s has the following files:", dir);
	list_for_each_entry(curdentry, &thedentry->d_subdirs, d_child) {
		printk("name = %s\n", curdentry->d_name.name);
	}
	filp_close(fi, NULL);
	return 0;
}

static void __exit ls_exit(void)
{
	printk(KERN_ALERT "[Goodbye] ls\n");
}

module_init(ls_init);
module_exit(ls_exit);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("datawolf");
