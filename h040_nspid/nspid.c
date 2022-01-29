/***********************************************
 * module : nspid
 *
 * Wang Long (w@laoqinren.net)
 **********************************************/
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/pid.h>
#include <linux/limits.h>
#include <linux/fs_struct.h>
#include <linux/mm.h>
#include <linux/atomic.h>
#include <linux/init.h>
#include <linux/connector.h>
#include <linux/gfp.h>
#include <linux/ptrace.h>
#include <linux/atomic.h>
#include <linux/pid_namespace.h>

static int pid = 1;
module_param(pid, int, 1);

static int __init nspid_init(void)
{
	pid_t p = (pid_t)pid;
	struct pid_namespace *ns;
	struct task_struct *task = get_pid_task(find_get_pid(p), PIDTYPE_PID);
	struct task_struct *parent;

	pid_t pid, tid, ppid, ptid;

	printk(KERN_ALERT "[Hello] nspid \n");
	ns = task_active_pid_ns(task);

	pid = task_tgid_nr_ns(task, ns);
	tid = task_pid_nr_ns(task, ns);

	rcu_read_lock();
        parent = rcu_dereference(task->real_parent);
	ppid = task_tgid_nr_ns(parent, ns);
	ptid = task_pid_nr_ns(parent, ns);
	rcu_read_unlock();


	printk(KERN_ALERT "PID = %d\n", pid);
	printk(KERN_ALERT "TID = %d\n", tid);
	printk(KERN_ALERT "PPID = %d\n", ppid);
	printk(KERN_ALERT "PTID = %d\n", ptid);

	return 0;
}

static void __exit nspid_exit(void)
{
	printk(KERN_ALERT "[Goodbye] nspid\n");
}

module_init(nspid_init);
module_exit(nspid_exit);
MODULE_LICENSE("GPL");

