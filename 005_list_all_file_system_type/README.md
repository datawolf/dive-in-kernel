## 说明

被linux支持的文件系统，都有且仅有一个`file_system_type`结构，而不管它有0个或者多个实例被安装到系统中。

linux内核中通过双向链表来存储`file_system_type`，其头节点文件变量`file_systems`.

##  输出结果如下

```
[  368.965951] list_all_file_system_type: module verification failed: signature and/or required key missing - tainting kernel
[  368.975237] file system type : sysfs
[  368.975260] file system type : rootfs
[  368.975278] file system type : ramfs
[  368.975296] file system type : bdev
[  368.975313] file system type : proc
[  368.975330] file system type : cpuset
[  368.975348] file system type : cgroup
[  368.975366] file system type : tmpfs
[  368.975383] file system type : devtmpfs
[  368.975401] file system type : debugfs
[  368.975420] file system type : tracefs
[  368.975438] file system type : securityfs
[  368.975458] file system type : sockfs
[  368.975475] file system type : bpf
[  368.975492] file system type : pipefs
[  368.975509] file system type : devpts
[  368.975527] file system type : ext3
[  368.975544] file system type : ext2
[  368.975561] file system type : ext4
[  368.975578] file system type : squashfs
[  368.975596] file system type : hugetlbfs
[  368.975615] file system type : vfat
[  368.975632] file system type : ecryptfs
[  368.975655] file system type : fuseblk
[  368.975673] file system type : fuse
[  368.975690] file system type : fusectl
[  368.975708] file system type : pstore
[  368.975725] file system type : mqueue
[  368.975743] file system type : btrfs
[  368.975761] file system type : autofs
[  368.975778] file system type : binfmt_misc
[  368.975798] file system type : aufs
[  374.655221] [goodbye] list_all_file_system_type
```
