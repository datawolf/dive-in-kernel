ifneq ($(KERNELRELEASE), )
obj-m := proc_cgroups.o
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
	@sudo insmod proc_cgroups.ko
	@sudo dmesg
unload:
	@sudo dmesg -c > /dev/null
	@sudo rmmod proc_cgroups
	@sudo dmesg
	@echo "#############[ END ] #################"
test:
	@make load
	@make unload
endif
