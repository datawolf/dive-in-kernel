ref_module 实现模块a使用模块b，同时将模块b的引用计数加一。


linux 2.6.35 中include/linux/module.h中没有ref_module的声明，需要自己添加。

[root@localhost 011_ref_module]# lsmod  | head -4
Module                  Size  Used by
test_module              847  1
ext3                  132801  1
jbd                    50559  1 ext3
[root@localhost 011_ref_module]# insmod ref_module.ko
[root@localhost 011_ref_module]# lsmod  | head -4
Module                  Size  Used by
ref_module               942  0
test_module              847  2 ref_module
ext3                  132801  1
[root@localhost 011_ref_module]# rmmod  ref_module
[root@localhost 011_ref_module]# lsmod  | head -4
Module                  Size  Used by
test_module              847  1
ext3                  132801  1
jbd                    50559  1 ext3

