查找列出系统中所有超级快信息：

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

执行结果如下:

The filesystem's name is : ext4
The super_block filesystem name is  : ext4
The registered filesystem is : binfmt_misc
The registered filesystem is :  x▒▒▒▒▒▒ x▒▒▒▒▒▒
The registered filesystem is : sysfs
The registered filesystem is : rootfs
The registered filesystem is : bdev
The registered filesystem is : proc
The registered filesystem is : tmpfs
The registered filesystem is : devtmpfs
The registered filesystem is : sockfs
The registered filesystem is : debugfs
The registered filesystem is : pipefs
The registered filesystem is : anon_inodefs
The registered filesystem is : devpts
The registered filesystem is : hugetlbfs
The registered filesystem is : mqueue
The registered filesystem is : selinuxfs
The registered filesystem is : usbfs
The registered filesystem is : securityfs
The registered filesystem is : sysfs
The registered filesystem is : tmpfs
The registered filesystem is : ext4
The registered filesystem is : ext4

