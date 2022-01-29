ifneq ($(KERNELRELEASE), )
obj-m := get_cwd_exe.o
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
	@sudo insmod get_cwd_exe.ko
	@sudo dmesg
unload:
	@sudo dmesg -c > /dev/null
	@sudo rmmod get_cwd_exe
	@sudo dmesg
	@echo "#############[ END ] #################"
test:
	@make load
	@make unload
endif
