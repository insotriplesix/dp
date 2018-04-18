TCPCLNT := tcp_client
UDPCLNT := udp_client
SERV := server
THPOOL := threadpool
CC := gcc
CFLAGS := -std=gnu99 -Wall -Wextra -g -pedantic -O2
LDLIBS := -lpthread

EXECUTABLES := $(TCPCLNT) $(UDPCLNT) $(SERV)

INCDIR := inc
SRCDIR := src

#SOURCES := $(wildcard $(SRCDIR)/*.c)
INCLUDES := -I $(INCDIR)

all: clean $(TCPCLNT) $(UDPCLNT) $(SERV)

$(TCPCLNT):
	$(CC) $(CFLAGS) $(INCLUDES) $(SRCDIR)/$(TCPCLNT).c -o $(TCPCLNT)

$(UDPCLNT):
	$(CC) $(CFLAGS) $(INCLUDES) $(SRCDIR)/$(UDPCLNT).c -o $(UDPCLNT)

$(SERV):
	$(CC) $(CFLAGS) $(INCLUDES) $(SRCDIR)/$(SERV).c $(SRCDIR)/$(THPOOL).c $(LDLIBS) -o $(SERV)

clean:
	rm -f $(EXECUTABLES)
