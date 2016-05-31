//
// Created by drspaceship on 31/05/16.
//

#ifndef ARM11_39_SYMBOLTABLE_H
#define ARM11_39_SYMBOLTABLE_H

#include <assembler/assembler.h>


void createSymbolTableAndCountInstrs(
        Assembler *this,
        ListMap *symbolTable
);
void handleLabel(
        Assembler *this,
        char *line,
        int lineNo,
        int *instructionlessLabels,
        ListMap *symbolTable
);
bool hasInstr(
        char *line
);

#endif //ARM11_39_SYMBOLTABLE_H
