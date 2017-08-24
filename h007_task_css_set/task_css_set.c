/***********************************************
 * module : task_css_set
 *
 * Wang Long (wanglong@laoqinren.net)
 **********************************************/
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/pid.h>
#include <linux/sched.h>
#include <linux/list.h>

static int pid = 1;
module_param(pid, int, 1);

static int __init task_css_set_init(void)
{
	pid_t p = (pid_t)pid;
	struct task_struct *tk = get_pid_task(find_get_pid(p), PIDTYPE_PID);
	struct task_struct *cur;

	printk(KERN_ALERT "[Hello] task_css_set \n");
	printk("task name: %s[%d]\n", tk->comm, tk->pid);

	printk("Process with the same css_set\n");
	list_for_each_entry(cur, &tk->cg_list, cg_list) {
		printk("name = %s[%d]\n", cur->comm, cur->pid);
	}

	return 0;
}

static void __exit task_css_set_exit(void)
{
	printk(KERN_ALERT "[Goodbye] task_css_set\n");
}

module_init(task_css_set_init);
module_exit(task_css_set_exit);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("datawolf");
