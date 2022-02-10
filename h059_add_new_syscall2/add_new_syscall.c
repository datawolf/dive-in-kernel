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



#define __NR_syscall 400	/* 系统调用号400 */
static int sys_mycall(void);

unsigned long *sys_call_table = 0;
static int (*anything_saved)(void);	/*定义一个函数指针，用来保存一个系统调用*/

int make_rw(unsigned long address)
{
	unsigned int level;
	pte_t *pte = lookup_address(address, &level);//查找虚拟地址所在的页表地址  
	if (pte->pte & ~_PAGE_RW)  //设置页表读写属性
		pte->pte |=  _PAGE_RW;  

	return 0;  
}

int make_ro(unsigned long address)
{
	unsigned int level;
	pte_t *pte = lookup_address(address, &level);
	pte->pte &= ~_PAGE_RW;  //设置只读属性

	return 0;
}

/* 添加自己的系统调用函数 */
static int sys_mycall(void)
{
	int ret = 12345;
	printk(KERN_ALERT "My syscall is successful!\n");
	return ret;
}

static int __init add_new_syscall_init(void)
{
	printk(KERN_ALERT "[Hello] add_new_syscall \n");

	sys_call_table = (unsigned long *)kallsyms_lookup_name("sys_call_table");	/* 获取系统调用服务首地址 */
	printk(KERN_ALERT "sys_call_table: 0x%px\n", sys_call_table);

	anything_saved = (int(*)(void))(sys_call_table[__NR_syscall]);	/* 保存原始系统调用 */
	make_rw((unsigned long)sys_call_table);
	sys_call_table[__NR_syscall] = (unsigned long)&sys_mycall;	/* 更改原始的系统调用服务地址 */
	make_ro((unsigned long)sys_call_table);

	return 0;
}

static void __exit add_new_syscall_exit(void)
{
	make_rw((unsigned long)sys_call_table);
	sys_call_table[__NR_syscall] = (unsigned long)anything_saved;	/* 设置cr0可更改 */
	make_ro((unsigned long)sys_call_table);
	printk(KERN_ALERT "[Goodbye] add_new_syscall\n");
}

module_init(add_new_syscall_init);
module_exit(add_new_syscall_exit);
MODULE_LICENSE("GPL");
