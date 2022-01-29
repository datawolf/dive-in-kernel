#define pr_fmt(fmt) KBUILD_MODNAME ": " fmt
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/kprobes.h>

static int can_attach_handler(struct kretprobe_instance *ri,
			      struct pt_regs *regs)
{
	return 0;
}

static int attach_handler(struct kretprobe_instance *ri, struct pt_regs *regs)
{
	return 0;
}

static int enqueue_task_fair_handler(struct kretprobe_instance *ri,
				     struct pt_regs *regs)
{
	return 0;
}

static int dequeue_task_fair_handler(struct kretprobe_instance *ri,
				     struct pt_regs *regs)
{
	return 0;
}

static struct kretprobe rp1 = {
	.entry_handler  = attach_handler,
	.kp.symbol_name = "cpuacct_attach"
};

static struct kretprobe rp2 = {
	.entry_handler  = can_attach_handler,
	.kp.symbol_name = "cpuacct_can_attach"
};

static struct kretprobe rp3 = {
	.entry_handler  = enqueue_task_fair_handler,
	.kp.symbol_name = "enqueue_task_fair"
};

static struct kretprobe rp4 = {
	.entry_handler  = dequeue_task_fair_handler,
	.kp.symbol_name = "dequeue_task_fair"
};

static struct kretprobe *rps[] = {&rp1, &rp2, &rp3, &rp4};

static int __init sched_bug_init(void)
{
	int ret;

	ret = register_kretprobes(rps, sizeof(rps) / sizeof(*rps));
	if (ret < 0) {
		pr_info("register_kretprobes failed, returned %d\n", ret);
		return ret;
	}

	return 0;
}

static void __exit sched_bug_exit(void)
{
	unregister_kretprobes(rps, sizeof(rps) / sizeof(*rps));
}

module_init(sched_bug_init);
module_exit(sched_bug_exit);
MODULE_LICENSE("GPL");
