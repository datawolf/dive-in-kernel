ifneq ($(KERNELRELEASE), )
obj-m := test_cap_sys_admin.o
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
	@sudo insmod test_cap_sys_admin.ko
	@sudo dmesg
unload:
	@sudo dmesg -c > /dev/null
	@sudo rmmod test_cap_sys_admin
	@sudo dmesg
	@echo "#############[ END ] #################"
test:
	@make load
	@make unload
endif
