/***********************************************
 * module : print_mem_cgroup_stat
 *
 * Wang Long (w@laoqinren.net)
 **********************************************/
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/memcontrol.h>
static int pid = 1;
module_param(pid, int, 0400);
MODULE_PARM_DESC(pid, "The pid to print");

static int __init print_mem_cgroup_stat_init(void)
{
	pid_t p = (pid_t)pid;
	struct task_struct *task;
	struct mem_cgroup *memcg = NULL;
	long val = 0;
	int cpu;

	printk(KERN_ALERT "[Hello] print_mem_cgroup_stat \n");
	task = get_pid_task(find_get_pid(p), PIDTYPE_PID);
	//memcg = mem_cgroup_from_task(task);
	memcg = mem_cgroup_from_css(task_subsys_state(task, mem_cgroup_subsys_id));

	for_each_online_cpu(cpu) {
		val = per_cpu(memcg->stat->count[MEM_CGROUP_STAT_WRITEBACK], cpu);
		printk(KERN_ALERT "cpu %d, writeback count = %ld", cpu, val);
	}
	return 0;
}

static void __exit print_mem_cgroup_stat_exit(void)
{
	printk(KERN_ALERT "[Goodbye] print_mem_cgroup_stat\n");
}

module_init(print_mem_cgroup_stat_init);
module_exit(print_mem_cgroup_stat_exit);
MODULE_LICENSE("GPL");
