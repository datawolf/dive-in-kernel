/***********************************************
 * module : mem_section_test
 *
 * Wang Long (wanglong@laoqinren.net)
 **********************************************/
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/mm.h>
#include <linux/page_cgroup.h>

static int __init mem_section_test_init(void)
{
	struct page *page = (struct page *)0xffffea00b2e65140;
	struct page_cgroup *pc = (struct page_cgroup *)0xffff8818bec80000;

	unsigned long pfn = page_to_pfn(page);

	printk(KERN_ALERT "[Hello] mem_section_test \n");
	printk(KERN_ALERT "pfn = 0x%lx\n", pfn);
	printk(KERN_ALERT "pc = 0x%p\n", (pc+pfn));

	return 0;
}

static void __exit mem_section_test_exit(void)
{
	printk(KERN_ALERT "[Goodbye] mem_section_test\n");
}

module_init(mem_section_test_init);
module_exit(mem_section_test_exit);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("datawolf");
