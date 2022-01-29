/***********************************************
 * module : hack_meminfo
 *
 * Wang Long (w@laoqinren.net)
 **********************************************/
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/spinlock.h>
#include <linux/kallsyms.h>
#include <linux/proc_fs.h>
#include <linux/seq_file.h>
#include <linux/pid_namespace.h>
#include <linux/memcontrol.h>
#include <linux/swap.h>
#include <linux/mman.h>
#include <linux/hugetlb.h>


struct proc_dir_entry {
	unsigned long unused[7];
	int (*single_show)(struct seq_file *, void *);
};
/*
struct proc_dir_entry {
    atomic_t in_use;
    refcount_t refcnt;
    struct list_head pde_openers;
    spinlock_t pde_unload_lock;
    struct completion *pde_unload_completion;
    const struct inode_operations *proc_iops;
    const struct file_operations *proc_fops;
    union {
        const struct seq_operations *seq_ops;
        int (*single_show)(struct seq_file *, void *);
    };
    proc_write_t write;
    void *data;
    unsigned int state_size;
    unsigned int low_ino;
    nlink_t nlink;
    kuid_t uid;
    kgid_t gid;
    loff_t size;
    struct proc_dir_entry *parent;
    struct rb_root subdir;
    struct rb_node subdir_node;
    char *name;
    umode_t mode;
    u8 namelen;
    char inline_name[];
};*/

struct proc_dir_entry *de;
typedef int (*my_meminfo_proc_show)(struct seq_file *m, void *v);
my_meminfo_proc_show meminfo_proc_show_bak;

typedef  struct proc_dir_entry *(*my_pde_subdir_find)(struct proc_dir_entry *dir,
                                              const char *name,
                                              unsigned int len);
void __attribute__((weak)) arch_report_meminfo(struct seq_file *m)
{
}

