/***********************************************
 * module : mycapset_call
 *
 * Wang Long (w@laoqinren.net)
 **********************************************/
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/unistd.h>
#include <linux/time.h>
//#include <asm/uaccess.h>
#include <linux/sched.h>
#include <linux/kallsyms.h>
#include <linux/audit.h>
#include <linux/capability.h>
#include <linux/export.h>
#include <linux/security.h>
#include <linux/pid_namespace.h>
#include <linux/user_namespace.h>
#include <linux/uaccess.h>
#include <linux/cn_proc.h>
#include <linux/syscalls.h>


struct kmem_cache **ori_cred_jar;
int *ori_suid_dumpable;

void (*orig_free_uid)(struct user_struct *);
int (*orig_security_prepare_creds)(struct cred *new, const struct cred *old, gfp_t gfp);
void (*orig_set_dumpable)(struct mm_struct *mm, int value);
void (*orig_security_cred_free)(struct cred *cred);
void (*orig_key_fsuid_changed)(struct task_struct *tsk);
void (*orig_key_fsgid_changed)(struct task_struct *tsk);
void (*orig_proc_id_connector)(struct task_struct *task, int which_id);
const struct cred * (*orig_get_task_cred)(struct task_struct *);
struct task_struct* (*orig_find_task_by_vpid)(pid_t nr);
void (*orig___audit_log_capset)(const struct cred *new, const struct cred *old);
int (*orig_security_capset)(struct cred *new, const struct cred *old,
		    const kernel_cap_t *effective,
		    const kernel_cap_t *inheritable,
		    const kernel_cap_t *permitted);


#define LOOKUP_SYMS(name) do {			                                 \
                orig_##name = (void *)kallsyms_lookup_name(#name);            \
                if (!orig_##name) {                                             \
                        pr_err("kallsyms_lookup_name: %s\n", #name);            \
                        return -EINVAL;                                         \
                }                                                               \
        } while (0)

static inline void alter_cred_subscribers(const struct cred *_cred, int n)
{
#ifdef CONFIG_DEBUG_CREDENTIALS
	struct cred *cred = (struct cred *) _cred;

	atomic_add(n, &cred->subscribers);
#endif
}

static bool cred_cap_issubset(const struct cred *set, const struct cred *subset)
{
	const struct user_namespace *set_ns = set->user_ns;
	const struct user_namespace *subset_ns = subset->user_ns;

	/* If the two credentials are in the same user namespace see if
	 * the capabilities of subset are a subset of set.
	 */
	if (set_ns == subset_ns)
		return cap_issubset(subset->cap_permitted, set->cap_permitted);

	/* The credentials are in a different user namespaces
	 * therefore one is a subset of the other only if a set is an
	 * ancestor of subset and set->euid is owner of subset or one
	 * of subsets ancestors.
	 */
	for (;subset_ns != &init_user_ns; subset_ns = subset_ns->parent) {
		if ((set_ns == subset_ns->parent)  &&
		    uid_eq(subset_ns->owner, set->euid))
			return true;
	}

	return false;
}

static inline void set_cred_subscribers(struct cred *cred, int n)
{
#ifdef CONFIG_DEBUG_CREDENTIALS
	atomic_set(&cred->subscribers, n);
#endif
}


static void put_cred_rcu(struct rcu_head *rcu)
{
	struct cred *cred = container_of(rcu, struct cred, rcu);


#ifdef CONFIG_DEBUG_CREDENTIALS
	if (cred->magic != CRED_MAGIC_DEAD ||
	    atomic_read(&cred->usage) != 0 ||
	    read_cred_subscribers(cred) != 0)
		panic("CRED: put_cred_rcu() sees %p with"
		      " mag %x, put %p, usage %d, subscr %d\n",
		      cred, cred->magic, cred->put_addr,
		      atomic_read(&cred->usage),
		      read_cred_subscribers(cred));
#else
	if (atomic_read(&cred->usage) != 0)
		panic("CRED: put_cred_rcu() sees %p with usage %d\n",
		      cred, atomic_read(&cred->usage));
#endif

	orig_security_cred_free(cred);
	key_put(cred->session_keyring);
	key_put(cred->process_keyring);
	key_put(cred->thread_keyring);
	key_put(cred->request_key_auth);
	if (cred->group_info)
		put_group_info(cred->group_info);
	orig_free_uid(cred->user);
	put_user_ns(cred->user_ns);
	kmem_cache_free(*ori_cred_jar, cred);
}

