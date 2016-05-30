#ifndef ARM11_IO_H
#define ARM11_IO_H

#include <stdio.h>
#include <stdint.h>
#include <util.h>

#define MAX_LINE_LENGTH 512 //maximum line length including newline/EOF

FILE *openFile(char *path, char *mode);
char **readLines(FILE *file);
int writeInstrs(FILE *file, uint32_t *instrs, int length);

#endif //ARM11_IO_H
