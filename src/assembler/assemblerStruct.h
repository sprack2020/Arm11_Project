//
// Created by drspaceship on 31/05/16.
//

#ifndef ARM11_39_ASSEMBLERSTRUCT_H
#define ARM11_39_ASSEMBLERSTRUCT_H

#include <stdint.h>

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

#endif //ARM11_39_ASSEMBLERSTRUCT_H