static void warn_legacy_capability_use(void)
{
	char name[sizeof(current->comm)];

	pr_info_once("warning: `%s' uses 32-bit capabilities (legacy support in use)\n",
		     get_task_comm(name, current));
}

static void warn_deprecated_v2(void)
{
	char name[sizeof(current->comm)];

	pr_info_once("warning: `%s' uses deprecated v2 capabilities in a way that may be insecure\n",
		     get_task_comm(name, current));
}


static int cap_validate_magic(cap_user_header_t header, unsigned *tocopy)
{
	__u32 version;

	if (get_user(version, &header->version)) {
		pr_info("cap_validate_magic: get_user");
		return -EFAULT;
	}

	switch (version) {
	case _LINUX_CAPABILITY_VERSION_1:
		warn_legacy_capability_use();
		*tocopy = _LINUX_CAPABILITY_U32S_1;
		break;
	case _LINUX_CAPABILITY_VERSION_2:
		warn_deprecated_v2();
		/*
		 * fall through - v3 is otherwise equivalent to v2.
		 */
	case _LINUX_CAPABILITY_VERSION_3:
		*tocopy = _LINUX_CAPABILITY_U32S_3;
		break;
	default:
		if (put_user((u32)_KERNEL_CAPABILITY_VERSION, &header->version)) {
			pr_info("cap_validate_magic: put_user");
			return -EFAULT;
		}
		return -EINVAL;
	}

	return 0;
}

#define __NR_syscall  126	/* 系统调用号444 */

unsigned int clear_and_return_cr0(void);
void setback_cr0(unsigned int val);

int orig_cr0;	/* 用来存储cr0寄存器原来的值 */
unsigned long **mysys_call_table = 0;
//static int (*anything_saved)(void);	/*定义一个函数指针，用来保存一个系统调用*/
int (*anything_saved)(cap_user_header_t header, const cap_user_data_t data);
/*
 * 设置cr0寄存器的第17位为0
 */
unsigned int clear_and_return_cr0(void)	
{
	unsigned int cr0 = 0;
	unsigned int ret;
	/* 前者用在32位系统。后者用在64位系统，本系统64位 */
	//asm volatile ("movl %%cr0, %%eax" : "=a"(cr0));	
	asm volatile ("movq %%cr0, %%rax" : "=a"(cr0));	/* 将cr0寄存器的值移动到rax寄存器中，同时输出到cr0变量中 */
	ret = cr0;
	cr0 &= 0xfffeffff;	/* 将cr0变量值中的第17位清0，将修改后的值写入cr0寄存器 */
	//asm volatile ("movl %%eax, %%cr0" :: "a"(cr0));
	asm volatile ("movq %%rax, %%cr0" :: "a"(cr0));	/* 读取cr0的值到rax寄存器，再将rax寄存器的值放入cr0中 */
	return ret;
}

/* 读取val的值到rax寄存器，再将rax寄存器的值放入cr0中 */
void setback_cr0(unsigned int val)
{
	//asm volatile ("movl %%eax, %%cr0" :: "a"(val));
	asm volatile ("movq %%rax, %%cr0" :: "a"(val));
}

void __put_cred_hulk(struct cred *, struct task_struct *);
struct cred *prepare_creds_hulk(struct task_struct *);
int commit_creds_hulk(struct cred *, struct task_struct *);
void abort_creds_hulk(struct cred *, struct task_struct *);

static inline void put_cred_hulk(const struct cred *_cred, struct task_struct *t)
{
	struct cred *cred = (struct cred *) _cred;

	validate_creds(cred);
	if (atomic_dec_and_test(&(cred)->usage))
		__put_cred_hulk(cred, t);
}


