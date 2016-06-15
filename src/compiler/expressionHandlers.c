//
// Created by drspaceship on 14/06/16.
//

#include "expressionHandlers.h"

static bool charComparator(void *char1, void *char2) {
    return *(char *) char1 == *(char *) char2;
}

static bool stringComparator(void *str1, void *str2) {
    return (bool) !strcmp((char*)str1, (char*)str2);
}

static void pinDeclarationHandler(
        Compiler_t *this,
        variable_t *var,
        int pinNum
);

static void pinAssignmentHandler(
        Compiler_t *this,
        variable_t *var,
        int state
);

//[v1,v2..vn]
void variableHandler(Compiler_t *this, char *declaration) {
    char *varStringList = removeBrackets(declaration);
    char *varString;

    //req free
    varString = strtok(strdup(varStringList), ",");

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
void assignmentHandler(Compiler_t *this, char *assignment, int whildID) {
    //requires freeing
    char *assign = removeBrackets(assignment);
    char *varString = getRd(assign);

    variable_t *variable = ListMapGet(this->variableTable, varString, stringComparator);
    //requires freeing
    char *assignArg = getArgument(assign);

    if (!strcmp(assign, "Continue")) {
        makeBranch(this, "b", "while", whildID);
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
                    pinAssignmentHandler(this, variable, atoi(assignArg));
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
    free(assign);
    free(varString);
//    free(assignArg);
}
void ifHandler(Compiler_t *this, char *stmt, int whileID, int ifID) {

    char *boolVar = getBool(stmt);
    bool isNegated = boolVar[0] == '!';
    if (isNegated) {
        boolVar++;
    }

    variable_t *var = ListMapGet(this->variableTable, boolVar, stringComparator);
    variable_t *gpioReserved = ListMapGet(this->variableTable, GPIO_RESERVED, stringComparator);
    variable_t *gpioState = ListMapGet(this->variableTable, GPIO_STATE, stringComparator);

    makeLabel(this, "if", ifID);
    if (var->isPin) {
        makeArithmetic(this, "and", gpioReserved->regNum, gpioState->regNum, var->regNum);
        makeCmp(this, gpioReserved->regNum);
    }
    else {
        makeCmp(this, var->regNum);
    }
    makeBranch(this, (isNegated) ? "bne" : "beq", "endif", ifID);
    parseInstructions(this, whileID, ifID + 1);
    makeLabel(this, "endif", ifID);
}

//var can't be a gpio variable
void whileHandler(Compiler_t *this, char *stmt, int whileID, int ifID) {
    variable_t *var = ListMapGet(this->variableTable, getBool(stmt), stringComparator);

    makeLabel(this, "while", whileID);
    makeCmp(this, var->regNum);
    makeBranch(this, "beq", "endwhile", whileID);
    parseInstructions(this, whileID + 1, ifID);
    makeBranch(this, "b", "while", whileID);
    makeLabel(this, "endwhile", whileID);
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

    //set the register to the updateMask
    makeLdr(this, var->regNum, var->updateMask);

    //get control mask
    makeArithmeticWithExpr(this, "orr", gpioReserved->regNum,
            gpioReserved->regNum, controlMask);

    //set control to output
    makeStr(this, gpioReserved->regNum, gpioPtr->regNum, var->controlShift);

    //clear pin
    makeStr(this, var->regNum, gpioPtr->regNum, SHIFT_CLEAR);

    //write pin
    makeStr(this, var->regNum, gpioPtr->regNum, SHIFT_WRITE);

}

static void pinAssignmentHandler(
        Compiler_t *this,
        variable_t *var,
        int state
) {
    variable_t *gpioPtr = ListMapGet(this->variableTable, GPIO_PTR, stringComparator);
    variable_t *gpioState = ListMapGet(this->variableTable, GPIO_STATE, stringComparator);
    variable_t *gpioReserved = ListMapGet(this->variableTable, GPIO_RESERVED, stringComparator);

    if (state) {
        makeStr(this, var->regNum, gpioPtr->regNum, SHIFT_WRITE);
        makeArithmetic(this, "orr", gpioState->regNum, gpioState->regNum, var->regNum);
        var->value = 1;
    }
    else {
        makeStr(this, var->regNum, gpioPtr->regNum, SHIFT_CLEAR);
        makeLdr(this, gpioReserved->regNum, 0xffffffff);
        makeArithmetic(this, "sub", gpioReserved->regNum, gpioReserved->regNum, var->regNum);
        makeArithmetic(this, "and", gpioState->regNum, gpioState->regNum, gpioReserved->regNum);
        var->value = 0;
    }
}