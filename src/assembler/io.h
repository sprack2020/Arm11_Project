#ifndef ARM11_IO_H
#define ARM11_IO_H

#include <stdio.h>

FILE* openFile(const char* path, const char* mode);
char** readLines(FILE* file);

#endif //ARM11_IO_H
