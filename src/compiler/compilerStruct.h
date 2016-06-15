//
// Created by drspaceship on 13/06/16.
//

#ifndef ARM11_39_COMPILERSTRUCT_H
#define ARM11_39_COMPILERSTRUCT_H

#include <util/ListMap.h>

typedef struct Compiler {
    char *sourcePath;
    char *outputPath;
    char **sourceLines;
    int numLines;
    int currLineNum;
    ListMap *variableTable;
    ListMap *opToMnem;
    char **assemblyProgram;
    int instrAddr;
} Compiler_t;

#endif //ARM11_39_COMPILERSTRUCT_H