int commit_creds_hulk(struct cred *new, struct task_struct *t)
{
	struct task_struct *task = t;
	const struct cred *old = task->real_cred;

	BUG_ON(task->cred != old);
#ifdef CONFIG_DEBUG_CREDENTIALS
	BUG_ON(read_cred_subscribers(old) < 2);
	validate_creds(old);
	validate_creds(new);
#endif
	BUG_ON(atomic_read(&new->usage) < 1);

	get_cred(new); /* we will require a ref for the subj creds too */

	/* dumpability changes */
	if (!uid_eq(old->euid, new->euid) ||
	    !gid_eq(old->egid, new->egid) ||
	    !uid_eq(old->fsuid, new->fsuid) ||
	    !gid_eq(old->fsgid, new->fsgid) ||
	    !cred_cap_issubset(old, new)) {
		if (task->mm)
			orig_set_dumpable(task->mm, *ori_suid_dumpable);
		task->pdeath_signal = 0;
		smp_wmb();
	}

	/* alter the thread keyring */
	if (!uid_eq(new->fsuid, old->fsuid))
		orig_key_fsuid_changed(task);
	if (!gid_eq(new->fsgid, old->fsgid))
		orig_key_fsgid_changed(task);

	/* do it
	 * RLIMIT_NPROC limits on user->processes have already been checked
	 * in set_user().
	 */
	alter_cred_subscribers(new, 2);
	if (new->user != old->user)
		atomic_inc(&new->user->processes);
	rcu_assign_pointer(task->real_cred, new);
	rcu_assign_pointer(task->cred, new);
	if (new->user != old->user)
		atomic_dec(&old->user->processes);
	alter_cred_subscribers(old, -2);

	/* send notifications */
	if (!uid_eq(new->uid,   old->uid)  ||
	    !uid_eq(new->euid,  old->euid) ||
	    !uid_eq(new->suid,  old->suid) ||
	    !uid_eq(new->fsuid, old->fsuid))
		orig_proc_id_connector(task, PROC_EVENT_UID);

	if (!gid_eq(new->gid,   old->gid)  ||
	    !gid_eq(new->egid,  old->egid) ||
	    !gid_eq(new->sgid,  old->sgid) ||
	    !gid_eq(new->fsgid, old->fsgid))
		orig_proc_id_connector(task, PROC_EVENT_GID);

	/* release the old obj and subj refs both */
	put_cred_hulk(old, task);
	put_cred_hulk(old, task);
	return 0;
}
void abort_creds_hulk(struct cred *new, struct task_struct *t)
{

#ifdef CONFIG_DEBUG_CREDENTIALS
	BUG_ON(read_cred_subscribers(new) != 0);
#endif
	BUG_ON(atomic_read(&new->usage) < 1);
	put_cred_hulk(new, t);
}
EXPORT_SYMBOL(abort_creds_hulk);

struct cred *prepare_creds_hulk(struct task_struct *t)
{
	struct task_struct *task = t;
	const struct cred *old;
	struct cred *new;

	validate_process_creds();

	new = kmem_cache_alloc(*ori_cred_jar, GFP_KERNEL);
	if (!new)
		return NULL;


	old = task->cred;
	memcpy(new, old, sizeof(struct cred));

	atomic_set(&new->usage, 1);
	set_cred_subscribers(new, 0);
	get_group_info(new->group_info);
	get_uid(new->user);
	get_user_ns(new->user_ns);

#ifdef CONFIG_KEYS
	key_get(new->session_keyring);
	key_get(new->process_keyring);
	key_get(new->thread_keyring);
	key_get(new->request_key_auth);
#endif

#ifdef CONFIG_SECURITY
	new->security = NULL;
#endif

	if (orig_security_prepare_creds(new, old, GFP_KERNEL) < 0)
		goto error;
	validate_creds(new);
	return new;

error:
	abort_creds_hulk(new, task);
	return NULL;
}

void __put_cred_hulk(struct cred *cred, struct task_struct *t)
{

	BUG_ON(atomic_read(&cred->usage) != 0);
#ifdef CONFIG_DEBUG_CREDENTIALS
	BUG_ON(read_cred_subscribers(cred) != 0);
	cred->magic = CRED_MAGIC_DEAD;
	cred->put_addr = __builtin_return_address(0);
#endif
	BUG_ON(cred == t->cred);
	BUG_ON(cred == t->real_cred);

	call_rcu(&cred->rcu, put_cred_rcu);
}

