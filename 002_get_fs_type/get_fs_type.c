#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/fs.h>


static int __init get_fs_type_init(void)
{
	const	char *name = "ext4";

	struct file_system_type *fst = get_fs_type(name);
	if (fst == NULL){
		printk(KERN_ALERT "NULL pointer error");
	}

	printk(KERN_ALERT "The filesystem's name is : %s\n", fst->name);
	return 0;
}

static void __exit get_fs_type_exit(void)
{
	printk(KERN_ALERT "Goodbye get_fs_type\n");
}

module_init(get_fs_type_init);
module_exit(get_fs_type_exit);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("datawolf");
