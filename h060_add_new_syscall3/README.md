
本来打算使用新的方法是这系统调用表可写：

```
/*
 * Functions to change memory attributes.
 */
int set_memory_ro(unsigned long addr, int numpages);
int set_memory_rw(unsigned long addr, int numpages);
int set_memory_x(unsigned long addr, int numpages);
int set_memory_nx(unsigned long addr, int numpages);
```

但经过实验发现，该方法无法完成。
在 set_memory_rw() 内部调用的set_memory_rw() static_protections()函数会在以下情况下删除_PAGE_RW标志：

* 它在 BIOS 区域
* 地址在 .rodata 里面
* CONFIG_DEBUG_RODATA 设置，内核设置为只读


参考：https://qa.icopy.site/questions/2103315/linux-kernel-system-call-hooking-example?noredirect=1
参考：https://elixir.bootlin.com/linux/v5.10/source/arch/x86/mm/pat/set_memory.c#L526

