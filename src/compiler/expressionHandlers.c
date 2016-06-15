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

static void pinDeclarationHandler(
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
                pinDeclarationHandler(this, variable, atoi(assignArg + 1));
            }
            else {
                if (variable->isPin) {

                }
                else {
                    uint32_t value = (uint32_t) atoi(assignArg);
                    makeLdr(this, variable->regNum, value);
                    variable->value = value;
                }
            }
        }
        else {
            //arithmetic
            char *mnem = ListMapGet(this->opToMnem, &opType, charComparator);
            makeArithmeticWithExpr(
                    this, mnem, variable->regNum,
                    variable->regNum, atoi(assignArg));
        }
    }
}
void ifHandler(Compiler_t *this, char *stmt) {

}
void whileHandler(Compiler_t *this, char *stmt) {

}

static void pinDeclarationHandler(
        Compiler_t *this,
        variable_t *var,
        int pinNum
) {
    var->isPin = true;
    var->controlShift = (pinNum / 10) * 4;
    var->updateMask = 1 << pinNum;
    uint32_t controlMask = 1 << (3 * (pinNum % 10));

    variable_t *gpioPtr = ListMapGet(this->variableTable, GPIO_PTR, stringComparator);
    variable_t *gpioReserved = ListMapGet(this->variableTable, GPIO_RESERVED, stringComparator);

    makeLdr(this, var->regNum, var->updateMask);

    makeArithmeticWithExpr(this, "orr", gpioReserved->regNum,
            gpioReserved->regNum, controlMask);

    //set control to output
    makeStr(this, gpioReserved->regNum, gpioPtr->regNum, var->controlShift);

    //clear pin
    makeStr(this, var->regNum, gpioPtr->regNum, SHIFT_CLEAR);

    //write pin
    makeStr(this, var->regNum, gpioPtr->regNum, SHIFT_WRITE);

}