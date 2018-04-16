RCVR := receiver
MLTR := multicaster
CC := gcc
CFLAGS := -std=gnu99 -Wall -Wextra -g -pedantic -O2
#LDLIBS := -lpthread

EXECUTABLES := $(RCVR) $(MLTR)

INCDIR := inc
SRCDIR := src

SOURCES := $(wildcard $(SRCDIR)/*.c)
INCLUDES := -I $(INCDIR)

all: clean $(RCVR) $(MLTR)

$(RCVR):
	$(CC) $(CFLAGS) $(INCLUDES) $(SRCDIR)/$(RCVR).c -o $(RCVR)

$(MLTR):
	$(CC) $(CFLAGS) $(INCLUDES) $(SRCDIR)/$(MLTR).c -o $(MLTR)

clean:
	rm -f $(EXECUTABLES)
