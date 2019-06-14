ifneq ($(KERNELRELEASE), )
obj-m := my_test_rcu.o
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
	@sudo insmod my_test_rcu.ko
	@sudo dmesg
unload:
	@sudo dmesg -c > /dev/null
	@sudo rmmod my_test_rcu
	@sudo dmesg
	@echo "#############[ END ] #################"
test:
	@make load
	@make unload
endif
