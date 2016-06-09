//
// Created by drspaceship on 31/05/16.
//

#include "functionTable.h"

#define NUM_MNEMONICS 24

static void functionTableDeleter(
        void *mnem,
        void *fp
);

const instructionHandler dp = handleDataProcessing;
const instructionHandler mul = handleMultiply;
const instructionHandler sdt = handleSDT;
const instructionHandler branch = handleBranch;
const instructionHandler lsl = handleLSL;
const instructionHandler halt = handleHalt;

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
        const instructionHandler *func
) {
    ListMapAdd(&this->listmap, mnen, (void **) func);
}

instructionHandler *functionTableGet(
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
    instructionHandler *fp = functionTableGet(this, mnem);
    assert(fp != NULL);
    return (*fp)(a, tokens);
}

// frees the elements of a function table.
// do nothing as mnem is a pointer to sourceLines and fp is a pointer to a
// function pointer.
static void functionTableDeleter(void *mnem, void *fp) {
}

void functionTableDeinit(functionTable *this) {
    ListMapDeinit((ListMap *) this, &functionTableDeleter);
}
