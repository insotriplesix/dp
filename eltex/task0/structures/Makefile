EXEC=main
CC=gcc
CFLAGS=-std=gnu99 -Wall -g

all: clean $(EXEC)

$(EXEC):
	$(CC) $(CFLAGS) $(EXEC).c -o $(EXEC).out

clean:
	rm -f *.out
