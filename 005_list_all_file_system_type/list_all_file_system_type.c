/***********************************************
 * module : list_all_file_system_type 
 * 
 * datawolf (wanglong@cse.buaa.edu.cn)
 **********************************************/
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/kallsyms.h>
#include <linux/fs.h>

static int __init list_all_file_system_type_init(void)
{
	char *sym_name = "file_systems";
    	unsigned long sym_addr = kallsyms_lookup_name(sym_name);
	struct file_system_type **tmp;
//	"file_systems"  address :ffffffff8201f928
	struct file_system_type *fst = (struct file_system_type *) sym_addr ;
//	const char * symbol_name;
//	void *addr;
//	symbol_name = "__symbol_get";
//	addr = __symbol_get(symbol_name);

/*	
	if (addr != NULL)	
		printk(KERN_ALERT "the address of file_systems is: %lx\n", (unsigned long)addr);
	else
		printk(KERN_ALERT "is not found");
*/
	tmp = &fst;
	while (*tmp){
		printk(KERN_ALERT "file system type : %s\n", (*tmp)->name);
		tmp = &(*tmp)->next;
	}
	
	printk(KERN_ALERT "*****************************************\n");
	printk(KERN_ALERT "file system type : %lx\n", sym_addr);
	printk(KERN_ALERT "file system type : %s\n", fst->name);

	if (fst->next == NULL)
		printk(KERN_ALERT "NULL\n");
	while (fst->next != NULL){
		printk(KERN_ALERT "file system type : %s\n", fst->name);
		fst = fst->next;	
	}
	
	 return 0;
}

static void __exit list_all_file_system_type_exit(void)
{
	printk(KERN_ALERT "[goodbye] list_all_file_system_type\n");
}

module_init(list_all_file_system_type_init);
module_exit(list_all_file_system_type_exit);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("datawolf");
