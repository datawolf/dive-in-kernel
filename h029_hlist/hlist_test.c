/***********************************************
 * module : hlist_test
 *
 * Wang Long (w@laoqinren.net)
 **********************************************/
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/list.h>

struct node {
	int val;
	struct hlist_node list;
};

static int __init hlist_test_init(void)
{
	struct hlist_head  head;
	struct node a, b, c, d, e;
	struct node *pos;
	struct hlist_node *p;

	printk(KERN_ALERT "[Hello] hlist_test \n");

	INIT_HLIST_HEAD(&head); //初始化链表头
	a.val = 1;
	b.val = 2;
	c.val = 3;
	d.val = 4;
	e.val = 5;

	hlist_add_head(&a.list, &head); //添加节点
	hlist_add_head(&b.list, &head);
	hlist_add_head(&c.list, &head);

	printk(KERN_ALERT "-------------------------------------- \n");
	//遍历链表，打印结果 方法1
	hlist_for_each_entry(pos, &head, list) {
		printk(KERN_ALERT "node.val = %d\n", pos->val);
	} // print 3 2 1

	printk(KERN_ALERT "-------------------------------------- \n");
	// 遍历链表，打印结果 方法2
	hlist_for_each(p, &head) {
		pos = hlist_entry(p, struct node, list);
		printk(KERN_ALERT "node.val = %d\n", pos->val);
	} // print 3 2 1

	printk(KERN_ALERT "-------------------------------------- \n");
	hlist_del_init(&b.list); // 删除中间节点
	hlist_for_each_entry(pos, &head, list) {
		printk(KERN_ALERT "node.val = %d\n", pos->val);
	} // print 3 1

	printk(KERN_ALERT "-------------------------------------- \n");
	hlist_add_before(&d.list, &a.list); //在最后一个节点之前添加新节点
	hlist_for_each_entry(pos, &head, list) {
		printk(KERN_ALERT "node.val = %d\n", pos->val);
	} // print 3 4 1

	printk(KERN_ALERT "-------------------------------------- \n");
	hlist_add_behind(&e.list, &a.list);//在最后一个节点之后添加新节点
	hlist_for_each_entry(pos, &head, list) {
		printk(KERN_ALERT "node.val = %d\n", pos->val);
	} // print 3 4 1 5

	return 0;
}

static void __exit hlist_test_exit(void)
{
	printk(KERN_ALERT "[Goodbye] hlist_test\n");
}

module_init(hlist_test_init);
module_exit(hlist_test_exit);
MODULE_LICENSE("GPL");
