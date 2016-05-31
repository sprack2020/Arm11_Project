//
// Created by shiraz on 30/05/16.
//
#ifndef ARM11_39_ASSEMBLER_H
#define ARM11_39_ASSEMBLER_H

#include <assembler/io.h>
#include <util/ListMap.h>
#include <string.h>

#define LABEL_DELIMITER ":"
#define INSTR_LENGTH 4

typedef struct Assembler {
    FILE *sourceFile;
    FILE *binaryFile;
    char **sourceLines;
    uint32_t *binaryProgram;
    int numLines;
    int firstEmptyAddr;
    int currInstrAddr;
} Assembler;

Assembler *newAssembler(char *srcPath);
void Assembler_init(Assembler *a, char *sourceFile);
void assemble(Assembler *this);

#endif //ARM11_39_ASSEMBLER_H
