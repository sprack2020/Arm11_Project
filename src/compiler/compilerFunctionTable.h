//
// Created by Shiraz Butt on 13/06/2016.
//

#ifndef ARM11_39_FUNCTIONTABLE_H
#define ARM11_39_FUNCTIONTABLE_H

#include <util/ListMap.h>
#include <stdint.h>
#include <compiler/expressionHandlers.h>

// dont know the type so i did this:

typedef enum {
    T1
} StmtType;

typedef char *(*StatementHandler)(void *);

typedef struct FunctionTable {
    ListMap *map;
} FunctionTable;

FunctionTable *FunctionTable_init(
        FunctionTable *this
);

FunctionTable *FunctionTable_deinit(
        FunctionTable *this,
        void (*deleter)(void *, void *)
);

StatementHandler FunctionTable_get(
        FunctionTable *this,
        StmtType stmtType
);

void FunctionTable_add(
        FunctionTable *this,
        StmtType stmtType,
        StatementHandler *handler
);

FunctionTable *FunctionTable_remove(
        FunctionTable *this,
        StmtType stmtType,
        StatementHandler handler
);

// shouldnt be required
char *FunctionTable_getAndApply(
        FunctionTable *this,
        StmtType stmtType,
        void *something /* whatever other arguments */
);

#endif //ARM11_39_FUNCTIONTABLE_H
