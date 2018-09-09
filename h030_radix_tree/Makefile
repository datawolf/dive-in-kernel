ifneq ($(KERNELRELEASE), )
obj-m := radix_tree_example.o
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
	@sudo insmod radix_tree_example.ko
	@sudo dmesg
unload:
	@sudo dmesg -c > /dev/null
	@sudo rmmod radix_tree_example
	@sudo dmesg
	@echo "#############[ END ] #################"
test:
	@make load
	@make unload
endif
