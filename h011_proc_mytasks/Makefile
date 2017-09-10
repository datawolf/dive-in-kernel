ifneq ($(KERNELRELEASE), )
obj-m := proc_mytasks.o
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
	@sudo insmod proc_mytasks.ko
	@sudo dmesg
unload:
	@sudo dmesg -c > /dev/null
	@sudo rmmod proc_mytasks
	@sudo dmesg
	@echo "#############[ END ] #################"
test:
	@make load
	@make unload
endif
