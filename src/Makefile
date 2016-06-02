CC      = gcc
CFLAGS  = -O3 -Wall -g -D_POSIX_SOURCE -D_BSD_SOURCE -std=c99 -Werror -pedantic -I .
LDFLAGS =
SOURCES = emulate.c emulator/global_state.c emulator/branch.c emulator/checkCond.c emulator/dataProcess.c emulator/dataTransfer.c emulator/decodeAndExecute.c emulator/getOperand2.c emulator/iMultiply.c emulator/printState.c emulator/updateCPSR.c util/util.c
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
