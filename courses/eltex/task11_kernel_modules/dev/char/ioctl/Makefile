obj-m += oblivion_ioctl.o

all:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules
	gcc -std=gnu99 -Wall -Wextra -Werror -pedantic user_ioctl.c

load:
	sudo insmod ./oblivion_ioctl.ko

unload:
	sudo rmmod oblivion_ioctl

clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
	rm -f a.out
