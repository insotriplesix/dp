EXEC := pipe
CC := gcc
CFLAGS := -std=gnu99 -Wall -Wextra -g -pedantic -O2

all: clean $(EXEC)

$(EXEC):
	$(CC) $(CFLAGS) main.c -o $(EXEC)

clean:
	rm -f $(EXEC)
