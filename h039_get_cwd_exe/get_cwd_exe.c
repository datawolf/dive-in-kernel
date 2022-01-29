/***********************************************
 * module : get_cwd_exe
 *
 * Wang Long (w@laoqinren.net)
 **********************************************/
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/pid.h>
#include <linux/limits.h>
#include <linux/fs_struct.h>
#include <linux/mm.h>
#include <linux/atomic.h>
#include <linux/init.h>
#include <linux/connector.h>
#include <linux/gfp.h>
#include <linux/ptrace.h>
#include <linux/atomic.h>
#include <linux/pid_namespace.h>


static int pid = 1;
module_param(pid, int, 1);

static void cn_proc_get_fs_pwd(struct task_struct *task, struct path *path)
{
       get_task_struct(task);
       task_lock(task);
       if (task->fs)
               get_fs_pwd(task->fs, path);
       task_unlock(task);
       put_task_struct(task);
}

static int get_process_cwd(struct task_struct *task, char *buf, int buflen)
{
       struct path path;
       char *p, *pathname;

       /*  We will allow 11 spaces for ' (deleted)' to be appended */
       pathname = kmalloc(PATH_MAX+11, GFP_KERNEL);
       if (!pathname)
               return -ENOMEM;


       cn_proc_get_fs_pwd(task, &path);
       p = d_path(&path, pathname, PATH_MAX+11);
       if (IS_ERR(p))
               return -ENAMETOOLONG;

       strncpy(buf, p, buflen);
       kfree(pathname);
       return 0;
}

static int get_process_exe(struct task_struct *task, char *buf, int buflen)
{
       struct file *exe_file;
       char *p, *pathname;

       exe_file = get_task_exe_file(task);
       if (!exe_file)
               return 0;

       /*  We will allow 11 spaces for ' (deleted)' to be appended */
       pathname = kmalloc(PATH_MAX+11, GFP_KERNEL);
       if (!pathname)
               return -ENOMEM;

       p = d_path(&exe_file->f_path, pathname, PATH_MAX+11);
       if (IS_ERR(p))
               return -ENAMETOOLONG;

       strncpy(buf, p, buflen);
       kfree(pathname);
       return 0;
}

static int __init get_cwd_exe_init(void)
{
	pid_t p = (pid_t)pid;
	char           cwd[64];
	char           path[64];
	int		ret = 0;
	struct task_struct *task = get_pid_task(find_get_pid(p), PIDTYPE_PID);

	printk(KERN_ALERT "[Hello] get_cwd_exe \n");
	ret = get_process_cwd(task, cwd, sizeof(cwd));
	if (ret != 0) {
		printk(KERN_ALERT "ERROR:  get_process_cwd: %d\n", ret);
	}else {
		printk(KERN_ALERT "get_process_cwd: %s\n", cwd);
	}

	ret = get_process_exe(task, path, sizeof(path));
	if (ret != 0) {
		printk(KERN_ALERT "ERROR:  get_process_path: %d\n", ret);
	}else {
		printk(KERN_ALERT "get_process_exe: %s\n", path);
	}
	return 0;
}

static void __exit get_cwd_exe_exit(void)
{
	printk(KERN_ALERT "[Goodbye] get_cwd_exe\n");
}

module_init(get_cwd_exe_init);
module_exit(get_cwd_exe_exit);
MODULE_LICENSE("GPL");

