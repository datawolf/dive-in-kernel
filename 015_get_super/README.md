## 说明

该模块示例了如果通过`current`找到对应的工作目录的所在的文件系统的超级块信息。
即，说明了`get_super`内核API的使用。


## 运行结果
```
root@localhost:015_get_super# dmesg -c
root@localhost:015_get_super# insmod get_super.ko 
root@localhost:015_get_super# rmmod get_super 
root@localhost:015_get_super# dmesg -c
[ 3086.178329] [Hello] get_super 
[ 3086.178830] the super block's dev number is 202:1.
[ 3086.179339] After the "get_super", the super block's dev number is 202:1.
[ 3091.289649] [Goodbye] get_super
```
