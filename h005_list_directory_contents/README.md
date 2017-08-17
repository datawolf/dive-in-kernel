## 说明

该模块可以通过指定设备号和inode节点号，打印出出该inode节点所代表的目录中的所有文件和文件夹。


## 用法


### 查询跟分区磁盘类型

```
root@localhost:h005_list_directory_contents# mount | grep xvda1
/dev/xvda1 on / type ext4 (rw,relatime,errors=remount-ro,data=ordered)
/dev/xvda1 on /var/lib/docker/aufs type ext4 (rw,relatime,errors=remount-ro,data=ordered)
```

 可以看出跟分区 `/`的磁盘类型为`ext4`

### 查询跟分区磁盘的设备号

```
root@localhost:h005_list_directory_contents# ls -l /dev/xvda1 
brw-rw---- 1 root disk 202, 1 Aug 16 20:06 /dev/xvda1
```

###  查看inode号

```
root@localhost:h005_list_directory_contents# ls -li /
total 152
 261633 drwxr-xr-x   2 root root  4096 Aug  8 12:08 bin
1308161 drwxr-xr-x   3 root root  4096 Aug  8 12:08 boot
1309176 drwxrwxr-x  17 root root  4096 Jul  5 10:11 busybox
1177453 drwxr-xr-x   4 root root  4096 Sep 20  2016 checkpoint
1309179 drwxr-xr-x   4 root root  4096 Nov 17  2016 container
      2 drwxr-xr-x  21 root root  4380 Aug 16 20:06 dev
 130817 drwxr-xr-x 127 root root 12288 Aug 15 15:05 etc
  14238 -rw-r--r--   1 root root  3163 Jul 12 16:19 gmon.out
1857934 drwxr-xr-x   6 root root  4096 Oct 28  2016 go
1438977 drwxr-xr-x   3 root root  4096 Oct  9  2015 home
  14454 lrwxrwxrwx   1 root root    32 Feb  6  2017 initrd.img -> boot/initrd.img-4.4.0-62-generic
     12 lrwxrwxrwx   1 root root    33 Aug 27  2015 initrd.img.old -> boot/initrd.img-3.13.0-24-generic
1700609 drwxr-xr-x  24 root root  4096 Apr 10 10:55 lib
 784898 drwxr-xr-x   2 root root  4096 Apr 10 10:48 lib32
2093057 drwxr-xr-x   2 root root  4096 Apr 10 10:48 lib64
     11 drwx------   2 root root 16384 Aug 27  2015 lost+found
1569793 drwxr-xr-x   3 root root  4096 Aug 27  2015 media
 784942 drwxr-xr-x   2 root root  4096 Feb  6  2017 mnt
1178161 drwxr-xr-x   4 root root  4096 Feb  3  2017 mycontainer
 392449 drwxr-xr-x   3 root root  4096 Oct 10  2015 opt
      1 dr-xr-xr-x 212 root root     0 Aug 16 20:06 proc
1310230 dr-xr-xr-x   2 root root  4096 Oct 21  2016 proc0
1310229 dr-xr-xr-x   2 root root  4096 Oct 21  2016 proc1
1309730 dr-xr-xr-x   2 root root  4096 Oct 21  2016 proc2
1310228 dr-xr-xr-x   2 root root  4096 Oct 21  2016 proc3
1309731 dr-xr-xr-x   2 root root  4096 Oct 21  2016 proc4
 654081 drwxr-xr-x  33 root root  4096 Aug 17 10:40 root
      2 drwxr-xr-x  27 root root  1040 Aug 17 06:25 run
 915713 drwxr-xr-x   2 root root 12288 Aug  8 12:07 sbin
 784967 drwxr-xr-x   2 root root  4096 Jan 14  2017 snap
1570040 drwxr-xr-x   2 root root  4096 Jun 30 09:37 some
1177345 drwxr-xr-x   2 root root  4096 Apr 17  2014 srv
      1 dr-xr-xr-x  13 root root     0 Aug 16 20:06 sys
1177451 drwxr-xr-x   2 root root  4096 Sep 19  2016 testdata
1962242 drwxrwxrwt   8 root root  4096 Aug 17 10:41 tmp
 915838 drwxr-xr-x  14 root root  4096 Mar 21 11:40 usr
2093059 drwxr-xr-x  14 root root  4096 Feb  6  2017 var
  14455 lrwxrwxrwx   1 root root    29 Feb  6  2017 vmlinuz -> boot/vmlinuz-4.4.0-62-generic
     13 lrwxrwxrwx   1 root root    30 Aug 27  2015 vmlinuz.old -> boot/vmlinuz-3.13.0-24-generic
```

### 插入模块

指定inode号为目录`/home`的indoe节点

```
root@localhost:h005_list_directory_contents# insmod list_directory_contents.ko  major=202 minor=1 fs="ext4" inode=1438977
root@localhost:h005_list_directory_contents# rmmod list_directory_contents 
```

###   查看结果

```
root@localhost:h005_list_directory_contents# dmesg
[ 3794.848667] The module params: inode = 1438977, major = 202, minor = 1, fs = ext4
[ 3794.848669] The filesystem's name is : ext4
[ 3794.848670] ******************************************
[ 3794.848672] Skip the ext4 filesystem is : xvde1(202:65)
[ 3794.848673] The ext4 filesystem is : xvda1(202:1)
[ 3794.849481] 1438977 [home] parent = /
               		file = wanglong
[ 3798.114930] [Goodbye] list_directory_contents
root@localhost:h005_list_directory_contents# ls -l /home/
total 4
drwxr-xr-x 13 wanglong wanglong 4096 Jun  8 16:18 wanglong
```