static int my_meminfo_proc_show1(struct seq_file *m, void *v)
{
        struct sysinfo i;
        unsigned long committed;
        long cached;
        long available;
        unsigned long pages[NR_LRU_LISTS];
        int lru;
        bool instance_view = false;
        struct mem_cgroup *memcg = NULL;

        if (in_noninit_pid_ns(current) &&
                !mem_cgroup_disabled()) {
                instance_view = true;
                memcg = mem_cgroup_from_task(current);
        }   
        if (!instance_view) {
                si_meminfo(&i);
                //si_swapinfo(&i);
                cached = global_node_page_state(NR_FILE_PAGES) -
                        i.bufferram;
//                        total_swapcache_pages() - i.bufferram;
                if (cached < 0)
                        cached = 0;

                for (lru = LRU_BASE; lru < NR_LRU_LISTS; lru++)
                        pages[lru] = global_node_page_state(NR_LRU_BASE + lru);
                available = si_mem_available();
        } else {
              //  cgroup_mem_sw_info(&i, memcg, &cached, pages);
                available = i.freeram;
        }   
        committed = vm_memory_committed();


        if (instance_view) {
                cached = available = 0;
        } else {
                cached = available = 1;
        }   
        seq_printf(m, "MemTotal:       %8lu kB\n", i.totalram << (PAGE_SHIFT - 10));
        seq_printf(m, "MemFree:        %8lu kB\n", i.freeram<< (PAGE_SHIFT - 10));
        seq_printf(m, "MemAvailable:   %8lu kB\n", available<< (PAGE_SHIFT - 10));
        seq_printf(m, "Buffers:        %8lu kB\n", i.bufferram<< (PAGE_SHIFT - 10));
        seq_printf(m, "Cached:         %8lu kB\n", cached<< (PAGE_SHIFT - 10));
        seq_printf(m, "SwapCached:     %8lu kB\n", 0ul); //XX
        seq_printf(m, "Active:         %8lu kB\n", (pages[LRU_ACTIVE_ANON] +
                                           pages[LRU_ACTIVE_FILE])<< (PAGE_SHIFT - 10));
        seq_printf(m, "Inactive:       %8lu kB\n", (pages[LRU_INACTIVE_ANON] +
                                           pages[LRU_INACTIVE_FILE])<< (PAGE_SHIFT - 10));
        seq_printf(m, "Active(anon):   %8lu kB\n", pages[LRU_ACTIVE_ANON]<< (PAGE_SHIFT - 10));
        seq_printf(m, "Inactive(anon): %8lu kB\n", pages[LRU_INACTIVE_ANON]<< (PAGE_SHIFT - 10));
        seq_printf(m, "Active(file):   %8lu kB\n", pages[LRU_ACTIVE_FILE]<< (PAGE_SHIFT - 10));
        seq_printf(m, "Inactive(file): %8lu kB\n", pages[LRU_INACTIVE_FILE]<< (PAGE_SHIFT - 10));
        seq_printf(m, "Unevictable:    %8lu kB\n", pages[LRU_UNEVICTABLE]<< (PAGE_SHIFT - 10));
        seq_printf(m, "Mlocked:        %8lu kB\n", global_zone_page_state(NR_MLOCK) << (PAGE_SHIFT - 10));

#ifdef CONFIG_HIGHMEM
        seq_printf(m, "HighTotal:      %8lu kB\n", i.totalhigh << (PAGE_SHIFT - 10));
        seq_printf(m, "HighFree:       %8lu kB\n", i.freehigh << (PAGE_SHIFT - 10));
        seq_printf(m, "LowTotal:       %8lu kB\n", (i.totalram - i.totalhigh ) << (PAGE_SHIFT - 10));
        seq_printf(m, "LowFree:        %8lu kB\n", (i.freeram - i.freehigh) << (PAGE_SHIFT - 10));
#endif

#ifndef CONFIG_MMU
        seq_printf(m, "MmapCopy:       %8lu kB\n",
                    (unsigned long)atomic_long_read(&mmap_pages_allocated) << (PAGE_SHIFT - 10));
#endif

        seq_printf(m, "SwapTotal:      %8lu kB\n", i.totalswap << (PAGE_SHIFT - 10)); //XX
        seq_printf(m, "SwapFree:       %8lu kB\n", i.freeswap << (PAGE_SHIFT - 10)); //XX
        seq_printf(m, "Dirty:          %8lu kB\n",
                    global_node_page_state(NR_FILE_DIRTY)<< (PAGE_SHIFT - 10));
        seq_printf(m, "Writeback:      %8lu kB\n",
                    global_node_page_state(NR_WRITEBACK)<< (PAGE_SHIFT - 10));
        seq_printf(m, "AnonPages:      %8lu kB\n",
                    global_node_page_state(NR_ANON_MAPPED)<< (PAGE_SHIFT - 10));
        seq_printf(m, "Mapped:         %8lu kB\n",
                    global_node_page_state(NR_FILE_MAPPED)<< (PAGE_SHIFT - 10));
        seq_printf(m, "Shmem:          %8lu kB\n", i.sharedram << (PAGE_SHIFT - 10));
        seq_printf(m, "Slab:           %8lu kB\n",
                    (global_node_page_state(NR_SLAB_RECLAIMABLE) +
                    global_node_page_state(NR_SLAB_UNRECLAIMABLE))<< (PAGE_SHIFT - 10));

        seq_printf(m, "SReclaimable:   %8lu kB\n",
                    global_node_page_state(NR_SLAB_RECLAIMABLE)<< (PAGE_SHIFT - 10));
        seq_printf(m, "SUnreclaim:     %8lu kB\n",
                    global_node_page_state(NR_SLAB_UNRECLAIMABLE)<< (PAGE_SHIFT - 10));
        seq_printf(m, "KernelStack:    %8lu kB\n",
                   global_zone_page_state(NR_KERNEL_STACK_KB)<< (PAGE_SHIFT - 10));
        seq_printf(m, "PageTables:     %8lu kB\n",
                    global_zone_page_state(NR_PAGETABLE) << (PAGE_SHIFT - 10));
#ifdef CONFIG_QUICKLIST
        seq_printf(m, "Quicklists:     %8lu kB\n", quicklist_total_size()<< (PAGE_SHIFT - 10));
#endif

        seq_printf(m, "NFS_Unstable:   %8lu kB\n",
                    global_node_page_state(NR_UNSTABLE_NFS)<< (PAGE_SHIFT - 10));
        seq_printf(m, "Bounce:         %8lu kB\n",
                    global_zone_page_state(NR_BOUNCE)<< (PAGE_SHIFT - 10) );
        seq_printf(m, "WritebackTmp:   %8lu kB\n",
                    global_node_page_state(NR_WRITEBACK_TEMP) << (PAGE_SHIFT - 10));
        seq_printf(m, "CommitLimit:    %8lu kB\n", 0ul); //XX
        seq_printf(m, "Committed_AS:   %8lu kB\n", committed << (PAGE_SHIFT - 10));
        seq_printf(m, "VmallocTotal:   %8lu kB\n",
                   (unsigned long)VMALLOC_TOTAL >> 10);
        seq_printf(m, "VmallocUsed:    %8lu kB\n", 0ul);
        seq_printf(m, "VmallocChunk:   %8lu kB\n", 0ul);

#ifdef CONFIG_MEMORY_FAILURE
        seq_printf(m, "HardwareCorrupted: %5lu kB\n", 0ul); //XX
#endif

#ifdef CONFIG_TRANSPARENT_HUGEPAGE
        seq_printf(m, "AnonHugePages:  %8lu kB\n",
                    (global_node_page_state(NR_ANON_THPS) * HPAGE_PMD_NR) << (PAGE_SHIFT - 10));
        seq_printf(m, "ShmemHugePages: %8lu kB\n",
                    (global_node_page_state(NR_SHMEM_THPS) * HPAGE_PMD_NR) << (PAGE_SHIFT - 10));
        seq_printf(m, "ShmemPmdMapped: %8lu kB\n",
                    (global_node_page_state(NR_SHMEM_PMDMAPPED) * HPAGE_PMD_NR)<< (PAGE_SHIFT - 10));
#endif

#ifdef CONFIG_CMA
        seq_printf(m, "CmaTotal:       %8lu kB\n", totalcma_pages << (PAGE_SHIFT - 10));
        seq_printf(m, "CmaFree:        %8lu kB\n",
                    global_zone_page_state(NR_FREE_CMA_PAGES) << (PAGE_SHIFT - 10));
#endif

        //hugetlb_report_meminfo(m);

        arch_report_meminfo(m);

        return 0;
}

