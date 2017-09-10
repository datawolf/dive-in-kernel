/***********************************************
 * module : proc_mytasks
 *
 * Wang Long (wanglong@laoqinren.net)
 **********************************************/
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/proc_fs.h>
#include <linux/seq_file.h>
#include <linux/sched.h>


static void *tasks_seq_start(struct seq_file *s, loff_t *pos)
{
	if (*pos == 0) {
		seq_printf(s, "All processes in system:\n%-24s%-5s\n", "name", "pid");
		return &init_task;
	} else {
		return NULL;
	}
}

static void *tasks_seq_next(struct seq_file *s, void *v, loff_t *pos)
{
	struct task_struct *task = (struct task_struct *)v;

	task = next_task(task);
	if ((*pos != 0) && (task == &init_task)) {
		return NULL;
	}
	++*pos;
	return task;
}

static void tasks_seq_stop(struct seq_file *s, void *v)
{
}

/*
 * The show function.
 */
static int tasks_seq_show(struct seq_file *s, void *v)
{
	struct task_struct *task = (struct task_struct *)v;

	seq_printf(s, "%-24s%-5d\n", task->comm, task->pid);

	return 0;
}

static struct seq_operations tasks_seq_ops = {
	.start = tasks_seq_start,
	.next = tasks_seq_next,
	.stop = tasks_seq_stop,
	.show = tasks_seq_show
};

static int tasks_open(struct inode *inode, struct file *file)
{
	return seq_open(file, &tasks_seq_ops);
}

static struct file_operations tasks_file_ops = {
	.owner   = THIS_MODULE,
	.open    = tasks_open,
	.read    = seq_read,
	.llseek  = seq_lseek,
	.release = seq_release
};

static int __init proc_mytasks_init(void)
{
	struct proc_dir_entry *pe;
	pe = proc_create("mytasks", 0, NULL, &tasks_file_ops);
	if (pe == NULL) {
		pr_err("proc_create failed\n");
		return -1;
	}
	return 0;
}

static void __exit proc_mytasks_exit(void)
{
	remove_proc_entry("mytasks", NULL);
}

module_init(proc_mytasks_init);
module_exit(proc_mytasks_exit);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("datawolf");
