CLNT := traceroute
CC := gcc
CFLAGS := -std=gnu99 -Wall -Wextra -g -pedantic -O0

EXECUTABLES := $(CLNT)

INCDIR := inc
SRCDIR := src

SOURCES := $(wildcard $(SRCDIR)/*.c)
INCLUDES := -I $(INCDIR)

all: clean $(CLNT)

$(CLNT):
	$(CC) $(CFLAGS) $(INCLUDES) $(SRCDIR)/$(CLNT).c -o $(CLNT)

clean:
	rm -f $(EXECUTABLES)
