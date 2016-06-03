//
// Created by drspaceship on 31/05/16.
//

#ifndef ARM11_39_ASSEMBLERSTRUCT_H
#define ARM11_39_ASSEMBLERSTRUCT_H

#include <stdint.h>

#include <util/ListMap.h>
#include <assembler/symbolTable.h>

typedef struct Assembler {
    char *sourcePath;
    char *binaryPath;
    char **sourceLines;
    int numLines;
    uint32_t *binaryProgram;
    int numInstrs;
    int firstEmptyAddr;
    int currInstrAddr;
    symbolTable symbolTable;
} Assembler;

#endif //ARM11_39_ASSEMBLERSTRUCT_H
