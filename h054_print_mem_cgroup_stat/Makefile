ifneq ($(KERNELRELEASE), )
obj-m := print_mem_cgroup_stat.o
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
	@sudo insmod print_mem_cgroup_stat.ko
	@sudo dmesg
unload:
	@sudo dmesg -c > /dev/null
	@sudo rmmod print_mem_cgroup_stat
	@sudo dmesg
	@echo "#############[ END ] #################"
test:
	@make load
	@make unload
endif
