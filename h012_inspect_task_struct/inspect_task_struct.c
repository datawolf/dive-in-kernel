/***********************************************
 * module : inspect_task_struct
 *
 * Wang Long (wanglong@laoqinren.net)
 **********************************************/
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/cred.h>
#include <linux/pid.h>
#include <linux/sched.h>

static int pid = 1;
module_param(pid, int, 1);

static int __init inspect_task_struct_init(void)
{
	pid_t p = (pid_t)pid;
	struct task_struct *task = get_pid_task(find_get_pid(p), PIDTYPE_PID);
	struct cred  *tcred;

	printk(KERN_ALERT "[Hello] inspect_task_struct \n");
	tcred = (struct cred *)(task->real_cred);
	printk("pid = %d, euid = %d\n", task->pid, tcred->euid);
	printk("pid = %d, suid = %d\n", task->pid, tcred->suid);
	printk("pid = %d, uid = %d\n", task->pid,  tcred->uid);
	printk("pid = %d, egid = %d\n", task->pid, tcred->egid);
	printk("pid = %d, sgid = %d\n", task->pid, tcred->sgid);
	printk("pid = %d, gid = %d\n", task->pid,  tcred->gid);
	printk("pid = %d, task->mm->flags = %lx\n", task->pid, task->mm->flags);
	return 0;
}

static void __exit inspect_task_struct_exit(void)
{
	printk(KERN_ALERT "[Goodbye] inspect_task_struct\n");
}

module_init(inspect_task_struct_init);
module_exit(inspect_task_struct_exit);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("datawolf");
