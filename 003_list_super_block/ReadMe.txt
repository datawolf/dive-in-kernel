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

