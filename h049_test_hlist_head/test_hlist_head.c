/***********************************************
 * module : test_hlist_head
 *
 * Wang Long (w@laoqinren.net)
 **********************************************/
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/list.h>


struct hlist_head  head1;
struct hlist_head  head2;
struct hlist_head  head3;

struct test_inet_tw_sock {
	int val;
	struct hlist_node list;
};

void detach_inet_tw (struct test_inet_tw_sock *tw)
{
	struct hlist_node *entry = &tw->list;

	__hlist_del(entry);

	entry->next = LIST_POISON2;
}

static int __init test_hlist_head_init(void)
{
	struct test_inet_tw_sock tw;
	struct test_inet_tw_sock *pos;
	printk(KERN_ALERT "[Hello] test_hlist_head \n");

	tw.val = 3;

	INIT_HLIST_HEAD(&head1);
	INIT_HLIST_HEAD(&head2);
	INIT_HLIST_HEAD(&head3);

	hlist_add_head(&tw.list, &head1);
	tw.val = 4;
	hlist_add_head(&tw.list, &head2);

	printk(KERN_ALERT "head1->first = %px\n", head1.first);
	hlist_for_each_entry(pos, &head1, list) {
		printk(KERN_ALERT "node addr = %px, node.val = %d\n", pos,  pos->val);
	}

	printk(KERN_ALERT "head2->first = %px\n", head2.first);
	hlist_for_each_entry(pos, &head2, list) {
		printk(KERN_ALERT "node addr = %px, node.val = %d\n", pos,  pos->val);
	}


	//detach 
	detach_inet_tw(&tw);
	printk(KERN_ALERT "==========After detach============\n");
	printk(KERN_ALERT "head1->first = %px\n", head1.first);
	printk(KERN_ALERT "head2->first = %px\n", head2.first);
	printk(KERN_ALERT "tw->next = %px\n", tw.list.next);
	printk(KERN_ALERT "tw->pprev = %px\n", *(tw.list.pprev));

	
//	hlist_for_each_entry(pos, &head1, list) {
//		printk(KERN_ALERT "node addr = %px, node.val = %d\n", pos,  pos->val);
//	}

//	hlist_for_each_entry(pos, &head2, list) {
//		printk(KERN_ALERT "node addr = %px, node.val = %d\n", pos,  pos->val);
//	}


	hlist_move_list(&head1, &head3);
	printk(KERN_ALERT "==========After Move============\n");
	printk(KERN_ALERT "head1->first = %px\n", head1.first);
	printk(KERN_ALERT "head2->first = %px\n", head2.first);
	printk(KERN_ALERT "head3->first = %px\n", head3.first);
	printk(KERN_ALERT "tw->next = %px\n", tw.list.next);
	printk(KERN_ALERT "tw->pprev = %px\n", *(tw.list.pprev));

	printk(KERN_ALERT "==========Get tw============\n");

	while(!hlist_empty(&head3)) {
		pos = hlist_entry(head3.first, struct test_inet_tw_sock, list);
		printk(KERN_ALERT "head1->first = %px\n", head1.first);
		printk(KERN_ALERT "head2->first = %px\n", head2.first);
		printk(KERN_ALERT "head3->first = %px\n", head3.first);
		printk(KERN_ALERT "tw->next = %px\n", tw.list.next);
		printk(KERN_ALERT "tw->pprev = %px\n", *(tw.list.pprev));
		// only print the first
		break;
	}


	return 0;
}

static void __exit test_hlist_head_exit(void)
{
	printk(KERN_ALERT "[Goodbye] test_hlist_head\n");
}

module_init(test_hlist_head_init);
module_exit(test_hlist_head_exit);
MODULE_LICENSE("GPL");
