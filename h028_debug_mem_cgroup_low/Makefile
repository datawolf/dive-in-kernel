ifneq ($(KERNELRELEASE), )
obj-m := debug_mem_cgroup_low.o
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
	@sudo insmod debug_mem_cgroup_low.ko
	@sudo dmesg
unload:
	@sudo dmesg -c > /dev/null
	@sudo rmmod debug_mem_cgroup_low
	@sudo dmesg
	@echo "#############[ END ] #################"
test:
	@make load
	@make unload
endif
