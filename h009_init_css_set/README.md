## 说明

本模块打印了`init_task->cgroup` 和`current->cgroup`相关的数据结构关系。


## 执行结果

```
make[1]: Entering directory `/root/dive-in-kernel/h009_init_css_set'
#############[START] #################
[15655.285007] [Hello] init_css_set 
[15655.285011] ###### init_css_set info #######
[15655.285012] init_css_set.refcount = 62
[15655.285013] ###### init_css_set_link info #######
[15655.285013] 0 addr = ffffffff81d8ce70, hierarchy_d = 0, hierarchy_name = , num = 1, (top_cgroup.name = /) name = /	subsys: OK
[15655.285017] cg = ffffffff81d8cd40
[15655.285017] 1 addr = ffff88011835c030, hierarchy_d = 1, hierarchy_name = systemd, num = 93, (top_cgroup.name = /) name = /	subsys: 
[15655.285020] cg = ffffffff81d8cd40
[15655.285020] 2 addr = ffff88011835e030, hierarchy_d = 2, hierarchy_name = , num = 1, (top_cgroup.name = /) name = /	subsys: freezer, 
[15655.285023] cg = ffffffff81d8cd40
[15655.285023] 3 addr = ffff8801180a6030, hierarchy_d = 3, hierarchy_name = , num = 89, (top_cgroup.name = /) name = /	subsys: memory, 
[15655.285026] cg = ffffffff81d8cd40
[15655.285026] 4 addr = ffff8801180a4030, hierarchy_d = 4, hierarchy_name = , num = 1, (top_cgroup.name = /) name = /	subsys: cpuset, 
[15655.285028] cg = ffffffff81d8cd40
[15655.285029] 5 addr = ffff8801180a2030, hierarchy_d = 5, hierarchy_name = , num = 1, (top_cgroup.name = /) name = /	subsys: hugetlb, 
[15655.285031] cg = ffffffff81d8cd40
[15655.285032] 6 addr = ffff8801180a0030, hierarchy_d = 6, hierarchy_name = , num = 89, (top_cgroup.name = /) name = /	subsys: cpuacct, cpu, 
[15655.285034] cg = ffffffff81d8cd40
[15655.285035] 7 addr = ffff880118086030, hierarchy_d = 7, hierarchy_name = , num = 1, (top_cgroup.name = /) name = /	subsys: perf_event, 
[15655.285038] cg = ffffffff81d8cd40
[15655.285038] 8 addr = ffff880118084030, hierarchy_d = 8, hierarchy_name = , num = 89, (top_cgroup.name = /) name = /	subsys: blkio, 
[15655.285041] cg = ffffffff81d8cd40
[15655.285041] 9 addr = ffff880118082030, hierarchy_d = 9, hierarchy_name = , num = 89, (top_cgroup.name = /) name = /	subsys: devices, 
[15655.285043] cg = ffffffff81d8cd40
[15655.285044] 10 addr = ffff880118080030, hierarchy_d = 10, hierarchy_name = , num = 1, (top_cgroup.name = /) name = /	subsys: net_cls, 
[15655.285046] cg = ffffffff81d8cd40
[15655.285047] #############
[15655.285048] current's css_set addr = ffff8800cc97d900
[15655.285048] 11 addr = ffffffff81d8ce70, hierarchy_id = 0, hierarchy_name = , num = 1, (top_cgroup.name = /) name = /	subsys: 
[15655.285050] cg = ffff8800cc97d900
[15655.285051] 12 addr = ffff8800d3459a00, hierarchy_id = 1, hierarchy_name = systemd, num = 93, (top_cgroup.name = /) name = session-1.scope	subsys: 
[15655.285053] cg = ffff8800cc97d900
[15655.285054] 13 addr = ffff88011835e030, hierarchy_id = 2, hierarchy_name = , num = 1, (top_cgroup.name = /) name = /	subsys: freezer, 
[15655.285056] cg = ffff8800cc97d900
[15655.285056] 14 addr = ffff880035e79800, hierarchy_id = 3, hierarchy_name = , num = 89, (top_cgroup.name = /) name = user.slice	subsys: memory, 
[15655.285058] cg = ffff8800cc97d900
[15655.285059] 15 addr = ffff8801180a4030, hierarchy_id = 4, hierarchy_name = , num = 1, (top_cgroup.name = /) name = /	subsys: cpuset, 
[15655.285089] cg = ffff8800cc97d900
[15655.285090] 16 addr = ffff8801180a2030, hierarchy_id = 5, hierarchy_name = , num = 1, (top_cgroup.name = /) name = /	subsys: hugetlb, 
[15655.285091] cg = ffff8800cc97d900
[15655.285092] 17 addr = ffff880035e79e00, hierarchy_id = 6, hierarchy_name = , num = 89, (top_cgroup.name = /) name = user.slice	subsys: cpuacct, cpu, 
[15655.285094] cg = ffff8800cc97d900
[15655.285095] 18 addr = ffff880118086030, hierarchy_id = 7, hierarchy_name = , num = 1, (top_cgroup.name = /) name = /	subsys: perf_event, 
[15655.285096] cg = ffff8800cc97d900
[15655.285097] 19 addr = ffff880035e79a00, hierarchy_id = 8, hierarchy_name = , num = 89, (top_cgroup.name = /) name = user.slice	subsys: blkio, 
[15655.285098] cg = ffff8800cc97d900
[15655.285099] 20 addr = ffff880035e79600, hierarchy_id = 9, hierarchy_name = , num = 89, (top_cgroup.name = /) name = user.slice	subsys: devices, 
[15655.285101] cg = ffff8800cc97d900
[15655.285101] 21 addr = ffff880118080030, hierarchy_id = 10, hierarchy_name = , num = 1, (top_cgroup.name = /) name = /	subsys: net_cls, 
[15655.285103] cg = ffff8800cc97d900
[15655.285103] CGROUP_SUBSYS_COUNT = 11
[15655.285104] ##################################

