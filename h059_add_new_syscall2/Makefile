ifneq ($(KERNELRELEASE), )
obj-m := add_new_syscall.o
else
KERNELDIR ?=/lib/modules/$(shell uname -r)/build
PWD := $(shell pwd)
all:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) modules
	gcc -o test_syscall test.c
clean:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) clean 
	rm -fr test_syscall
load:
	@sudo dmesg -c > /dev/null
	@echo "#############[START] #################"
	@sudo insmod add_new_syscall.ko
	@sudo dmesg
unload:
	@sudo dmesg -c > /dev/null
	@sudo rmmod add_new_syscall
	@sudo dmesg
	@echo "#############[ END ] #################"
test:
	@make load
	./test_syscall
	sleep 2
	@sudo dmesg
	@make unload
endif
