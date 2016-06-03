CC = gcc
CFLAGS = -Wall -g -D_POSIX_SOURCE -D_BSD_SOURCE -std=c99 -Werror -pedantic
LDFLAGS =

all: util branch

util:
	$(CC) $(CFLAGS) util_test.c ../../src/util.c -o util_test

branch:
	$(CC) $(CFLAGS) ../../src/branch.c branch_test.c -o branch_test

clean:
	rm -f $(wildcard *.o)
	rm -f util_test
