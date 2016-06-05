//
// Created by drspaceship on 31/05/16.
//

#include "functionTable.h"

#define NUM_MNEMONICS 24

const assembleFunctionPointer dp = handleDataProcessing;
const assembleFunctionPointer mul = handleMultiply;
const assembleFunctionPointer sdt = handleSDT;
const assembleFunctionPointer branch = handleBranch;
const assembleFunctionPointer lsl = handleLSL;
const assembleFunctionPointer halt = handleHalt;

void functionTableInit(functionTable *this) {
    ListMapInit(&this->listmap);

    functionTableAdd(this, "add", &dp);
    functionTableAdd(this, "sub", &dp);
    functionTableAdd(this, "rsb", &dp);
    functionTableAdd(this, "and", &dp);
    functionTableAdd(this, "eor", &dp);
    functionTableAdd(this, "orr", &dp);
    functionTableAdd(this, "mov", &dp);
    functionTableAdd(this, "tst", &dp);
    functionTableAdd(this, "teq", &dp);
    functionTableAdd(this, "cmp", &dp);
    functionTableAdd(this, "mul", &mul);
    functionTableAdd(this, "mla", &mul);
    functionTableAdd(this, "ldr", &sdt);
    functionTableAdd(this, "str", &sdt);
    functionTableAdd(this, "beq", &branch);
    functionTableAdd(this, "bne", &branch);
    functionTableAdd(this, "bge", &branch);
    functionTableAdd(this, "blt", &branch);
    functionTableAdd(this, "bgt", &branch);
    functionTableAdd(this, "ble", &branch);
    functionTableAdd(this, "b", &branch);
    functionTableAdd(this, "lsl", &lsl);
    functionTableAdd(this, "andeq", &halt);
    functionTableAdd(this, "halt", &halt);
}

void functionTableAdd(
        functionTable *this,
        char *mnen,
        const assembleFunctionPointer *func
) {
    ListMapAdd(&this->listmap, mnen, (void **) func);
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
        char *mnem,
        Assembler *a,
        char **tokens
) {
    assembleFunctionPointer *fp = functionTableGet(this, mnem);
    assert(fp != NULL);
    return (*fp)(a, tokens);
}
