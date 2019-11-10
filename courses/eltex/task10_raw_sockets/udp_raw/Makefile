CLNT := client
SERV := server
CC := gcc
CFLAGS := -std=gnu99 -Wall -Wextra -g -pedantic -O2

EXECUTABLES := $(CLNT) $(SERV)

INCDIR := inc
SRCDIR := src

SOURCES := $(wildcard $(SRCDIR)/*.c)
INCLUDES := -I $(INCDIR)

all: clean $(CLNT) $(SERV)

$(CLNT):
	$(CC) $(CFLAGS) $(INCLUDES) $(SRCDIR)/$(CLNT).c -o $(CLNT)

$(SERV):
	$(CC) $(CFLAGS) $(INCLUDES) $(SRCDIR)/$(SERV).c -o $(SERV)

clean:
	rm -f $(EXECUTABLES)
