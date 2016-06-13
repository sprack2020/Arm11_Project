//
// Created by Shiraz Butt on 13/06/2016.
//

#include "FunctionTable.h"

static bool stmtTypeComparator(void *stmt1, void *stmt2) {
    return *(StmtType *) stmt1 == *(StmtType *) stmt2;
}

// intialises the given function table
FunctionTable *FunctionTable_init(FunctionTable *this) {
    assert(this != NULL);

    ListMapInit(this->map);

    return this;
}

// deinitialises a FunctionTable
FunctionTable *FunctionTable_deinit(FunctionTable *this, void (*deleter)(void *, void *)) {
    assert(this != NULL);

    ListMapDeinit(this->map, deleter);

    return this;
}

// gets the function associated with a statement type
StatementHandler FunctionTable_get(FunctionTable *this, StmtType stmtType) {
    assert(this != NULL);

    StatementHandler *handlerPtr = ListMapGet(this->map, &stmtType, &stmtTypeComparator);

    return *handlerPtr;
}

// adds a (stmtType, stmtHandler) pair to the map
void FunctionTable_add(FunctionTable *this, StmtType stmtType, StatementHandler *handlerPtr) {
    ListMapAdd(this->map, (void *) (intptr_t) stmtType, handlerPtr);
}

//char *FunctionTable_getAndApply(FunctionTable *this, StmtType stmtType, void *something) {
//    return FunctionTable_get(this, stmtType)(something);
//}
