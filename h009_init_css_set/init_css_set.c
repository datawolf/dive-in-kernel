/***********************************************
 * module : init_css_set
 *
 * Wang Long (wanglong@laoqinren.net)
 **********************************************/
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/sched.h>
#include <linux/list.h>
#include <linux/cgroup.h>
#include <linux/kallsyms.h>

struct cg_cgroup_link {
	/*
	 * List running through cg_cgroup_links associated with a
	 * cgroup, anchored on cgroup->css_sets
	 */
	struct list_head cgrp_link_list;
	struct cgroup *cgrp;
	/*
	 * List running through cg_cgroup_links pointing at a                                                                                                 
	 * single css_set object, anchored on css_set->cg_links
	 */
	struct list_head cg_link_list;
	struct css_set *cg; 
};

static int __init init_css_set_init(void)
{
	int i = 0;
	struct cgroup_subsys_state *css;
	struct css_set *ics = (struct css_set*)kallsyms_lookup_name("init_css_set");
	struct cg_cgroup_link *icsl = (struct cg_cgroup_link*)kallsyms_lookup_name("init_css_set_link");
	struct cg_cgroup_link *ccl;

	printk(KERN_ALERT "[Hello] init_css_set \n");
	printk("###### init_css_set info #######\n");
	printk("init_css_set.refcount = %d\n", ics->refcount.counter);

	printk("###### init_css_set_link info #######\n");
	list_for_each_entry(ccl, &(ics->cg_links), cg_link_list) {
		printk("%d ", i++);
		if (ccl->cgrp) {
			struct cgroup_subsys *cs;
			printk("addr = %p, hierarchy_d = %d, hierarchy_name = %s, num = %d, (top_cgroup.name = %s) name = %s",
				ccl->cgrp, ccl->cgrp->root->hierarchy_id, 
				ccl->cgrp->root->name,
				ccl->cgrp->root->number_of_cgroups,
				ccl->cgrp->root->top_cgroup.name->name,
				ccl->cgrp->name->name);
			printk("\tsubsys: ");
			list_for_each_entry(cs, &ccl->cgrp->root->subsys_list, sibling) {
				printk("%s, ", cs->name);
			}
		}
		if (ccl == icsl)
			printk("OK");
		printk("\n");
		printk("cg = %p\n", ccl->cg);
	}
	printk("#############\n");
	printk("current's css_set addr = %p\n", current->cgroups);
	list_for_each_entry(ccl, &(current->cgroups->cg_links), cg_link_list) {
		printk("%d ", i++);
		if (ccl->cgrp) {
			struct cgroup_subsys *cs;
			printk("addr = %p, hierarchy_id = %d, hierarchy_name = %s, num = %d, (top_cgroup.name = %s) name = %s",
				ccl->cgrp,
				ccl->cgrp->root->hierarchy_id,
				ccl->cgrp->root->name,
				ccl->cgrp->root->number_of_cgroups,
				ccl->cgrp->root->top_cgroup.name->name,
				ccl->cgrp->name->name);
			printk("\tsubsys: ");
			list_for_each_entry(cs, &ccl->cgrp->root->subsys_list, sibling) {
				printk("%s, ", cs->name);
			}
		}
		if (ccl == icsl)
			printk("OK");
		printk("\n");
		printk("cg = %p\n", ccl->cg);
	}
	printk("CGROUP_SUBSYS_COUNT = %d\n", CGROUP_SUBSYS_COUNT);
	printk("##################################\n\n");
	for (i = 0; i < CGROUP_SUBSYS_COUNT; i++) {
		struct cgroup *cg;
		css = ics->subsys[i];
		if (css) {
			printk("init_css_set.subsys[%d] addr = %p\n", i, css->cgroup);
			printk("init_css_set.subsys[%d].refcnt = %d\n", i, css->refcnt.counter);
			printk("init_css_set.subsys[%d].cgroup.name = %s\n", i, css->cgroup->name->name);
			printk("init_css_set.subsys[%d].cgroupfs_root.name = %s\n", i, css->cgroup->root->top_cgroup.name->name);
			printk("init_css_set.subsys[%d].cgroupfs_root.release_agent = %s\n", i,
				css->cgroup->root->release_agent_path);
			if (css->cgroup->parent)
				printk("init_css_set.subsys[%d].cgroup.parent.name = %s\n", i, css->cgroup->parent->name->name);
			list_for_each_entry(cg, &css->cgroup->children, sibling) {
				printk("init_css_set.subsys[%d].childcgroup.name = %s\n", i, cg->name->name);
			}
		}
		printk("\n");
	}
	printk("##################################\n\n");
	for (i = 0; i < CGROUP_SUBSYS_COUNT; i++) {
		struct cgroup *cg;
		css = current->cgroups->subsys[i];
		if (css) {
			printk("current->cgroups.subsys[%d] addr = %p\n", i, css->cgroup);
			printk("current->cgroups.subsys[%d].refcnt = %d\n", i, css->refcnt.counter);
			printk("current->cgroups.subsys[%d].cgroup.name = %s\n", i, css->cgroup->name->name);
			printk("current->cgroups.subsys[%d].cgroupfs_root.name = %s\n", i, css->cgroup->root->top_cgroup.name->name);
			printk("current->cgroups.subsys[%d].cgroupfs_root.release_agent = %s\n", i,
				css->cgroup->root->release_agent_path);
			if (css->cgroup->parent)
				printk("current->cgroups.subsys[%d].cgroup.parent.name = %s\n", i, css->cgroup->parent->name->name);
			list_for_each_entry(cg, &css->cgroup->children, sibling) {
				printk("current->cgroups.subsys[%d].childcgroup.name = %s\n", i, cg->name->name);
			}
		}
		printk("\n");
	}

	return 0;
}

static void __exit init_css_set_exit(void)
{
	printk(KERN_ALERT "[Goodbye] init_css_set\n");
}

module_init(init_css_set_init);
module_exit(init_css_set_exit);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("datawolf");



