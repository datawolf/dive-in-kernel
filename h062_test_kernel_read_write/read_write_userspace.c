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

char buf_write[128];
char buf_read[128];
static int __init read_write_userspace_init(void)
{
	struct file *fp;
	int ret;

	loff_t pos;

	printk(KERN_ALERT "[Hello] read_write_userspace \n");

	fp = filp_open("/root/kernel_file2", O_RDWR|O_CREAT, 0644);
	if (IS_ERR(fp)) {
		printk(KERN_ALERT "create file error");
		return -1;
	}

	sprintf(buf_write,"%s", "The message: I from kerenl!, using kernel_write and kernel_read\n");

	pos = 0;
	ret = kernel_write(fp, buf_write, sizeof(buf_write), &pos);
	if (ret < 0)
		printk(KERN_ALERT "kernel_write : ret = %d\n", ret);

	pos =0;
	ret = kernel_read(fp, buf_read, sizeof(buf_read), &pos);
	if (ret < 0)
		printk(KERN_ALERT "kernel_read: ret = %d\n", ret);

	printk(KERN_ALERT "write connent = %s\n", buf_read);
	filp_close(fp, NULL);

	return 0;
}

static void __exit read_write_userspace_exit(void)
{
	printk(KERN_ALERT "[Goodbye] read_write_userspace\n");
}

module_init(read_write_userspace_init);
module_exit(read_write_userspace_exit);
MODULE_LICENSE("GPL");
