obj-m += netfilter.o

all:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules
#	gcc --std=gnu99 -Wall -Wextra -Werror -pedantic user_netfilter.c

load:
	sudo insmod ./netfilter.ko

unload:
	sudo rmmod netfilter

clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
#	rm -f a.out
