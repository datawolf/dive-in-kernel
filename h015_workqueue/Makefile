ifneq ($(KERNELRELEASE), )
obj-m := myworkqueue.o
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
	@sudo insmod myworkqueue.ko
	@sudo dmesg
unload:
	@sudo dmesg -c > /dev/null
	@sudo rmmod myworkqueue
	@sudo dmesg
	@echo "#############[ END ] #################"
endif
