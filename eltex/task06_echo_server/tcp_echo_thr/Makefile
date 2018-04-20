CLNT := client
SERV := server
CC := gcc
CFLAGS := -std=gnu99 -Wall -Wextra -g -pedantic -O2
LDLIBS := -lpthread

all: clean $(CLNT) $(SERV)

$(CLNT):
	$(CC) $(CFLAGS) $(CLNT).c -o $(CLNT)

$(SERV):
	$(CC) $(CFLAGS) $(SERV).c $(LDLIBS) -o $(SERV)

clean:
	rm -f $(CLNT) $(SERV)
