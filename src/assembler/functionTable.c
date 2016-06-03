//
// Created by drspaceship on 31/05/16.
//

#include "functionTable.h"

void functionTableInit(functionTable *this) {
    ListMapInit(&this->listmap);

    functionTableAdd(this, "add", &handleDataProcessing);
    functionTableAdd(this, "sub", &handleDataProcessing);
    functionTableAdd(this, "rsb", &handleDataProcessing);
    functionTableAdd(this, "and", &handleDataProcessing);
    functionTableAdd(this, "eor", &handleDataProcessing);
    functionTableAdd(this, "orr", &handleDataProcessing);
    functionTableAdd(this, "mov", &handleDataProcessing);
    functionTableAdd(this, "tst", &handleDataProcessing);
    functionTableAdd(this, "teq", &handleDataProcessing);
    functionTableAdd(this, "cmp", &handleDataProcessing);
    functionTableAdd(this, "mul", &handleMultiply);
    functionTableAdd(this, "mla", &handleMultiply);
    functionTableAdd(this, "ldr", &handleSDT);
    functionTableAdd(this, "str", &handleSDT);
    functionTableAdd(this, "beq", &handleBranch);
    functionTableAdd(this, "bne", &handleBranch);
    functionTableAdd(this, "bge", &handleBranch);
    functionTableAdd(this, "blt", &handleBranch);
    functionTableAdd(this, "bgt", &handleBranch);
    functionTableAdd(this, "ble", &handleBranch);
    functionTableAdd(this, "b", &handleBranch);
    functionTableAdd(this, "lsl", &handleLSL);
    functionTableAdd(this, "andeq", &handleHalt);
    functionTableAdd(this, "halt", &handleHalt);
}

void functionTableAdd(
        functionTable *this,
        char *mnen,
        assembleFunctionPointer func
) {
    ListMapAdd(&this->listmap, mnen, func);
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
