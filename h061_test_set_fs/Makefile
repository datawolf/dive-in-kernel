ifneq ($(KERNELRELEASE), )
obj-m := read_write_userspace.o
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
	@sudo insmod read_write_userspace.ko
	@sudo dmesg
unload:
	@sudo dmesg -c > /dev/null
	@sudo rmmod read_write_userspace
	@sudo dmesg
	@echo "#############[ END ] #################"
test:
	@make load
	@make unload
endif
