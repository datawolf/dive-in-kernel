/***********************************************
 * module : cgroup_css_links
 *
 * Wang Long (w@laoqinren.net)
 **********************************************/
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/pid.h>
#include <linux/sched.h>
#include <linux/list.h>
#include <linux/cgroup.h>
#include <linux/kallsyms.h>

struct cg_cgroup_link {
	struct list_head cgrp_link_list;
	struct cgroup *cgrp;
	struct list_head cg_link_list;
	struct css_set *cg;
};

static int __init cgroup_css_links_init(void)
{
	// find the "rootnode" hierarchy, it is the "dummy hierarchy"
	struct cgroupfs_root *rootnode = (struct cgroupfs_root*)kallsyms_lookup_name("rootnode");
	// the dummy hierarchy only have on cgroup.
	// All tasks in system are under this cgroup.
	struct cgroup *cgrp = &rootnode->top_cgroup;
	struct cg_cgroup_link *link;

	printk(KERN_ALERT "[Hello] cgroup_css_links \n");

	list_for_each_entry(link, &cgrp->css_sets, cgrp_link_list) {
		struct css_set *cg = link->cg;
		struct task_struct *task;
		printk("css_set %p\n", cg);
		list_for_each_entry(task, &cg->tasks, cg_list) {
			printk("\ttask %d\n", task_pid_vnr(task));
		}
	}

	return 0;
}

static void __exit cgroup_css_links_exit(void)
{
	printk(KERN_ALERT "[Goodbye] cgroup_css_links\n");
}

module_init(cgroup_css_links_init);
module_exit(cgroup_css_links_exit);
MODULE_LICENSE("GPL");
