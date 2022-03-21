/***********************************************
 * module : add_new_syscall
 *
 * Wang Long (w@laoqinren.net)
 **********************************************/
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/unistd.h>
#include <linux/time.h>
#include <linux/sched.h>
#include <linux/kallsyms.h>
#include <linux/mm.h>
#include <linux/set_memory.h>

#define __NR_syscall 400	/* 系统调用号400 */
static int sys_mycall(void);

unsigned long *sys_call_table = 0;
static int (*anything_saved)(void);	/*定义一个函数指针，用来保存一个系统调用*/


static int (*hulk_set_memory_rw)(unsigned long addr, int numpages);
static int (*hulk_set_memory_ro)(unsigned long addr, int numpages);

/* 添加自己的系统调用函数 */
static int sys_mycall(void)
{
	int ret = 12345;
	printk(KERN_ALERT "My syscall is successful!\n");
	return ret;
}

static int __init add_new_syscall_init(void)
{
	int ret;
	printk(KERN_ALERT "[Hello] add_new_syscall \n");

	hulk_set_memory_rw = (void *)kallsyms_lookup_name("set_memory_rw");
	if (!hulk_set_memory_rw) {
		pr_err("can't find set_memory_rw symbol\n");
		return -ENXIO;
	}

	hulk_set_memory_ro = (void *)kallsyms_lookup_name("set_memory_ro");
	if (!hulk_set_memory_ro) {
		pr_err("can't find set_memory_ro symbol\n");
		return -ENXIO;
	}


	sys_call_table = (unsigned long *)kallsyms_lookup_name("sys_call_table");	/* 获取系统调用服务首地址 */
	printk(KERN_ALERT "sys_call_table: 0x%px\n", sys_call_table);

	anything_saved = (int(*)(void))(sys_call_table[__NR_syscall]);	/* 保存原始系统调用 */
	ret = hulk_set_memory_rw((unsigned long)sys_call_table & PAGE_MASK , 1);
	if (ret)
		printk(KERN_ALERT "hulk_set_memory_rw returns: %d\n", ret);
//	sys_call_table[__NR_syscall] = (unsigned long)&sys_mycall;	/* 更改原始的系统调用服务地址 */
	ret = hulk_set_memory_ro((unsigned long)sys_call_table & PAGE_MASK , 1);
	if (ret)
		printk(KERN_ALERT "hulk_set_memory_ro returns: %d\n", ret);

	return 0;
}

static void __exit add_new_syscall_exit(void)
{
	int ret;
	ret = hulk_set_memory_rw((unsigned long)sys_call_table & PAGE_MASK , 1);
	if (ret)
		printk(KERN_ALERT "hulk_set_memory_rw returns: %d\n", ret);
//	sys_call_table[__NR_syscall] = (unsigned long)anything_saved;	/* 设置cr0可更改 */
	ret = hulk_set_memory_ro((unsigned long)sys_call_table & PAGE_MASK , 1);
	if (ret)
		printk(KERN_ALERT "hulk_set_memory_ro returns: %d\n", ret);
	printk(KERN_ALERT "[Goodbye] add_new_syscall\n");
}

module_init(add_new_syscall_init);
module_exit(add_new_syscall_exit);
MODULE_LICENSE("GPL");
