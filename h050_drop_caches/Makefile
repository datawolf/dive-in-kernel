
EXTRA_CFLAGS := -DMODULE
ARCH := $(shell uname -i)
UNAME := $(shell uname -r)

ifeq ($(KERNEL_BUILD_PATH),)
	KERNEL_BUILD_PATH := /lib/modules/$(UNAME)/build
endif

ifneq ($(findstring mt20190308.130,$(KERNEL_BUILD_PATH)),)
	EXTRA_CFLAGS += -DMTOS_130
endif

ifneq ($(findstring mt20191225.323,$(KERNEL_BUILD_PATH)),)
	EXTRA_CFLAGS += -DMTOS_323
endif

ifneq ($(findstring mt20200626.413,$(KERNEL_BUILD_PATH)),)
	EXTRA_CFLAGS += -DMTOS_413
endif

ifneq ($(KERNELRELEASE), )
obj-m := drop_caches.o
else
KERNELDIR ?=/lib/modules/$(shell uname -r)/build
PWD := $(shell pwd)
all:
	$(MAKE) CFLAGS_MODULE="$(EXTRA_CFLAGS)"  -C $(KERNELDIR) M=$(PWD) modules
clean:
	$(MAKE) CFLAGS_MODULE="$(EXTRA_CFLAGS)" -C $(KERNELDIR) M=$(PWD) clean
load:
	@sudo dmesg -c > /dev/null
	@echo "#############[START] #################"
	@sudo insmod drop_caches.ko
	@sudo dmesg
unload:
	@sudo dmesg -c > /dev/null
	@sudo rmmod drop_caches
	@sudo dmesg
	@echo "#############[ END ] #################"
test:
	@make load
	@make unload
endif
