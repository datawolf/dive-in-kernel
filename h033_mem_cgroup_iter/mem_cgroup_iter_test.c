/***********************************************
 * module : mem_cgroup_iter_test
 *
 * Wang Long (w@laoqinren.net)
 **********************************************/
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/cgroup.h>
#include <linux/memcontrol.h>
#include <linux/kallsyms.h>

struct mem_cgroup {
	struct cgroup_subsys_state css;
};


typedef struct mem_cgroup * (*mymem_cgroup_iter)(struct mem_cgroup *,
                                   struct mem_cgroup *,
                                   struct mem_cgroup_reclaim_cookie *);

static  mymem_cgroup_iter   mem_cgroup_iter1;


#define for_each_mem_cgroup(iter) \
	for (iter = mem_cgroup_iter1(NULL, NULL, NULL); \
		iter != NULL;				\
	iter = mem_cgroup_iter1(NULL, iter, NULL))

static int __init mem_cgroup_iter_test_init(void)
{
	struct mem_cgroup *iter;
	static char memcg_name[PATH_MAX];
	int ret;

	printk(KERN_ALERT "[Hello] mem_cgroup_iter_test \n");

	mem_cgroup_iter1 = (mymem_cgroup_iter)kallsyms_lookup_name("mem_cgroup_iter");
	for_each_mem_cgroup(iter) {
		rcu_read_lock();
		ret = cgroup_path(iter->css.cgroup, memcg_name, PATH_MAX);
		if (!ret)
			printk(KERN_DEBUG "%s", memcg_name);
		rcu_read_unlock();
	}
	return 0;
}

static void __exit mem_cgroup_iter_test_exit(void)
{
	printk(KERN_ALERT "[Goodbye] mem_cgroup_iter_test\n");
}

module_init(mem_cgroup_iter_test_init);
module_exit(mem_cgroup_iter_test_exit);
MODULE_LICENSE("GPL");
