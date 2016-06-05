//
// Created by drspaceship on 31/05/16.
//

#ifndef ARM11_39_FUNCTIONTABLE_H
#define ARM11_39_FUNCTIONTABLE_H

#include <util/ListMap.h>
#include <stdint.h>
#include <assembler/tokenizer.h>
#include <string.h>
#include <assembler/assemblerStruct.h>
#include <util/util.h>
#include <assembler/tokenHandlers.h>

typedef struct functionTable {
    ListMap listmap;
} functionTable;

typedef uint32_t (*assembleFunctionPointer)(Assembler *, char **);

void functionTableInit(
        functionTable *ft
);

void functionTableAdd(
        functionTable *ft,
        char *mnen,
        const assembleFunctionPointer *fs
);

assembleFunctionPointer *functionTableGet(
        functionTable *this,
        char *mnen
);

uint32_t functionTableGetAndApply(
        functionTable *this,
        char *mnen,
        Assembler *a,
        char **tokens
);

#endif //ARM11_39_FUNCTIONTABLE_H
