NAME := hello
VER := $(shell uname -r)
KDIR ?= /lib/modules/$(VER)/build

obj-m += $(NAME).o

all:
	$(MAKE) -C $(KDIR) M=$(PWD) modules

load:
	sudo insmod ./$(NAME).ko

unload:
	sudo rmmod $(NAME)

clean:
	$(MAKE) -C $(KDIR) M=$(PWD) clean