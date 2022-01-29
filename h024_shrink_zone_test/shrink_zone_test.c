/***********************************************
 * module : shrink_zone_test
 *
 * Wang Long (wanglong@laoqinren.net)
 **********************************************/
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/mmzone.h>
#include <linux/kallsyms.h>

#define for_each_zone1(zone)                             \
        for (zone = (first_online_pgdat2())->node_zones; \
             zone;                                      \
             zone = next_zone2(zone))

typedef struct pglist_data* (*first_online_pgdat1)(void);
typedef struct zone* (*next_zone1)(struct zone *zone);
typedef int(*zone_reclaim)(struct zone *zone, gfp_t gfp_mask, unsigned int order);

static int __init shrink_zone_test_init(void)
{
	struct zone *z;
	printk(KERN_ALERT "[Hello] shrink_zone_test \n");
	first_online_pgdat1 first_online_pgdat2;
	next_zone1 next_zone2;
	zone_reclaim zone_reclaim2;
	next_zone2 = kallsyms_lookup_name("next_zone");
	first_online_pgdat2 = kallsyms_lookup_name("first_online_pgdat");
	zone_reclaim2 = kallsyms_lookup_name("zone_reclaim");

	for_each_zone1(z) {
		printk(KERN_ALERT "node= %d, name = %s \n", z->node, z->name);
		zone_reclaim2(z, GFP_KERNEL, 2);
	}

	return 0;
}

static void __exit shrink_zone_test_exit(void)
{
	printk(KERN_ALERT "[Goodbye] shrink_zone_test\n");
}

module_init(shrink_zone_test_init);
module_exit(shrink_zone_test_exit);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("datawolf");
