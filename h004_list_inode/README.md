## 说明

该模块可以查看特定的文件系统在linux系统上的所有超级块信息。

## 实现说明

在linux的数据结构`file_system_type`中，有一个域`fs_supers`链接具有同一种类型的超级快。同一种文件系统类型的超级块通过`s_instances`链接。

## 使用方法

默认情况下，显示所有类型为ext4的`super_block`信息

```
# dmesg -c
# insmod list_super_block.ko
# rmmod list_super_block
# dmesg
[ 1307.249846] The filesystem's name is : ext4
[ 1307.249870] ******************************************
[ 1307.249894] The ext4 filesystem  is : xvde1
[ 1307.249915] The ext4 filesystem  is : xvda1
[ 1315.040887] Goodbye list_super_block
```

在插入模块时，我们可以指定参数`fs`

```
# dmesg -c
# insmod list_super_block.ko  fs="proc"
# rmmod list_super_block
# dmesg
[ 1509.699923] The filesystem's name is : proc
[ 1509.700322] ******************************************
[ 1509.700346] The proc filesystem  is : proc
[ 1509.701017] The proc filesystem  is : proc
[ 1509.701364] The proc filesystem  is : proc
[ 1514.676233] Goodbye list_super_block
```
