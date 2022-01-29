/***********************************************
 * module : debug_mem_cgroup_low
 *
 * Wang Long (w@laoqinren.net)
 **********************************************/
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/kprobes.h>

static bool j_mem_cgroup_low(struct mem_cgroup *root, struct mem_cgroup *memcg)
{
	pr_info("jprobe: root = %p, memcg = %p\n", root, memcg);
	jprobe_return();
	return 0;
}

static struct jprobe my_jprobe = {
	.entry			= j_mem_cgroup_low,
	.kp = {
		.symbol_name	= "mem_cgroup_low",
	},
};

static int __init debug_mem_cgroup_low_init(void)
{
	int ret;

	ret = register_jprobe(&my_jprobe);
	if (ret < 0) {
		printk(KERN_INFO "register_jprobe failed, returned %d\n", ret);
		return -1;
	}

	printk(KERN_ALERT "[Hello] debug_mem_cgroup_low \n");
	printk(KERN_INFO "Planted jprobe at %p, handler addr %p\n",
	       my_jprobe.kp.addr, my_jprobe.entry);
	return 0;
}

static void __exit debug_mem_cgroup_low_exit(void)
{
	unregister_jprobe(&my_jprobe);
	printk(KERN_ALERT "[Goodbye] debug_mem_cgroup_low\n");
}

module_init(debug_mem_cgroup_low_init);
module_exit(debug_mem_cgroup_low_exit);
MODULE_LICENSE("GPL");
