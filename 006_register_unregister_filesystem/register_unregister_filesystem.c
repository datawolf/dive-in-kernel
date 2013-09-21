/***********************************************
 * module : register_unregister_filesystem 
 * 
 * datawolf (wanglong@cse.buaa.edu.cn)
 **********************************************/
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/fs.h>

static int __init register_unregister_filesystem_init(void)
{
	const char *name = "ext4";
	struct file_system_type *fst = get_fs_type(name);
	
	printk(KERN_ALERT "[Hello] register_unregister_filesystem \n");
	//注册文件系统名为ext4的文件系统
	if (register_filesystem(fst) == 0)
	{
		printk(KERN_ALERT "Register filesystem successfully\n");
		printk(KERN_ALERT "The name of the Register filesystem is %s\n", fst->name);
	}else
	{
		printk(KERN_ALERT "Register filesystem failed\n");
	}


	//注销文件系统名为ext4的文件系统
	if (unregister_filesystem(fst) == 0)
	{
		printk(KERN_ALERT "Unregister filesystem successfully\n");
		printk(KERN_ALERT "The name of the Unregister filesystem is %s\n", fst->name);
	}else
	{
		printk(KERN_ALERT "Unregister filesystem failed\n");
	}

	//重新注册文件系统名为ext4的文件系统
	if (register_filesystem(fst) == 0)
	{
		printk(KERN_ALERT "Register filesystem successfully\n");
		printk(KERN_ALERT "The name of the Register filesystem is %s\n", fst->name);
	}else
	{
		printk(KERN_ALERT "Register filesystem failed\n");
	}
	
	return 0;
}

static void __exit register_unregister_filesystem_exit(void)
{
	printk(KERN_ALERT "[Goodbye] register_unregister_filesystem\n");
}

module_init(register_unregister_filesystem_init);
module_exit(register_unregister_filesystem_exit);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("datawolf");
