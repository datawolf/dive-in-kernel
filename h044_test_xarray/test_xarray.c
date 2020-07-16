/***********************************************
 * module : test_xarray
 *
 * Wang Long (w@laoqinren.net)
 **********************************************/
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/xarray.h>

void xa_dump_node(const struct xa_node *node)
{
	unsigned i, j;

	if (!node)
		return;
	if ((unsigned long)node & 3) {
		pr_cont("node %px\n", node);
		return;
	}

	pr_cont("node %px %s %d parent %px shift %d count %d values %d "
		"array %px list %px %px marks",
		node, node->parent ? "offset" : "max", node->offset,
		node->parent, node->shift, node->count, node->nr_values,
		node->array, node->private_list.prev, node->private_list.next);
	for (i = 0; i < XA_MAX_MARKS; i++)
		for (j = 0; j < XA_MARK_LONGS; j++)
			pr_cont(" %lx", node->marks[i][j]);
	pr_cont("\n");
}

void xa_dump_index(unsigned long index, unsigned int shift)
{
	if (!shift)
		pr_info("%lu: ", index);
	else if (shift >= BITS_PER_LONG)
		pr_info("0-%lu: ", ~0UL);
	else
		pr_info("%lu-%lu: ", index, index | ((1UL << shift) - 1));
}

void xa_dump_entry(const void *entry, unsigned long index, unsigned long shift)
{
	if (!entry)
		return;

	xa_dump_index(index, shift);

	if (xa_is_node(entry)) {
		if (shift == 0) {
			pr_cont("%px\n", entry);
		} else {
			unsigned long i;
			struct xa_node *node = xa_to_node(entry);
			xa_dump_node(node);
			for (i = 0; i < XA_CHUNK_SIZE; i++)
				xa_dump_entry(node->slots[i],
				      index + (i << node->shift), node->shift);
		}
	} else if (xa_is_value(entry))
		pr_cont("value %ld (0x%lx) [%px]\n", xa_to_value(entry),
						xa_to_value(entry), entry);
	else if (!xa_is_internal(entry))
		pr_cont("%px\n", entry);
	else if (xa_is_retry(entry))
		pr_cont("retry (%ld)\n", xa_to_internal(entry));
	else if (xa_is_sibling(entry))
		pr_cont("sibling (slot %ld)\n", xa_to_sibling(entry));
	else if (xa_is_zero(entry))
		pr_cont("zero (%ld)\n", xa_to_internal(entry));
	else
		pr_cont("UNKNOWN ENTRY (%px)\n", entry);
}

void xa_dump(const struct xarray *xa)
{
	void *entry = xa->xa_head;
	unsigned int shift = 0;

	pr_info("xarray: %px head %px flags %x marks %d %d %d\n", xa, entry,
			xa->xa_flags, xa_marked(xa, XA_MARK_0),
			xa_marked(xa, XA_MARK_1), xa_marked(xa, XA_MARK_2));
	if (xa_is_node(entry))
		shift = xa_to_node(entry)->shift + XA_CHUNK_SHIFT;
	xa_dump_entry(entry, 0, shift);
}
static DEFINE_XARRAY(array);

static void *xa_mk_index(unsigned long index)
{
	return xa_mk_value(index & LONG_MAX);
}

static void *xa_store_index(struct xarray *xa, unsigned long index, gfp_t gfp)
{
	return xa_store(xa, index, xa_mk_index(index), gfp);
}


static int __init test_xarray_init(void)
{
	printk(KERN_ALERT "[Hello] test_xarray \n");

	printk(KERN_ALERT "##### empty \n");
	xa_dump(&array);

	printk(KERN_ALERT "##### insert 0\n");
	xa_store_index(&array, 0, 0);
	xa_dump(&array);

	printk(KERN_ALERT "##### insert 4 \n");
	xa_store_index(&array, 4, 0);
	xa_dump(&array);

	printk(KERN_ALERT "##### insert 131 \n");
	xa_store_index(&array, 131, 0);
	xa_dump(&array);

	printk(KERN_ALERT "##### insert 4100 \n");
	xa_store_index(&array, 4100, 0);
	xa_dump(&array);

	return 0;
}

static void __exit test_xarray_exit(void)
{
	xa_destroy(&array);
	printk(KERN_ALERT "[Goodbye] test_xarray\n");
}

module_init(test_xarray_init);
module_exit(test_xarray_exit);
MODULE_LICENSE("GPL");
