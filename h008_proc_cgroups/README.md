## 说明

本模块通过`subsys`变量遍历系统中支持的`cgroups`

## 执行结果

```
make[1]: Entering directory `/root/dive-in-kernel/h008_proc_cgroups'
#############[START] #################
[15710.101142] [Hello] proc_cgroups 
[15710.101145] CGROUP_BUILTIN_SUBSYS_COUNT = 10
[15710.101146] CGROUP_SUBSYS_COUNT = 11

[15710.101147] #subsys_name	hierarchy	num_cgroups	enabled
[15710.101148] [0]cpuset	5	1	1
[15710.101150] [1]cpu	2	88	1
[15710.101151] [2]cpuacct	2	88	1
[15710.101152] [3]memory	10	88	1
[15710.101153] [4]devices	6	88	1
[15710.101153] [5]freezer	3	1	1
[15710.101154] [6]net_cls	4	1	1
[15710.101155] [7]blkio	8	88	1
[15710.101156] [8]perf_event	9	1	1
[15710.101157] [9]hugetlb	7	1	1
[15710.101159] [10]net_prio	0	1	1
make[1]: Leaving directory `/root/dive-in-kernel/h008_proc_cgroups'
make[1]: Entering directory `/root/dive-in-kernel/h008_proc_cgroups'
[15710.134711] [Goodbye] proc_cgroups
#############[ END ] #################
make[1]: Leaving directory `/root/dive-in-kernel/h008_proc_cgroups'
```