[15655.285105] init_css_set.subsys[0] addr = ffff8801180a4030
[15655.285106] init_css_set.subsys[0].refcnt = 1
[15655.285106] init_css_set.subsys[0].cgroup.name = /
[15655.285107] init_css_set.subsys[0].cgroupfs_root.name = /
[15655.285108] init_css_set.subsys[0].cgroupfs_root.release_agent = 

[15655.285109] init_css_set.subsys[1] addr = ffff8801180a0030
[15655.285110] init_css_set.subsys[1].refcnt = 1
[15655.285110] init_css_set.subsys[1].cgroup.name = /
[15655.285111] init_css_set.subsys[1].cgroupfs_root.name = /
[15655.285112] init_css_set.subsys[1].cgroupfs_root.release_agent = 
[15655.285113] init_css_set.subsys[1].childcgroup.name = system.slice
[15655.285114] init_css_set.subsys[1].childcgroup.name = user.slice

[15655.285115] init_css_set.subsys[2] addr = ffff8801180a0030
[15655.285115] init_css_set.subsys[2].refcnt = 1
[15655.285116] init_css_set.subsys[2].cgroup.name = /
[15655.285117] init_css_set.subsys[2].cgroupfs_root.name = /
[15655.285117] init_css_set.subsys[2].cgroupfs_root.release_agent = 
[15655.285118] init_css_set.subsys[2].childcgroup.name = system.slice
[15655.285119] init_css_set.subsys[2].childcgroup.name = user.slice

[15655.285120] init_css_set.subsys[3] addr = ffff8801180a6030
[15655.285121] init_css_set.subsys[3].refcnt = 1
[15655.285121] init_css_set.subsys[3].cgroup.name = /
[15655.285122] init_css_set.subsys[3].cgroupfs_root.name = /
[15655.285123] init_css_set.subsys[3].cgroupfs_root.release_agent = 
[15655.285123] init_css_set.subsys[3].childcgroup.name = system.slice
[15655.285124] init_css_set.subsys[3].childcgroup.name = user.slice

[15655.285125] init_css_set.subsys[4] addr = ffff880118082030
[15655.285126] init_css_set.subsys[4].refcnt = 1
[15655.285127] init_css_set.subsys[4].cgroup.name = /
[15655.285127] init_css_set.subsys[4].cgroupfs_root.name = /
[15655.285128] init_css_set.subsys[4].cgroupfs_root.release_agent = 
[15655.285129] init_css_set.subsys[4].childcgroup.name = system.slice
[15655.285129] init_css_set.subsys[4].childcgroup.name = user.slice

[15655.285131] init_css_set.subsys[5] addr = ffff88011835e030
[15655.285131] init_css_set.subsys[5].refcnt = 1
[15655.285132] init_css_set.subsys[5].cgroup.name = /
[15655.285133] init_css_set.subsys[5].cgroupfs_root.name = /
[15655.285133] init_css_set.subsys[5].cgroupfs_root.release_agent = 

[15655.285135] init_css_set.subsys[6] addr = ffff880118080030
[15655.285135] init_css_set.subsys[6].refcnt = 1
[15655.285136] init_css_set.subsys[6].cgroup.name = /
[15655.285137] init_css_set.subsys[6].cgroupfs_root.name = /
[15655.285137] init_css_set.subsys[6].cgroupfs_root.release_agent = 

[15655.285139] init_css_set.subsys[7] addr = ffff880118084030
[15655.285139] init_css_set.subsys[7].refcnt = 1
[15655.285140] init_css_set.subsys[7].cgroup.name = /
[15655.285141] init_css_set.subsys[7].cgroupfs_root.name = /
[15655.285141] init_css_set.subsys[7].cgroupfs_root.release_agent = 
[15655.285142] init_css_set.subsys[7].childcgroup.name = system.slice
[15655.285143] init_css_set.subsys[7].childcgroup.name = user.slice

[15655.285144] init_css_set.subsys[8] addr = ffff880118086030
[15655.285145] init_css_set.subsys[8].refcnt = 1
[15655.285146] init_css_set.subsys[8].cgroup.name = /
[15655.285146] init_css_set.subsys[8].cgroupfs_root.name = /
[15655.285147] init_css_set.subsys[8].cgroupfs_root.release_agent = 

