ifneq ($(KERNELRELEASE), )
obj-m := calc_load_account_active.o
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
	@sudo insmod calc_load_account_active.ko
	@sudo dmesg
unload:
	@sudo dmesg -c > /dev/null
	@sudo rmmod calc_load_account_active
	@sudo dmesg
	@echo "#############[ END ] #################"
test:
	@make load
	@make unload
endif
