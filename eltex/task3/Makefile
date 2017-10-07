EXEC=main
CC=gcc
CFLAGS=-std=gnu99 -Wall -g -pedantic
LIBS=-lncurses

INCDIR=inc
SRCDIR=src

SOURCES=$(wildcard $(SRCDIR)/*.c)
INCLUDES=-I $(INCDIR)

all: clean $(EXEC)

$(EXEC):
	$(CC) $(CFLAGS) $(INCLUDES) $(EXEC).c $(SOURCES) $(LIBS)

clean:
	rm -f *.out
