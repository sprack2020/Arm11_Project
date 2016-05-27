#ifndef ARM11_IO_H
#define ARM11_IO_H

#include <stdio.h>
#include <stdint.h>
#include "util.c"

FILE* openFile(char* path, char* mode);
char** readLines(FILE* file);
int writeInstrs(FILE* file, uint32_t* instrs, int length);

#endif //ARM11_IO_H
