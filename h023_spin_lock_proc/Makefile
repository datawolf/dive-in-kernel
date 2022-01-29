ifneq ($(KERNELRELEASE), )
obj-m := spin_lock_proc.o
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
	@sudo insmod spin_lock_proc.ko
	@sudo dmesg
unload:
	@sudo dmesg -c > /dev/null
	@sudo rmmod spin_lock_proc
	@sudo dmesg
	@echo "#############[ END ] #################"
test:
	@make load
	@make unload
endif
