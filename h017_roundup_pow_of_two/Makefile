ifneq ($(KERNELRELEASE), )
obj-m := roundup_pow_of_two.o
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
	@sudo insmod roundup_pow_of_two.ko
	@sudo dmesg
unload:
	@sudo dmesg -c > /dev/null
	@sudo rmmod roundup_pow_of_two
	@sudo dmesg
	@echo "#############[ END ] #################"
test:
	@make load
	@make unload
endif
