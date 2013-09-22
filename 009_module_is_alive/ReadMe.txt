module_is_live 函数判断module是否处于活动状态。

[root@localhost 009_module_is_alive]# dmesg
[root@localhost 009_module_is_alive]# insmod module_is_live.ko
[root@localhost 009_module_is_alive]# dmesg
[Hello] module_is_live
in init , state is not GOING
[root@localhost 009_module_is_alive]# rmmod module_is_live.ko
[root@localhost 009_module_is_alive]# dmesg
[Hello] module_is_live
in init , state is not GOING
in exit, state is GOING
[Goodbye] module_is_live

