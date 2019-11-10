obj-m += oblivion.o

all:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

load:
	sudo insmod ./oblivion.ko

unload:
	sudo rmmod oblivion

clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
