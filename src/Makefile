CC      = gcc
CFLAGS  = -Wall -g -D_POSIX_SOURCE -D_BSD_SOURCE -std=c99 -Werror -pedantic -I src
LDFLAGS =
SOURCES = emulate.c branch.c checkCond.c dataProcess.c dataTransfer.c decodeAndExecute.c getOperand2.c iMultiply.c printState.c updateCPSR.c util.c
OBJECTS = $(SOURCES:.c=.o)
EXECUTABLE = emulate

all: emulate

# emulator: $(SOURCES) $(EXECUTABLE)
#
# $(EXECUTABLE): $(OBJECTS)
# 	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

# %.o: %.c
# 	$(CC) $(CFLAGS) $< -o $@

emulate:
	$(CC) $(SOURCES) $(CFLAGS) -o emulate

# Given makefile, don't know how these work?
# .SUFFIXES: .c .o
#
# .PHONY: all clean
#
# all: assemble emulate
#
# assemble: assemble.o
#
# emulate: emulate.o

clean:
	rm -f $(wildcard *.o)
	rm -f assemble
	rm -f emulate