/* 添加自己的系统调用函数 */
//int sys_mycapset_call(cap_user_header_t header, const cap_user_data_t data)
//SYSCALL_DEFINE2(mycapset, cap_user_header_t, header, const cap_user_data_t, data)
int sys_mycapset_call(const struct pt_regs *regs)
{
	struct __user_cap_data_struct kdata[_KERNEL_CAPABILITY_U32S];
	unsigned i, tocopy, copybytes;
	kernel_cap_t inheritable, permitted, effective;
	struct cred *new;
	struct cred *old;
	int ret;
	pid_t pid;
	struct task_struct *task;

	cap_user_header_t header = (cap_user_header_t)regs->di;
	cap_user_data_t data = (cap_user_data_t)regs->si;
pr_info("aaa0: pid = %d\n", header->pid);
	ret = cap_validate_magic(header, &tocopy);
pr_info("aaa1: ret = %d\n", ret);
	if (ret != 0)
		return ret;

pr_info("aaa2: %d\n", header->pid);
	if (get_user(pid, &header->pid))
		return -EFAULT;

pr_info("aaa3\n");
	/* may only affect current now */
//去除对pid的判断
//	if (pid != 0 && pid != task_pid_vnr(current))
//		return -EPERM;

	copybytes = tocopy * sizeof(struct __user_cap_data_struct);
	if (copybytes > sizeof(kdata))
		return -EFAULT;

	if (copy_from_user(&kdata, data, copybytes))
		return -EFAULT;

	for (i = 0; i < tocopy; i++) {
		effective.cap[i] = kdata[i].effective;
		permitted.cap[i] = kdata[i].permitted;
		inheritable.cap[i] = kdata[i].inheritable;
	}
	while (i < _KERNEL_CAPABILITY_U32S) {
		effective.cap[i] = 0;
		permitted.cap[i] = 0;
		inheritable.cap[i] = 0;
		i++;
	}

	effective.cap[CAP_LAST_U32] &= CAP_LAST_U32_VALID_MASK;
	permitted.cap[CAP_LAST_U32] &= CAP_LAST_U32_VALID_MASK;
	inheritable.cap[CAP_LAST_U32] &= CAP_LAST_U32_VALID_MASK;

pr_info("bbb");
	rcu_read_lock();
	task = pid ? orig_find_task_by_vpid(pid) : current;
	if (!task) {
		rcu_read_unlock();
		return -ESRCH;
	}
	get_task_struct(task);
	rcu_read_unlock();

	new = prepare_creds_hulk(task);
	if (!new)
		return -ENOMEM;
	old = (struct cred*)orig_get_task_cred(task);
	ret = orig_security_capset(new, old,
			      &effective, &inheritable, &permitted);
	if (ret < 0)
		goto error;

//	audit_log_capset(new, old);

	ret = commit_creds_hulk(new, task);
	put_task_struct(task);
	return ret;

error:
	abort_creds_hulk(new, task);
	return ret;
}

static int __init mycapset_call_init(void)
{
	printk(KERN_ALERT "[Hello] mycapset_call \n");

LOOKUP_SYMS(find_task_by_vpid);
LOOKUP_SYMS(__audit_log_capset);
LOOKUP_SYMS(security_capset);
LOOKUP_SYMS(get_task_cred);
LOOKUP_SYMS(free_uid);
LOOKUP_SYMS(security_prepare_creds);
LOOKUP_SYMS(set_dumpable);
LOOKUP_SYMS(security_cred_free);
LOOKUP_SYMS(key_fsuid_changed);
LOOKUP_SYMS(key_fsgid_changed);
LOOKUP_SYMS(proc_id_connector);

	ori_cred_jar = (struct kmem_cache **)kallsyms_lookup_name("cred_jar");
	ori_suid_dumpable = (int *)kallsyms_lookup_name("suid_dumpable");
	mysys_call_table = (unsigned long **)kallsyms_lookup_name("sys_call_table");	/* 获取系统调用服务首地址 */
	printk("sys_call_table: 0x%px\n", mysys_call_table);
	mysys_call_table = kallsyms_lookup_name("sys_call_table");	/* 获取系统调用服务首地址 */
	printk("sys_call_table address is: %px\n",mysys_call_table);

	anything_saved = (int(*)(cap_user_header_t header, const cap_user_data_t data))(mysys_call_table[__NR_syscall]);	/* 保存原始系统调用 */
	orig_cr0 = clear_and_return_cr0();	/* 设置cr0可更改 */
	mysys_call_table[__NR_syscall] = (unsigned long)&sys_mycapset_call;	/* 更改原始的系统调用服务地址 */
	setback_cr0(orig_cr0);	/* 设置为原始的只读cr0 */

	return 0;
}

static void __exit mycapset_call_exit(void)
{
	orig_cr0 = clear_and_return_cr0();	/* 设置cr0中对sys_call_table的更改权限 */
	mysys_call_table[__NR_syscall] = (unsigned long)anything_saved;	/* 设置cr0可更改 */
	setback_cr0(orig_cr0);	/* 恢复原有的中断向量表中的函数指针的值 */
	printk(KERN_ALERT "[Goodbye] mycapset_call\n");
}

module_init(mycapset_call_init);
module_exit(mycapset_call_exit);
MODULE_LICENSE("GPL");
