//
// Created by drspaceship on 31/05/16.
//

#include "functionTable.h"

void functionTableInit(functionTable *this) {
    ListMapInit(&this->listmap);
}

void functionTableAdd(
        functionTable *this,
        char *mnen,
        assembleFunctionPointer func
) {
    ListMapAdd(&this->listmap, mnen, (void **) &func);
}

assembleFunctionPointer *functionTableGet(
        functionTable *this,
        char *mnen
) {
    return ListMapGet(&this->listmap, mnen, &strcmpFromVoid);
}

// TODO: name better, maybe incorporate the getting as well
uint32_t functionTableGetAndApply(
        functionTable *this,
        char *mnen,
        Assembler *a,
        char **tokens
) {
    assembleFunctionPointer *fp = functionTableGet(this, mnen);
    return (*fp)(a, tokens);
}
