/***********************************************
 * module : test_irq
 *
 * Wang Long (w@laoqinren.net)
 **********************************************/
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/hrtimer.h>
#include <linux/cpu.h>
#include <linux/cpuhotplug.h>

struct timer_info  {
	int cpu;
	int count;
	struct hrtimer timer;
};

struct timer_info timer_infos[NR_CPUS];


static inline ktime_t __ms_to_ktime(u64 ms)
{
	return ms * NSEC_PER_MSEC;
}

static enum hrtimer_restart hrtimer_handler(struct hrtimer *hrtimer)
{
	enum hrtimer_restart ret = HRTIMER_RESTART;
	int cpu = smp_processor_id();
	struct timer_info  *t = container_of(hrtimer, struct timer_info, timer);

	if (in_irq()) {
		t->count++;
		if (t->count % 500 == 0) {
			printk(KERN_ALERT "[in irq], timer's cpu = %d, actual cpu = %d, hrtimer = %px, hrtimer[%d] = %px \n", t->cpu, cpu, hrtimer, cpu, &timer_infos[cpu].timer);
		}
	} else {
		printk(KERN_ALERT "[NOT in irq], timer's cpu = %d, actual cpu = %d, hrtimer = %px, hrtimer[%d] = %px \n", t->cpu, cpu, hrtimer, cpu, &timer_infos[cpu].timer);
	}

	hrtimer_forward_now(hrtimer, __ms_to_ktime(10));

	return ret;
}

static void start_timer(void *info)
{
	int cpu = smp_processor_id();
	struct hrtimer *timer = &timer_infos[cpu].timer;


	timer_infos[cpu].cpu = cpu;

	/* start per-cpu hrtimer */
	hrtimer_init(timer, CLOCK_MONOTONIC, HRTIMER_MODE_PINNED);
	timer->function = hrtimer_handler;
	hrtimer_start_range_ns(timer,
			__ms_to_ktime(10),
			0,
			HRTIMER_MODE_REL_PINNED /*HRTIMER_MODE_PINNED*/);

	printk(KERN_ALERT "hrtimer[%d] = %px\n", cpu, timer);
}

static enum cpuhp_state cpuhp_ret;

static int test_irq_online(unsigned int cpu)
{

	smp_call_function_single(cpu, start_timer, NULL, 1);

	return 0;

}

static int test_irq_offline(unsigned int cpu)
{

	hrtimer_cancel(&timer_infos[cpu].timer);

	return 0;
}

static int __init test_irq_init(void)
{
	printk(KERN_ALERT "[Hello] test_irq \n");

	on_each_cpu(start_timer, NULL, 1);

	cpuhp_ret = cpuhp_setup_state_nocalls(CPUHP_AP_ONLINE_DYN,
					"test_irq:on_off_line", test_irq_online,
					test_irq_offline);
	WARN_ON(cpuhp_ret < 0);
	return 0;
}

static void __exit test_irq_exit(void)
{
	int cpu;
	printk(KERN_ALERT "[Goodbye] test_irq\n");

	for_each_possible_cpu(cpu)
	{
		hrtimer_cancel(&timer_infos[cpu].timer);
	}

	cpuhp_remove_state_nocalls(cpuhp_ret);
}

module_init(test_irq_init);
module_exit(test_irq_exit);
MODULE_LICENSE("GPL");
