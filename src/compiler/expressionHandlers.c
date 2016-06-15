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
        variable_t *var,
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
    char *varString = getRd(assign);
    variable_t *variable = ListMapGet(this->variableTable, varString, stringComparator);
    char *assignArg = getArgument(assign);

    if (!strcmp(assign, "Continue")) {
        //some way of branching to correct while label
    }
    else {
        char opType = getOpType(assign);
        if (opType == '=') {
            //assignment
            if (assignArg[0] == 'P') {
                pinAssignmentHandler(this, variable, atoi(assignArg + 1));
            }
            else {
                makeLdr(this->assemblyProgram[this->instrAddr],
                        variable->regNum, atoi(assignArg));
                this->instrAddr++;
            }
        }
        else {
            //arithmetic
            char *mnem = ListMapGet(this->opToMnem, &opType, charComparator);
            makeArithmeticWithExpr(
                    this->assemblyProgram[this->instrAddr],
                    mnem, variable->regNum, variable->regNum, atoi(assignArg));
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
        variable_t *var,
        int pinNum
) {

}