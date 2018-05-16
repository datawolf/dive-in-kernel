/***********************************************
 * module : css_set_cg_links
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


static int pid = 1;
module_param(pid, int, 1);


struct cg_cgroup_link {
	struct list_head cgrp_link_list;
	struct cgroup *cgrp;
	struct list_head cg_link_list;
	struct css_set *cg;
};

static int __init css_set_cg_links_init(void)
{
	pid_t p = (pid_t)pid;
	struct task_struct *tk = get_pid_task(find_get_pid(p), PIDTYPE_PID);
	struct css_set *init_css = (struct css_set*)kallsyms_lookup_name("init_css_set");
	struct css_set *cg;
	struct cg_cgroup_link *link;

	printk(KERN_ALERT "[Hello] css_set_cg_links \n");
	printk("task name: %s[%d]\n", tk->comm, tk->pid);

	cg = tk->cgroups;
	printk("###### css_set info #######\n");
	printk("css_set.refcount = %d\n", cg->refcount.counter);

	if (cg == init_css)
		printk("@@@@@ in init cgroup @@@@@\n");
	else
		printk("@@@@@ NOT in init cgroup @@@@@\n");

	list_for_each_entry(link, &cg->cg_links, cg_link_list) {
		struct cgroup *c = link->cgrp;
		const char *name;

		if (c->dentry)
			name = c->dentry->d_name.name;
		else
			name = "?";
		printk("Root %d(%s) group %s\n", c->root->hierarchy_id, c->root->name, name);
	}

	return 0;
}

static void __exit css_set_cg_links_exit(void)
{
	printk(KERN_ALERT "[Goodbye] css_set_cg_links\n");
}

module_init(css_set_cg_links_init);
module_exit(css_set_cg_links_exit);
MODULE_LICENSE("GPL");
