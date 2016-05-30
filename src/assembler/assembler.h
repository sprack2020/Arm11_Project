//
// Created by shiraz on 30/05/16.
//
#ifndef ARM11_39_ASSEMBLER_H
#define ARM11_39_ASSEMBLER_H

#include <assembler/io.h>

typedef struct Assembler {
    FILE *sourceFile;
    FILE *binaryFile;
    char **srcLines;
    uint32_t *binaryProgram;
    int numInstrs;
    int firstEmptyAddr;
    int currInstrAddr;
} Assembler;

Assembler *newAssembler(char *srcPath);
void Assembler_init(Assembler *a, char *sourceFile);
void assemble(Assembler *this);

#endif //ARM11_39_ASSEMBLER_H
