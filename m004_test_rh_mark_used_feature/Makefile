ifneq ($(KERNELRELEASE), )
obj-m := test_rh_mark_used_feature.o
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
	@sudo cat /proc/driver/rh_features
	@sudo insmod test_rh_mark_used_feature.ko
	@sudo cat /proc/driver/rh_features
	@sudo dmesg
unload:
	@sudo dmesg -c > /dev/null
	@sudo rmmod test_rh_mark_used_feature
	@sudo dmesg
	@echo "#############[ END ] #################"
test:
	@make load
	@make unload
endif
