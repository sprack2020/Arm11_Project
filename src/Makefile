CC      = gcc
CFLAGS  = -I . -Wall -g -D_POSIX_SOURCE -D_BSD_SOURCE -std=c99 -pedantic
LDFLAGS =

EMULATE_SOURCES   = emulate.c emulator/global_state.c emulator/branch.c emulator/checkCond.c emulator/dataProcess.c emulator/dataTransfer.c emulator/decodeAndExecute.c emulator/getOperand2.c emulator/iMultiply.c emulator/printState.c emulator/updateCPSR.c util/util.c
ASSEMBLER_SOURCES = assemble.c assembler/assembler.c assembler/functionTable.c assembler/genInstr.c assembler/io.c assembler/symbolTable.c assembler/tokenHandlers.c assembler/tokenizer.c util/util.c assembler/tokenHandlerUtil.c
ASSEMBLER_STRUCTS = assembler/assemblerStruct.h
COMPILER_SOURCES  = compilerMain.c compiler/compiler.c compiler/compilerFunctionTable.c compiler/compilerTokenizer.c compiler/expressionHandlers.c compiler/instructionMaker.c compiler/variable.c
COMPILER_STRUCTS  = compiler/variableStruct.h compiler/compilerStruct.h
MAP_SOURCES       = util/ListMap.c util/ListMapIterator.c util/ListMapNode.c

EMULATE_OBJECTS   = $(EMULATE_SOURCES:.c=.o)
ASSEMBLER_OBJECTS = $(ASSEMBLER_SOURCES:.c=.o)
COMPILER_OBJECTS  = $(COMPILER_SOURCES:.c=.o)
MAP_OBJECTS       = $(MAP_SOURCES:.c=.o)

BIN_DIR = ../bin
OBJ_DIR = ../obj

all: emulate compile assemble

dirs:
	mkdir -p $(OBJ_DIR)/emulator
	mkdir -p $(OBJ_DIR)/assembler
	mkdir -p $(OBJ_DIR)/compiler

emulate: $(EMULATE_OBJECTS)
	$(CC) $(LDFLAGS) $(addprefix $(OBJ_DIR)/, $^) -o $(BIN_DIR)/$@

assemble: $(ASSEMBLER_OBJECTS) $(MAP_OBJECTS)
	$(CC) $(LDFLAGS) $(addprefix $(OBJ_DIR)/, $^) -o $(BIN_DIR)/$@

compile: $(COMPILER_OBJECTS) $(MAP_OBJECTS)
	$(CC) $(LDFLAGS) $(addprefix $(OBJ_DIR)/, $^) -o $(BIN_DIR)/$@

%.o: %.c %.h
	$(CC) $(CFLAGS) $< -c -o $(OBJ_DIR)/$@

.SUFFIXES: .c .o .h

.PHONY: all clean

clean:
	rm -f $(BIN_DIR)/assemble
	rm -f $(BIN_DIR)/emulate
	rm -f $(BIN_DIR)/compile
	rm -f $(OBJ_DIR)/*.o
	rm -f $(OBJ_DIR)/assembler/*.o
	rm -f $(OBJ_DIR)/emulator/*.o
	rm -f $(OBJ_DIR)/util/*.o
	rm -f $(OBJ_DIR)/compiler/*.o
