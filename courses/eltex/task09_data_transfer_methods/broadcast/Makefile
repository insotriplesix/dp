RCVR := receiver
BRDR := broadcaster
CC := gcc
CFLAGS := -std=gnu99 -Wall -Wextra -g -pedantic -O2
#LDLIBS := -lpthread

EXECUTABLES := $(RCVR) $(BRDR)

INCDIR := inc
SRCDIR := src

SOURCES := $(wildcard $(SRCDIR)/*.c)
INCLUDES := -I $(INCDIR)

all: clean $(RCVR) $(BRDR)

$(RCVR):
	$(CC) $(CFLAGS) $(INCLUDES) $(SRCDIR)/$(RCVR).c -o $(RCVR)

$(BRDR):
	$(CC) $(CFLAGS) $(INCLUDES) $(SRCDIR)/$(BRDR).c -o $(BRDR)

clean:
	rm -f $(EXECUTABLES)
