obj-m += sys666.o

all:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

load:
	sudo insmod ./sys666.ko

unload:
	sudo rmmod sys666

clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
