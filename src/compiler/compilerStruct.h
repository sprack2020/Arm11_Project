//
// Created by drspaceship on 13/06/16.
//

#ifndef ARM11_39_COMPILERSTRUCT_H
#define ARM11_39_COMPILERSTRUCT_H

typedef struct Compiler {
    char *sourcePath;
    char *outputPath;
    char **sourceLines;
    int numLines;
} Compiler_t;

#endif //ARM11_39_COMPILERSTRUCT_H
