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
#include <linux/cgroup.h>

static int pid = 1;
module_param(pid, int, 1);

static int __init task_css_set_init(void)
{
	pid_t p = (pid_t)pid;
	struct task_struct *tk = get_pid_task(find_get_pid(p), PIDTYPE_PID);
	struct task_struct *cur;
	int i;
	struct cgroup_subsys_state *css;

	printk(KERN_ALERT "[Hello] task_css_set \n");
	printk("task name: %s[%d]\n", tk->comm, tk->pid);

	printk("Process with the same css_set\n");
	list_for_each_entry(cur, &tk->cg_list, cg_list) {
		printk("name = %s[%d]\n", cur->comm, cur->pid);
	}

	printk("###### css_set info #######\n");
	printk("css_set.refcount = %d\n", tk->cgroups->refcount.counter);

	printk("CGROUP_SUBSYS_COUNT = %d\n", CGROUP_SUBSYS_COUNT);
	for (i = 0; i < CGROUP_SUBSYS_COUNT; i++) {
		struct cgroup *cg;
		css = tk->cgroups->subsys[i];
		if (css) {
			printk("subsys[%d].refcnt = %d\n", i, css->refcnt.counter);
			printk("subsys[%d].cgroup.name = %s\n", i, css->cgroup->name->name);
			printk("subsys[%d].cgroupfs_root.name = %s\n", i, css->cgroup->root->top_cgroup.name->name);
			printk("subsys[%d].cgroupfs_root.release_agent = %s\n", i,
				css->cgroup->root->release_agent_path);
			if (css->cgroup->parent)
				printk("subsys[%d].cgroup.parent.name = %s\n", i, css->cgroup->parent->name->name);
			list_for_each_entry(cg, &css->cgroup->children, sibling) {
				printk("subsys[%d].childcgroup.name = %s\n", i, cg->name->name);
			}
		}
		printk("\n");
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
