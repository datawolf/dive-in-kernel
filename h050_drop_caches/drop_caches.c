/***********************************************
 * module : drop_caches
 *
 * Wang Long (w@laoqinren.net)
 **********************************************/
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/mnt_namespace.h>
#include <linux/kallsyms.h>
#include <linux/mount.h>
#include <linux/pid.h>
#include <linux/memcontrol.h>
#include <linux/nsproxy.h>

static int pid = 1;
module_param(pid, int, 0444);

#if defined(MTOS_130)

struct mnt_namespace {
	atomic_t		count;
	unsigned int		proc_inum;
	struct mount *	root;
	struct list_head	list;
	struct user_namespace	*user_ns;
	struct ucounts		*ucounts;
	u64			seq;	/* Sequence number to prevent loops */
	wait_queue_head_t poll;
	u64 event;
	RH_KABI_EXTEND(unsigned int	mounts) /* # of mounts in the namespace */
	RH_KABI_EXTEND(unsigned int	pending_mounts)
};

struct mount {
	struct hlist_node mnt_hash;
	struct mount *mnt_parent;
	struct dentry *mnt_mountpoint;
	struct vfsmount mnt;
	union {
		struct rcu_head mnt_rcu;
		struct llist_node mnt_llist;
	};
#ifdef CONFIG_SMP
	struct mnt_pcp __percpu *mnt_pcp;
#else
	int mnt_count;
	int mnt_writers;
#endif
	struct list_head mnt_mounts;	/* list of children, anchored here */
	struct list_head mnt_child;	/* and going through their mnt_child */
	struct list_head mnt_instance;	/* mount instance on sb->s_mounts */
	const char *mnt_devname;	/* Name of device e.g. /dev/dsk/hda1 */
	struct list_head mnt_list;
	//...
};
#else
struct mnt_namespace {
        atomic_t                count;
        struct ns_common        ns; 
        struct mount *  root;
        struct list_head        list;
        struct user_namespace   *user_ns;
        struct ucounts          *ucounts;
        u64                     seq;    /* Sequence number to prevent loops */
        wait_queue_head_t poll;
        u64 event;
        unsigned int            mounts; /* # of mounts in the namespace */
        unsigned int            pending_mounts;
} __randomize_layout;

//struct mnt_pcp { 
//	int mnt_count;
//	int mnt_writers; 
//};

struct mount {
	struct hlist_node mnt_hash; 
	struct mount *mnt_parent;
	struct vfsmount mnt; 
	union { 
		struct rcu_head mnt_rcu;   
		struct llist_node mnt_llist;
	};
#ifdef CONFIG_SMP
	struct mnt_pcp __percpu *mnt_pcp; 
#else
	int mnt_count; 
	int mnt_writers; 
#endif
	struct list_head mnt_mounts;
	struct list_head mnt_child;
	struct list_head mnt_instance;
	const char *mnt_devname;
	struct list_head mnt_list;
	//...
}__randomize_layout;
#endif

spinlock_t *orig_sb_lock;
struct rw_semaphore *orig_namespace_sem;
struct mem_cgroup **orig_root_mem_cgroup;
#if defined(MTOS_130)
unsigned long (*orig_shrink_slab)(struct shrink_control *shrink,
			  unsigned long nr_pages_scanned,
			  unsigned long lru_pages);
#else
unsigned long (*orig_shrink_slab)(gfp_t gfp_mask, int nid,
				struct mem_cgroup *memcg,
				int priority);
#endif

void (*orig_drop_pagecache_sb)(struct super_block *, void *);
void (*orig_put_super)(struct super_block *sb);
struct mem_cgroup * (*orig_mem_cgroup_from_task)(struct task_struct *p);

#define LOOKUP_SYMS(name) do {			                                 \
                orig_##name = (void *)kallsyms_lookup_name(#name);            \
                if (!orig_##name) {                                             \
                        pr_err("kallsyms_lookup_name: %s\n", #name);            \
                        return -EINVAL;                                         \
                }                                                               \
        } while (0)


