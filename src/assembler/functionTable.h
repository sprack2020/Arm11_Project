//
// Created by drspaceship on 31/05/16.
//

#ifndef ARM11_39_FUNCTIONTABLE_H
#define ARM11_39_FUNCTIONTABLE_H

#include <util/ListMap.h>
#include <stdint.h>
#include <assembler/tokenizer.h>
#include <string.h>

typedef struct functionTable {
    ListMap listmap;
} functionTable;

typedef uint32_t (*assembleFunctionPointer)(tokens);

void functionTableInit(
        functionTable *ft
);
void functionTableAdd(
        functionTable *ft,
        char *mnen,
        uint32_t(*func)(tokens)
);
assembleFunctionPointer functionTableGet(
        functionTable *this,
        char *mnen
);

#endif //ARM11_39_FUNCTIONTABLE_H