[15655.285148] init_css_set.subsys[9] addr = ffff8801180a2030
[15655.285149] init_css_set.subsys[9].refcnt = 1
[15655.285149] init_css_set.subsys[9].cgroup.name = /
[15655.285150] init_css_set.subsys[9].cgroupfs_root.name = /
[15655.285151] init_css_set.subsys[9].cgroupfs_root.release_agent = 


[15655.285152] ##################################

[15655.285153] current->cgroups.subsys[0] addr = ffff8801180a4030
[15655.285154] current->cgroups.subsys[0].refcnt = 1
[15655.285155] current->cgroups.subsys[0].cgroup.name = /
[15655.285155] current->cgroups.subsys[0].cgroupfs_root.name = /
[15655.285156] current->cgroups.subsys[0].cgroupfs_root.release_agent = 

[15655.285157] current->cgroups.subsys[1] addr = ffff880035e79e00
[15655.285158] current->cgroups.subsys[1].refcnt = 1
[15655.285159] current->cgroups.subsys[1].cgroup.name = user.slice
[15655.285159] current->cgroups.subsys[1].cgroupfs_root.name = /
[15655.285160] current->cgroups.subsys[1].cgroupfs_root.release_agent = 
[15655.285160] current->cgroups.subsys[1].cgroup.parent.name = /

[15655.285162] current->cgroups.subsys[2] addr = ffff880035e79e00
[15655.285162] current->cgroups.subsys[2].refcnt = 1
[15655.285163] current->cgroups.subsys[2].cgroup.name = user.slice
[15655.285164] current->cgroups.subsys[2].cgroupfs_root.name = /
[15655.285164] current->cgroups.subsys[2].cgroupfs_root.release_agent = 
[15655.285165] current->cgroups.subsys[2].cgroup.parent.name = /

[15655.285166] current->cgroups.subsys[3] addr = ffff880035e79800
[15655.285167] current->cgroups.subsys[3].refcnt = 1
[15655.285167] current->cgroups.subsys[3].cgroup.name = user.slice
[15655.285168] current->cgroups.subsys[3].cgroupfs_root.name = /
[15655.285169] current->cgroups.subsys[3].cgroupfs_root.release_agent = 
[15655.285169] current->cgroups.subsys[3].cgroup.parent.name = /

[15655.285171] current->cgroups.subsys[4] addr = ffff880035e79600
[15655.285171] current->cgroups.subsys[4].refcnt = 1
[15655.285172] current->cgroups.subsys[4].cgroup.name = user.slice
[15655.285173] current->cgroups.subsys[4].cgroupfs_root.name = /
[15655.285173] current->cgroups.subsys[4].cgroupfs_root.release_agent = 
[15655.285174] current->cgroups.subsys[4].cgroup.parent.name = /

[15655.285175] current->cgroups.subsys[5] addr = ffff88011835e030
[15655.285176] current->cgroups.subsys[5].refcnt = 1
[15655.285176] current->cgroups.subsys[5].cgroup.name = /
[15655.285177] current->cgroups.subsys[5].cgroupfs_root.name = /
[15655.285178] current->cgroups.subsys[5].cgroupfs_root.release_agent = 

[15655.285179] current->cgroups.subsys[6] addr = ffff880118080030
[15655.285179] current->cgroups.subsys[6].refcnt = 1
[15655.285180] current->cgroups.subsys[6].cgroup.name = /
[15655.285181] current->cgroups.subsys[6].cgroupfs_root.name = /
[15655.285181] current->cgroups.subsys[6].cgroupfs_root.release_agent = 

[15655.285182] current->cgroups.subsys[7] addr = ffff880035e79a00
[15655.285183] current->cgroups.subsys[7].refcnt = 4
[15655.285184] current->cgroups.subsys[7].cgroup.name = user.slice
[15655.285184] current->cgroups.subsys[7].cgroupfs_root.name = /
[15655.285185] current->cgroups.subsys[7].cgroupfs_root.release_agent = 
[15655.285186] current->cgroups.subsys[7].cgroup.parent.name = /

[15655.285187] current->cgroups.subsys[8] addr = ffff880118086030
[15655.285187] current->cgroups.subsys[8].refcnt = 1
[15655.285188] current->cgroups.subsys[8].cgroup.name = /
[15655.285189] current->cgroups.subsys[8].cgroupfs_root.name = /
[15655.285189] current->cgroups.subsys[8].cgroupfs_root.release_agent = 

[15655.285191] current->cgroups.subsys[9] addr = ffff8801180a2030
[15655.285191] current->cgroups.subsys[9].refcnt = 1
[15655.285192] current->cgroups.subsys[9].cgroup.name = /
[15655.285192] current->cgroups.subsys[9].cgroupfs_root.name = /
[15655.285193] current->cgroups.subsys[9].cgroupfs_root.release_agent = 


make[1]: Leaving directory `/root/dive-in-kernel/h009_init_css_set'
make[1]: Entering directory `/root/dive-in-kernel/h009_init_css_set'
[15655.347277] [Goodbye] init_css_set
#############[ END ] #################
make[1]: Leaving directory `/root/dive-in-kernel/h009_init_css_set'
```
