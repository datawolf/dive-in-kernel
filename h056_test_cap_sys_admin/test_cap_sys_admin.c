/***********************************************
 * module : test_cap_sys_admin
 *
 * Wang Long (w@laoqinren.net)
 **********************************************/
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/capability.h>
#include <linux/pid.h>
#include <linux/cred.h>

static int pid = 1;
module_param(pid, int, 0400);
MODULE_PARM_DESC(pid, "The pid to clear CAP_SYS_ADMIN");

static void render_cap_t(const char *header,
			kernel_cap_t *a)
{
	char buff[1024];
	int desc = 0;
	unsigned __capi;

	desc += sprintf(buff+desc, "%s", header);
	CAP_FOR_EACH_U32(__capi) {
		desc += sprintf(buff+desc, "%08x",
			   a->cap[CAP_LAST_U32 - __capi]);
	}
	printk("%s", buff);
}


static int __init test_cap_sys_admin_init(void)
{
	pid_t pp = (pid_t)pid;
	struct task_struct *p;
	const struct cred *cred;
	kernel_cap_t cap_inheritable, cap_permitted, cap_effective,
			cap_bset, cap_ambient;

	printk(KERN_ALERT "[Hello] test_cap_sys_admin \n");

	p = get_pid_task(find_get_pid(pp), PIDTYPE_PID);
	rcu_read_lock();
	cred = __task_cred(p);
	cap_inheritable	= cred->cap_inheritable;
	cap_permitted	= cred->cap_permitted;
	cap_effective	= cred->cap_effective;
	cap_bset	= cred->cap_bset;
	cap_ambient	= cred->cap_ambient;
	rcu_read_unlock();

	render_cap_t("CapInh:\t", &cap_inheritable);
	render_cap_t("CapPrm:\t", &cap_permitted);
	render_cap_t("CapEff:\t", &cap_effective);
	render_cap_t("CapBnd:\t", &cap_bset);
	render_cap_t("CapAmb:\t", &cap_ambient);

	return 0;
}

static void __exit test_cap_sys_admin_exit(void)
{
	printk(KERN_ALERT "[Goodbye] test_cap_sys_admin\n");
}

module_init(test_cap_sys_admin_init);
module_exit(test_cap_sys_admin_exit);
MODULE_LICENSE("GPL");
