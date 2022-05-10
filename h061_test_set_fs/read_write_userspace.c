/***********************************************
 * module : read_write_userspace
 *
 * Wang Long (w@laoqinren.net)
 **********************************************/
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/uaccess.h>
#include <linux/kallsyms.h>

static ssize_t (*orig_vfs_write)(struct file *file, const char __user *buf, size_t count, loff_t *pos);
static ssize_t (*orig_vfs_read)(struct file *file, char __user *buf, size_t count, loff_t *pos);

char buf_write[128];
char buf_read[128];
static int __init read_write_userspace_init(void)
{
	struct file *fp;
	mm_segment_t old_fs;
	int ret;

	loff_t pos;

	printk(KERN_ALERT "[Hello] read_write_userspace \n");

	orig_vfs_read = (void *)kallsyms_lookup_name("vfs_read");
	if (!orig_vfs_read) {
		pr_err("can't find vfs_read symbol\n");
		return -ENXIO;
	}

	orig_vfs_write = (void *)kallsyms_lookup_name("vfs_write");
	if (!orig_vfs_write) {
		pr_err("can't find vfs_write symbol\n");
		return -ENXIO;
	}

	fp = filp_open("/root/kernel_file", O_RDWR|O_CREAT, 0644);
	if (IS_ERR(fp)) {
		printk(KERN_ALERT "create file error");
		return -1;
	}

	sprintf(buf_write,"%s", "The message: I from kerenl!\n");
	old_fs = get_fs();
	set_fs(KERNEL_DS);

	pos = 0;
	ret = orig_vfs_write(fp, buf_write, sizeof(buf_write), &pos);
	if (ret < 0)
		printk(KERN_ALERT "vfs_write : ret = %d\n", ret);

	pos =0;
	ret = orig_vfs_read(fp, buf_read, sizeof(buf_read), &pos);
	if (ret < 0)
		printk(KERN_ALERT "vfs_read: ret = %d\n", ret);

	printk(KERN_ALERT "write connent = %s\n", buf_read);
	filp_close(fp, NULL);
	set_fs(old_fs);

	return 0;
}

static void __exit read_write_userspace_exit(void)
{
	printk(KERN_ALERT "[Goodbye] read_write_userspace\n");
}

module_init(read_write_userspace_init);
module_exit(read_write_userspace_exit);
MODULE_LICENSE("GPL");
