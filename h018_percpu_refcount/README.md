## 说明

只有调用了`percpu_ref_kill`后，后续的`percpu_ref_put`才会检测引用计数是否为0;
当引用计数为0时，才会调用`release`方法。
