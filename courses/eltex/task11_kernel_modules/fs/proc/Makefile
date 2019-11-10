obj-m += proc666.o

all:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

load:
	sudo insmod ./proc666.ko

unload:
	sudo rmmod proc666

clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
