ifneq ($(KERNELRELEASE), )
obj-m := test_kallsyms_lookup_name.o
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
	@sudo insmod test_kallsyms_lookup_name.ko
	@sudo dmesg
unload:
	@sudo dmesg -c > /dev/null
	@sudo rmmod test_kallsyms_lookup_name
	@sudo dmesg
	@echo "#############[ END ] #################"
test:
	@make load
	@make unload
	cat /proc/kallsyms | grep -E 'super_blocks|sys_call_table'
endif
