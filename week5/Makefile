KERNELDIR = /lib/modules/$(shell uname -r)/build

obj-m := week5_kthread.o

PWD := $(shell pwd)

all :
	make -C $(KERNELDIR) M=$(PWD) modules

clean:
	make -C $(KERNELDIR) M=$(PWD) clean
