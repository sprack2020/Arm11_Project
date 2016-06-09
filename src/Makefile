CC      = gcc
CFLAGS  = -Wall -g -D_POSIX_SOURCE -D_BSD_SOURCE -std=c99 -pedantic -I .
LDFLAGS =
EMULATE_SOURCES = emulate.c emulator/global_state.c emulator/branch.c emulator/checkCond.c emulator/dataProcess.c emulator/dataTransfer.c emulator/decodeAndExecute.c emulator/getOperand2.c emulator/iMultiply.c emulator/printState.c emulator/updateCPSR.c util/util.c
EMULATE_OBJECTS =  $(EMULATE_SOURCES:.c=.o)
ASSEMBLER_SOURCES = assemble.c assembler/assembler.c assembler/functionTable.c assembler/genInstr.c assembler/io.c assembler/symbolTable.c assembler/tokenHandlers.c assembler/tokenizer.c util/util.c util/ListMap.c util/ListMapIterator.c util/ListMapNode.c assembler/tokenHandlerUtil.c
ASSEMBLER_OBJECTS =  $(ASSEMBLER_SOURCES:.c=.o)


all: emulate assemble

emulate: $(EMULATE_OBJECTS)

assemble: $(ASSEMBLER_OBJECTS)

%.o: %.c %.h
	$(CC) $(CFLAGS) $< -c -o $@

.SUFFIXES: .c .o

.PHONY: all clean

clean:
	rm -f $(wildcard *.o)
	rm -f assemble
	rm -f emulate
