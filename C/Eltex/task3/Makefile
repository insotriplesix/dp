EXEC=main
CC=gcc
CFLAGS=-std=gnu99 -Wall -g -pedantic
LIBS=-lpanel -lncurses

#BUILDDIR=build
INCDIR=inc
SRCDIR=src

SOURCES=$(wildcard $(SRCDIR)/*.c)
INCLUDES=-I $(INCDIR)
#OBJECTS=$(patsubst $(SOURCEDIR)/%.c,$(BUILDDIR)/%.o,$(SOURCES))

all: clean $(EXEC)

#dir:
#	mkdir -p $(BUILDDIR)

#$(OBJECTS):
#	$(CC) -c $< -o $@

$(EXEC):
	$(CC) $(CFLAGS) $(INCLUDES) $(EXEC).c $(SOURCES) $(LIBS)

clean:
	rm -f *.out
#	rm -rf $(BUILDDIR)
