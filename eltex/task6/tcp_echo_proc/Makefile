CLNT := client
SERV := server
CC := gcc
CFLAGS := -std=gnu99 -Wall -Wextra -g -pedantic -O2

INCDIR := inc
SRCDIR := src

all: clean $(CLNT) $(SERV)

$(CLNT):
	$(CC) $(CFLAGS) $(CLNT).c -o $(CLNT)

$(SERV):
	$(CC) $(CFLAGS) $(SERV).c -o $(SERV)

clean:
	rm -f $(CLNT) $(SERV)