void mtos_drop_slab(struct task_struct *tk)
{
#if defined(MTOS_130)

	// copy from: http://xr-hulk-k8s-node1931.gh.sankuai.com/mtkernel/mt20190308.130.862/source/fs/drop_caches.c#L42
	int nr_objects;
	struct shrink_control shrink = {
		.gfp_mask = GFP_KERNEL,
	};

	do {
		nr_objects = orig_shrink_slab(&shrink, 1000, 1000);
	} while (nr_objects > 10);
#else

	// ref: http://xr-hulk-k8s-node1931.gh.sankuai.com/mtkernel/v4.18-mt20191225.323/source/mm/vmscan.c#L563
	int nid;
	struct mem_cgroup *memcg = NULL;

	rcu_read_lock();
	memcg = orig_mem_cgroup_from_task(tk);
	if (memcg)
		css_get(&memcg->css); //get css
	rcu_read_unlock();

	for_each_online_node(nid)
		orig_shrink_slab(GFP_KERNEL, nid, memcg, 0);

	rcu_read_lock();
	if (memcg)
		css_put(&memcg->css); // put css
	rcu_read_unlock();
#endif
}

void drop_one_sb(struct super_block * sb)
{
	spin_lock(orig_sb_lock);
	if (hlist_unhashed(&sb->s_instances)) {
		spin_unlock(orig_sb_lock);
		return;
	}
	sb->s_count++; //get
	spin_unlock(orig_sb_lock);

	down_read(&sb->s_umount);
	if (sb->s_root && (sb->s_flags & MS_BORN)) {
		printk(KERN_INFO "dev_t: %d,%d fs_name: %s name: %s", 
			MAJOR(sb->s_dev),
			MINOR(sb->s_dev),
			sb->s_type->name,
			sb->s_id);
		orig_drop_pagecache_sb(sb, NULL);
	}
	up_read(&sb->s_umount);

	orig_put_super(sb); //put
}

void mtos_drop_pagecache(struct task_struct* tk)
{
	struct mnt_namespace *ns = tk->nsproxy->mnt_ns;
	struct mount *m;
	struct super_block *sb;
	struct mem_cgroup *memcg = NULL;

	rcu_read_lock();
	memcg = orig_mem_cgroup_from_task(tk);
	if (memcg)
		css_get(&memcg->css); // get css
	rcu_read_unlock();

	down_read(orig_namespace_sem);
	list_for_each_entry(m, &ns->list, mnt_list) {
		sb = m->mnt.mnt_sb;
		if (memcg != *orig_root_mem_cgroup){
			//容器里，只drop 系统盘和数据盘
			if (!strcmp("ext4", sb->s_type->name))
				drop_one_sb(sb);
		} else {
			//宿主机上，只drop sda和sdb
			if (!strncmp("/dev/sda", m->mnt_devname, 8))
				drop_one_sb(sb);
			if (!strncmp("/dev/sdb", m->mnt_devname, 8))
				drop_one_sb(sb);
		}
	}
	up_read(orig_namespace_sem);

	rcu_read_lock();
	if (memcg)
		css_put(&memcg->css); //put css
	rcu_read_unlock();
}

static int __init drop_caches_init(void)
{
	pid_t p = (pid_t)pid; 
	struct task_struct *tk = get_pid_task(find_get_pid(p), PIDTYPE_PID);

	LOOKUP_SYMS(drop_pagecache_sb);
	LOOKUP_SYMS(mem_cgroup_from_task);
	LOOKUP_SYMS(shrink_slab);
	LOOKUP_SYMS(put_super);
	orig_sb_lock = (spinlock_t *)kallsyms_lookup_name("sb_lock");
	orig_namespace_sem = (struct rw_semaphore *)kallsyms_lookup_name("namespace_sem");
	orig_root_mem_cgroup = (struct mem_cgroup **)kallsyms_lookup_name("root_mem_cgroup");

	printk(KERN_ALERT "[Hello] drop_caches \n");

	mtos_drop_pagecache(tk);
	mtos_drop_slab(tk);
	return 0;
}

static void __exit drop_caches_exit(void)
{
	printk(KERN_ALERT "[Goodbye] drop_caches\n");
}

module_init(drop_caches_init);
module_exit(drop_caches_exit);
MODULE_LICENSE("GPL");
