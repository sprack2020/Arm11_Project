CC      = gcc
CFLAGS  = -Wall -g -D_POSIX_SOURCE -D_BSD_SOURCE -std=c99 -Werror -pedantic
LDFLAGS=
SOURCES=branch.c checkCond.c dataProcess.c dataTransfer.c decodeAndExecute.c emulate.c iMultiply.c printState.c util.c
OBJECTS=$(SOURCES:.c=.o)
EXECUTABLE=emulate

emulator: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
    $(CC) $(LDFLAGS) $(OBJECTS) -o $@

.c.o:
    $(CC) $(CFLAGS) $< -o $@

.SUFFIXES: .c .o

.PHONY: all clean

all: assemble emulate

assemble: assemble.o

emulate: emulate.o

clean:
	rm -f $(wildcard *.o)
	rm -f assemble
	rm -f emulate
