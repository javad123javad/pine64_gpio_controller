PWD := $(shell pwd)
obj-m  = chr_dev_dtb.o
obj-m += dev_req.o
obj-m +=lagacy_gpio.o
obj-m +=dt_gpio.o
CROSS = aarch64-linux-gnu-
KERNEL_DIR = /lib/modules/`uname -r`/build
all:
	make ARCH=arm64 CROSS_COMPILE=$(CROSS) -C $(KERNEL_DIR) M=$(PWD)
	gcc test_gpio.c -o test_gpio 
clean:
	make -C $(KERNEL_DIR) M=$(PWD) clean
ifneq (,$(wildcard ./test_gpio))
	rm ./test_gpio
endif

       
	
