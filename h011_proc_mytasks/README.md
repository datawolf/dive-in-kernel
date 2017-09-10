## 说明

该模块在`/proc`下创建了文件`mytasks`，它输出了当前系统上所有的进程


## 示例输出

```
# cat /proc/mytasks
All processes in system:
name                    pid  
swapper/0               0    
systemd                 1    
kthreadd                2    
ksoftirqd/0             3    
kworker/0:0H            5    
migration/0             7    
rcu_bh                  8    
rcuob/0                 9    
rcuob/1                 10   
rcu_sched               11   
rcuos/0                 12   
rcuos/1                 13   
watchdog/0              14   
watchdog/1              15   
migration/1             16   
ksoftirqd/1             17   
kworker/1:0H            19   
khelper                 20   
kdevtmpfs               21   
netns                   22   
writeback               23   
kintegrityd             24   
bioset                  25   
kblockd                 26   
khubd                   27   
md                      28   
khungtaskd              32   
kswapd0                 33   
ksmd                    34   
khugepaged              35   
fsnotify_mark           36   
crypto                  37   
kthrotld                46   
kworker/u4:1            47   
kmpath_rdacd            48   
...
...
...
```
