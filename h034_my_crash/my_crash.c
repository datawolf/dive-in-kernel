/***********************************************
 * module : my_crash
 *
 * Wang Long (w@laoqinren.net)
 **********************************************/
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/types.h>
#include <linux/miscdevice.h>
#include <linux/init.h>
#include <asm/io.h>
#include <asm/uaccess.h>
#include <asm/types.h>
#include <asm/crash-driver.h>

static unsigned long dram_size = 0;
/*
 *  These are the file operation functions that allow crash utility
 *  access to physical memory.
 */

static loff_t 
crash_llseek(struct file * file, loff_t offset, int orig)
{
	unsigned long newpos = -1;
	switch (orig) {
	case 0:
		newpos = offset;
		break;
	case 1:
		newpos = file->f_pos + offset;
		break;
	case 2:
		newpos = dram_size + offset;
		break;
	}

	if ((newpos < 0) || (newpos > dram_size))
		return  -EINVAL;

	file->f_pos = newpos;

	return newpos;
}

/*
 *  Determine the page address for an address offset value, 
 *  get a virtual address for it, and copy it out.
 *  Accesses must fit within a page.
 */
static ssize_t
crash_read(struct file *file, char *buf, size_t count, loff_t *poff)
{
	void *vaddr;
	struct page *page;
	u64 offset;
	ssize_t read;

	offset = *poff;
	if (offset >> PAGE_SHIFT != (offset+count-1) >> PAGE_SHIFT) 
		return -EINVAL;

	vaddr = map_virtual(offset, &page);
	if (!vaddr)
		return -EFAULT;

	if (copy_to_user(buf, vaddr, count)) {
		unmap_virtual(page);
		return -EFAULT;
	}
	unmap_virtual(page);

	read = count;
	*poff += read;
	return read;
}

static int 
crash_open(struct inode * inode, struct file * filp)
{
        return capable(CAP_SYS_RAWIO) ? 0 : -EPERM;
}

static struct file_operations crash_fops = {
	.owner = THIS_MODULE,
	.llseek = crash_llseek,
	.read = crash_read,
	.open = crash_open,
};

static struct miscdevice crash_dev = {
	MISC_DYNAMIC_MINOR,
	"mycrash",
	&crash_fops
};


static inline unsigned long get_total_physpages(void)
{
	int nid;
	unsigned long phys_pages = 0;

	for_each_online_node(nid)
		phys_pages += node_spanned_pages(nid);

	return phys_pages;
}


static int __init my_crash_init(void)
{
	int ret;

	dram_size = (unsigned long )get_total_physpages() << PAGE_SHIFT;

	printk(KERN_ALERT "[Hello] my_crash, ramtop = %08lx(%lu MB)\n", dram_size, dram_size >> 20);
	ret = misc_register(&crash_dev);
	if (ret) {
		printk(KERN_ERR 
		    "crash memory driver: cannot misc_register (MISC_DYNAMIC_MINOR)\n");
		goto out;
	}
	
	ret = 0;
out:
	return ret;

	return 0;
}

static void __exit my_crash_exit(void)
{
	misc_deregister(&crash_dev);
	printk(KERN_ALERT "[Goodbye] my_crash\n");
}

module_init(my_crash_init);
module_exit(my_crash_exit);
MODULE_LICENSE("GPL");
