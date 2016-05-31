//
// Created by shiraz on 30/05/16.
//
#ifndef ARM11_39_ASSEMBLER_H
#define ARM11_39_ASSEMBLER_H

#include <assembler/io.h>
#include <util/ListMap.h>
#include <string.h>
#include <assembler/symbolTable.h>

#define LABEL_DELIMITER ":"
#define INSTR_LENGTH 4

typedef struct Assembler {
    char *sourcePath;
    char *binaryPath;
    char **sourceLines;
    uint32_t *binaryProgram;
    int numLines;
    int numInstrs;
    int firstEmptyAddr;
    int currInstrAddr;
} Assembler;

Assembler *newAssembler(char **argv);
void assemblerInit(Assembler *a, char *sourceFile, char *binaryPath);
void assemble(Assembler *this);
void assemblerDeInit(Assembler *this);
#endif //ARM11_39_ASSEMBLER_H
