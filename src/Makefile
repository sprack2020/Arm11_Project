CC      = gcc
CFLAGS  = -Wall -g -D_POSIX_SOURCE -D_BSD_SOURCE -std=c99 -pedantic -I .
LDFLAGS =
EMULATE_SOURCES = emulate.c emulator/global_state.c emulator/branch.c emulator/checkCond.c emulator/dataProcess.c emulator/dataTransfer.c emulator/decodeAndExecute.c emulator/getOperand2.c emulator/iMultiply.c emulator/printState.c emulator/updateCPSR.c util/util.c
EMULATE_OBJECTS =  $(addprefix $(OUTPUT_DIR)/, $(EMULATE_SOURCES:.c=.o))
ASSEMBLER_SOURCES = assemble.c assembler/assembler.c assembler/functionTable.c assembler/genInstr.c assembler/io.c assembler/symbolTable.c assembler/tokenHandlers.c assembler/tokenizer.c util/util.c assembler/tokenHandlerUtil.c
ASSEMBLER_STRUCTS = assembler/assemblerStruct.h
ASSEMBLER_OBJECTS =  $(ASSEMBLER_SOURCES:.c=.o)
COMPILER_SOURCES = compilerMain.c compiler/compiler.c compiler/compilerFunctionTable.c compiler/compilerTokenizer.c compiler/expressionHandlers.c compiler/instructionMaker.c compiler/variable.c
COMPILER_STRUCTS = compiler/variableStruct.h compiler/compilerStruct.h
COMPILER_OBJECTS = $(COMPILER_SOURCES:.c=.o)
MAP_SOURCES = util/ListMap.c util/ListMapIterator.c util/ListMapNode.c
MAP_OBJECTS = $(MAP_SOURCES:.c=.o)
OUTPUT_DIR = ../bin

all: emulate assemble compile

emulate: $(EMULATE_OBJECTS)
	$(CC) $(LDFLAGS) $^ -o $(OUTPUT_DIR)/$@

assemble: $(MAP_OBJECTS) $(ASSEMBLER_STRUCTS) $(ASSEMBLER_OBJECTS)

compile: $(MAP_OBJECTS) $(COMPILER_STRUCTS) $(COMPILER_OBJECTS)

%.o: %.c %.h
	$(CC) $(CFLAGS) $< -c -o $(OUTPUT_DIR)/$@

.SUFFIXES: .c .o

.PHONY: all clean

clean:
	rm -f $(OUTPUT_DIR)/assemble
	rm -f $(OUTPUT_DIR)/emulate
	rm -f $(OUTPUT_DIR)/emulator/*.o
	rm -f $(OUTPUT_DIR)/util/*.o
	rm -f $(OUTPUT_DIR)/assembler/*.o
