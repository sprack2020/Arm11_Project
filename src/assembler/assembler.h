#ifndef ARM11_39_ASSEMBLER_H
#define ARM11_39_ASSEMBLER_H

#include <string.h>

#include <assembler/assemblerStruct.h>
#include <assembler/io.h>
#include <assembler/symbolTable.h>
#include <util/ListMap.h>
#include <assembler/functionTable.h>
#include <assembler/tokenizer.h>


#define LABEL_DELIMITER ":"
#define INSTR_LENGTH 4
#define NUM_TOKENS 6


Assembler *newAssembler(char *sourcePath, char *binaryPath);
void assemblerInit(Assembler *a, char *sourceFile, char *binaryPath);
void assemble(Assembler *this);
void assemblerDeInit(Assembler *this);

#endif //ARM11_39_ASSEMBLER_H
