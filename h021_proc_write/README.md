## 说明

本模块用来验证 proc中的write接口中count值的含义，并验证其正确的处理方法。


### 不进行 cmd[count-1] = '\0'; 处理

```
~/dive-in-kernel/h021_proc_write (master) # echo "helloworld" > /proc/proc_write 
root@127.0.0.1::[00:29:58]::[Exit Code: 0] ->
~/dive-in-kernel/h021_proc_write (master) # cat /proc/proc_write 
helloworld
(11)
root@127.0.0.1::[00:30:04]::[Exit Code: 0] ->
~/dive-in-kernel/h021_proc_write (master) # echo "12" > /proc/proc_write 
root@127.0.0.1::[00:30:19]::[Exit Code: 0] ->
~/dive-in-kernel/h021_proc_write (master) # cat /proc/proc_write 
12
loworld
(11)
root@127.0.0.1::[00:30:23]::[Exit Code: 0] ->
```

### 进行 cmd[count-1] = '\0'; 处理

```
root@127.0.0.1::[00:33:59]::[Exit Code: 0] ->
~/dive-in-kernel/h021_proc_write (master) # echo "helloworld" > /proc/proc_write 
root@127.0.0.1::[00:34:11]::[Exit Code: 0] ->
~/dive-in-kernel/h021_proc_write (master) # cat /proc/proc_write 
helloworld(10)
root@127.0.0.1::[00:34:18]::[Exit Code: 0] ->
~/dive-in-kernel/h021_proc_write (master) # echo "12" > /proc/proc_write 
root@127.0.0.1::[00:34:33]::[Exit Code: 0] ->
~/dive-in-kernel/h021_proc_write (master) # cat /proc/proc_write 
12(2)
root@127.0.0.1::[00:34:35]::[Exit Code: 0] ->
~/dive-in-kernel/h021_proc_write (master) # 
```

所以，当将输入当做字符串处理时，需要将末尾的`\n`换成`\0`.
