#ifndef ARM11_39_SYMBOLTABLE_H
#define ARM11_39_SYMBOLTABLE_H

#include <ctype.h>
#include <assembler/assemblerStruct.h>
#include <assembler/assembler.h>

void createSymbolTableAndCountInstrs(
        Assembler *this
);

void handleLabel(
        Assembler *this,
        char *line,
        int lineNo,
        int *instructionlessLabels
);

bool hasInstr(
        char *line
);

#endif //ARM11_39_SYMBOLTABLE_H
