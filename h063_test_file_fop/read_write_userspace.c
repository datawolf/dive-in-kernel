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
	mm_segment_t old_fs;
	loff_t pos;

	printk(KERN_ALERT "[Hello] read_write_userspace \n");

	fp = filp_open("/root/kernel_file3", O_RDWR|O_APPEND|O_CREAT, 0644);
	if (IS_ERR(fp)) {
		printk(KERN_ALERT "create file error");
		return -1;
	}

	if (fp->f_op == NULL) {
		printk(KERN_ALERT "fp->f_op == NULL");
		return -1;
	}

	if (fp->f_op->write == NULL) {
		printk(KERN_ALERT "fp->f_op->write == NULL");
		return -1;
	}

	if (fp->f_op->read == NULL) {
		printk(KERN_ALERT "fp->f_op->read == NULL");
		return -1;
	}

	sprintf(buf_write,"%s", "The message: I from kerenl!, using file->f_op->write\n");
	old_fs = get_fs();
	pos = 0;
	ret = fp->f_op->write(fp, buf_write, sizeof(buf_write), &pos);
	if (ret < 0)
		printk(KERN_ALERT "fp->f_op->write: ret = %d\n", ret);

	pos =0;
	ret = fp->f_op->read(fp, buf_read, sizeof(buf_read), &pos);
	if (ret < 0)
		printk(KERN_ALERT "fp->f_op->read: ret = %d\n", ret);

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
