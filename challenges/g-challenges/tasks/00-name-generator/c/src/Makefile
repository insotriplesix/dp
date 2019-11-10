EXEC=main
CC=gcc
CFLAGS=-std=gnu99 -Wall -g -pedantic

all: clean $(EXEC)

$(EXEC):
	$(CC) $(CFLAGS) $(EXEC).c

clean:
	rm -f *.out
