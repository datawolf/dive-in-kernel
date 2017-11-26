ifneq ($(KERNELRELEASE), )
obj-m := percpu_refcount.o
else
KERNELDIR ?=/lib/modules/$(shell uname -r)/build
PWD := $(shell pwd)
all:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) modules
clean:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) clean 
load:
	@sudo dmesg -c > /dev/null
	@echo "#############[START] #################"
	@sudo insmod percpu_refcount.ko
	@sudo dmesg
unload:
	@sudo dmesg -c > /dev/null
	@sudo rmmod percpu_refcount
	@sudo dmesg
	@echo "#############[ END ] #################"
test:
	@make load
	@make unload
endif