static int __init hack_meminfo_init(void)
{
	rwlock_t *proc_subdir_lock = (rwlock_t *)kallsyms_lookup_name("proc_subdir_lock");
	struct proc_dir_entry *proc_root = (struct proc_dir_entry *)kallsyms_lookup_name("proc_root");
	my_pde_subdir_find pde_subdir_find1 =  (my_pde_subdir_find)kallsyms_lookup_name("pde_subdir_find");

	printk(KERN_ALERT "[Hello] hack_meminfo \n");
	printk(KERN_DEBUG "proc_subdir_lock = %lx\n", (unsigned long)proc_subdir_lock);
	printk(KERN_DEBUG "proc_root = %lx\n", (unsigned long)proc_root);
	printk(KERN_DEBUG "pde_subdir_find = %lx\n", (unsigned long)pde_subdir_find1);

	read_lock(proc_subdir_lock);
	de = pde_subdir_find1(proc_root, "meminfo", 7);
	read_unlock(proc_subdir_lock);
	meminfo_proc_show_bak = de->single_show;

	printk(KERN_ALERT "de = %lx\n", (unsigned long)de);
	printk(KERN_ALERT "de->single_show = %lx\n", (unsigned long)(de->single_show));
	de->single_show = my_meminfo_proc_show1;
	return 0;
}

static void __exit hack_meminfo_exit(void)
{
	de->single_show = meminfo_proc_show_bak;
	printk(KERN_ALERT "[Goodbye] hack_meminfo\n");
}

module_init(hack_meminfo_init);
module_exit(hack_meminfo_exit);
MODULE_LICENSE("GPL");
