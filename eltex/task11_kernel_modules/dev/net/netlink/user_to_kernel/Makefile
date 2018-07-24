obj-m += netlink3000.o

all:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules
	gcc --std=gnu99 -Wall -Wextra -Werror -pedantic user_netlink.c

load:
	sudo insmod ./netlink3000.ko

unload:
	sudo rmmod netlink3000

clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
	rm -f a.out
