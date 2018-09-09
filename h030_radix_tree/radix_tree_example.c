/***********************************************
 * module : radix_tree_example
 *
 * Wang Long (w@laoqinren.net)
 **********************************************/
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/radix-tree.h>

static RADIX_TREE(mytree, GFP_KERNEL);

static int __init radix_tree_example_init(void)
{
	char a[40] = "hello, radix tree";
	radix_tree_insert(&mytree, 0, (void *)a);
	radix_tree_insert(&mytree, 4, (void *)a);
	radix_tree_insert(&mytree, 131, (void *)a);
	radix_tree_insert(&mytree, 4096, (void *)a);

	radix_tree_lookup(&mytree, 1);
	printk(KERN_ALERT "[Hello] radix_tree_example \n");
	return 0;
}

static void __exit radix_tree_example_exit(void)
{
	radix_tree_delete(&mytree, 0);
	radix_tree_delete(&mytree, 4);
	radix_tree_delete(&mytree, 131);
	radix_tree_delete(&mytree, 4096);
	printk(KERN_ALERT "[Goodbye] radix_tree_example\n");
}

module_init(radix_tree_example_init);
module_exit(radix_tree_example_exit);
MODULE_LICENSE("GPL");
