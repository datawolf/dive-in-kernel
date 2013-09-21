[root@localhost] # cat /proc/filesystem
nodev	sysfs
nodev	rootfs
nodev	bdev
nodev	proc
nodev	cgroup
nodev	cpuset
nodev	tmpfs
nodev	devtmpfs
nodev	binfmt_misc
nodev	debugfs
nodev	securityfs
nodev	sockfs
nodev	usbfs
nodev	pipefs
nodev	anon_inodefs
nodev	devpts
nodev	ramfs
nodev	hugetlbfs
	iso9660
nodev	mqueue
	ext4
-------------------------------------------------
there are 21 file systems. 
so the sysfs(3) return the number of 21.



---------------------------------------------------
sysfs.c的执行结果:
The total  number of file system in the kernel is 0.
The ext4 file system type index is 20
The file system which index is 0  identifier string is : sysfs
The file system which index is 1  identifier string is : rootfs
The file system which index is 2  identifier string is : bdev
The file system which index is 3  identifier string is : proc
The file system which index is 4  identifier string is : cgroup
The file system which index is 5  identifier string is : cpuset
The file system which index is 6  identifier string is : tmpfs
The file system which index is 7  identifier string is : devtmpfs
The file system which index is 8  identifier string is : binfmt_misc
The file system which index is 9  identifier string is : debugfs
The file system which index is 10  identifier string is : securityfs
The file system which index is 11  identifier string is : sockfs
The file system which index is 12  identifier string is : usbfs
The file system which index is 13  identifier string is : pipefs
The file system which index is 14  identifier string is : anon_inodefs
The file system which index is 15  identifier string is : devpts
The file system which index is 16  identifier string is : ramfs
The file system which index is 17  identifier string is : hugetlbfs
The file system which index is 18  identifier string is : iso9660
The file system which index is 19  identifier string is : mqueue
The file system which index is 20  identifier string is : ext4
