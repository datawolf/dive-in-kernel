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
unsigned long * sys_call_table;

unsigned int clear_and_return_cr0(void);
void setback_cr0(unsigned int val);
static int sys_mycall(void);

int orig_cr0;	/* 用来存储cr0寄存器原来的值 */
unsigned long *sys_call_table = 0;
static int (*anything_saved)(void);	/*定义一个函数指针，用来保存一个系统调用*/

/*
 * 设置cr0寄存器的第17位为0
 */
unsigned int clear_and_return_cr0(void)	
{
	unsigned int cr0 = 0;
	unsigned int ret;
	/* 前者用在32位系统。后者用在64位系统，本系统64位 */

	/* 将cr0寄存器的值移动到rax寄存器中，同时输出到cr0变量中 */
	//asm volatile ("movl %%cr0, %%eax" : "=a"(cr0));
	asm volatile ("movq %%cr0, %%rax" : "=a"(cr0));

	ret = cr0;
	cr0 &= 0xfffeffff;	/* 将cr0变量值中的第17位清0，将修改后的值写入cr0寄存器 */
	
	/* 读取cr0的值到rax寄存器，再将rax寄存器的值放入cr0中 */
	//asm volatile ("movl %%eax, %%cr0" :: "a"(cr0));
	asm volatile ("movq %%rax, %%cr0" :: "a"(cr0));	
	return ret;
}

/* 读取val的值到rax寄存器，再将rax寄存器的值放入cr0中 */
void setback_cr0(unsigned int val)
{
	//asm volatile ("movl %%eax, %%cr0" :: "a"(val));
	asm volatile ("movq %%rax, %%cr0" :: "a"(val));
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
	printk(KERN_ALERT "sys_call_table: 0x%p\n", sys_call_table);

	anything_saved = (int(*)(void))(sys_call_table[__NR_syscall]);	/* 保存原始系统调用 */
	orig_cr0 = clear_and_return_cr0();	/* 设置cr0可更改 */
	sys_call_table[__NR_syscall] = (unsigned long)&sys_mycall;	/* 更改原始的系统调用服务地址 */
	setback_cr0(orig_cr0);	/* 设置为原始的只读cr0 */

	return 0;
}

static void __exit add_new_syscall_exit(void)
{
	orig_cr0 = clear_and_return_cr0();	/* 设置cr0中对sys_call_table的更改权限 */
	sys_call_table[__NR_syscall] = (unsigned long)anything_saved;	/* 设置cr0可更改 */
	setback_cr0(orig_cr0);	/* 恢复原有的中断向量表中的函数指针的值 */
	printk(KERN_ALERT "[Goodbye] add_new_syscall\n");
}

module_init(add_new_syscall_init);
module_exit(add_new_syscall_exit);
MODULE_LICENSE("GPL");
