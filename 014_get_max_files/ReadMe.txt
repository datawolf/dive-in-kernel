get_max_files函数用于返回系统中可以同时打开的最大文件数目。


[root@localhost 014_get_max_files]# insmod get_max_files.ko
[root@localhost 014_get_max_files]# dmesg
[Hello] get_max_files
the return value of the get_max_files is 184663.
