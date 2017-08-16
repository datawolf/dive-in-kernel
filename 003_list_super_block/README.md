## 说明

该模块可以查看特定的文件系统在linux系统上的所有超级块信息。

## 实现说明

在linux的数据结构`file_system_type`中，有一个域`fs_supers`链接具有同一种类型的超级快。同一种文件系统类型的超级块通过`s_instances`链接。



## 使用方法


## 示例

查找列出所有已经挂载的ext4文件系统的超级快信息：

系统中的文件系统挂载情况如下
[root@localhost]# mount

/dev/mapper/VolGroup-lv_root on / type ext4 (rw)
proc on /proc type proc (rw)
sysfs on /sys type sysfs (rw)
devpts on /dev/pts type devpts (rw,gid=5,mode=620)
tmpfs on /dev/shm type tmpfs (rw)
/dev/sdb1 on /boot type ext4 (rw)
/dev/mapper/VolGroup-lv_home on /home type ext4 (rw)
none on /proc/sys/fs/binfmt_misc type binfmt_misc (rw)


总共有三个ext4文件系统，执行结果如下：
The filesystem's name is : ext4
The ext4 filesystem  is : dm-2
The ext4 filesystem  is : sdb1
The ext4 filesystem  is : dm-0

