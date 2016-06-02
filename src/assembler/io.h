#ifndef ARM11_IO_H
#define ARM11_IO_H

#include <assembler/assembler.h>
#include <stdio.h>
#include <stdint.h>
#include <util/util.h>


#define MAX_LINE_LENGTH 512 //maximum line length including newline/EOF

FILE *openFile(char *path, char *mode);
void closeFile(FILE *file);
int writeInstrs(FILE *file, uint32_t *instrs, int length);
int countLines(FILE *file);

#endif //ARM11_IO_H
