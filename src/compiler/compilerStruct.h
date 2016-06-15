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
    ListMap *variableTable;
    ListMap *opToMnem;
    char **assemblyProgram;
    int instrAddr;
    //wtf is varRegNum? was I high?
    int varRegNum;
    int whileID;
} Compiler_t;

#endif //ARM11_39_COMPILERSTRUCT_H
