obj-m += hello-1.o
obj-m += hello-2.o
obj-m += hello-3.o
obj-m += hello-4.o
obj-m += hello-5.o
obj-m += hello-6.o
hello-6-objs := hello-6_1.o hello-6_2.o

all:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

load:
	sudo insmod ./hello-1.ko
	sudo insmod ./hello-2.ko
	sudo insmod ./hello-3.ko
	sudo insmod ./hello-4.ko
	sudo insmod ./hello-5.ko myshort=111 mylong=0x999 mystring="oblivion|skyrim?" myarray=6,6,6
	sudo insmod ./hello-6.ko

unload:
	sudo rmmod hello-1
	sudo rmmod hello-2
	sudo rmmod hello-3
	sudo rmmod hello-4
	sudo rmmod hello-5
	sudo rmmod hello-6

clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
