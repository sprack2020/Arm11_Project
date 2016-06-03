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
    ListMapAdd(&this->listmap, mnen, func);
}

assembleFunctionPointer functionTableGet(
        functionTable *this,
        char *mnen
) {
    return (assembleFunctionPointer) (void **) ListMapGet(&this->listmap, mnen,
                                                          &strcmpFromVoid);
}
