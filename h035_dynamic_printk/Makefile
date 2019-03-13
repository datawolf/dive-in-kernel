ifneq ($(KERNELRELEASE), )
obj-m := dynamic_printk.o
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
	@sudo insmod dynamic_printk.ko
	@sudo dmesg
unload:
	@sudo dmesg -c > /dev/null
	@sudo rmmod dynamic_printk
	@sudo dmesg
	@echo "#############[ END ] #################"
test:
	@make load
	@make unload
endif
