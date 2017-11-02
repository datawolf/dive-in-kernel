ifneq ($(KERNELRELEASE), )
obj-m := list_all_bdi.o
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
	@sudo insmod list_all_bdi.ko
	@sudo dmesg
unload:
	@sudo dmesg -c > /dev/null
	@sudo rmmod list_all_bdi
	@sudo dmesg
	@echo "#############[ END ] #################"
test:
	@make load
	@make unload
endif
