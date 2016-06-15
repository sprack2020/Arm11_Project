//
// Created by drspaceship on 14/06/16.
//

#include "expressionHandlers.h"

static bool charComparator(void *char1, void *char2) {
    return *(char *) char1 == *(char *) char2;
}

static bool stringComparator(void *str1, void *str2) {
    return *(char **) str1 == *(char **) str2;
}

static void pinAssignmentHandler(
        Compiler_t *this,
        char *assignment,
        int pinNum
);

//[v1,v2..vn]
void variableHandler(Compiler_t *this, char *declaration) {
    char *varStringList = removeBrackets(declaration);
    char *varString;

    varString = strtok(varStringList, ",");

    variable_t *var = malloc(sizeof(variable_t));
    init_variable(var, 0);

    ListMapAdd(this->variableTable, varString, var);

    int i = 1;
    while ((varString = strtok(NULL, ",")) != NULL) {
        variable_t *newVar = malloc(sizeof(variable_t));
        init_variable(newVar, i);
        ListMapAdd(this->variableTable, varString, newVar);
        i++;
    }
}

//<I =n> or
//<I 'op'n> where op is +,-,*  or
//<I =Pn>
//<Continue>
void assignmentHandler(Compiler_t *this, char *assignment) {
    char *assign = removeBrackets(assignment);
    char *RdVar = getRd(assign);
    variable_t *Rd = ListMapGet(this->variableTable, RdVar, stringComparator);
    char *assignArg = getArgument(assign);

    if (!strcmp(assign, "Continue")) {

    }
    else {
        char opType = getOpType(assign);
        if (opType == '=') {
            //assignment
            if (assignArg[0] == 'P') {

            }
        }
        else {
            //arithmetic
            char *mnem = ListMapGet(this->opToMnem, &opType, charComparator);
            makeArithmeticWithExpr(
                    this->assemblyProgram[this->instrAddr],
                    mnem, Rd->regNum, Rd->regNum, atoi(assignArg));
            this->instrAddr++;
        }
    }
}
void ifHandler(Compiler_t *this, char *stmt) {

}
void whileHandler(Compiler_t *this, char *stmt) {

}

static void pinAssignmentHandler(
        Compiler_t *this,
        char *assignment,
        int pinNum
) {

}