all: clean hello

hello:
	as -o hello.o hello.S
	ld -s -o hello.out hello.o

clean:
	rm -f *.o*
