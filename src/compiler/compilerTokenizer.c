//
// Created by drspaceship on 14/06/16.
//

#include "compilerTokenizer.h"

//PRE: stmt is [something] or <something>
//']' could be any bracket
//return something

char *removeBrackets(char *stmt) {

    //stmt + 1 removes first bracket
    return strtok((stmt + 1), ">])");
}

//makes reg string for var->reg map
char *getFreeReg(int regNum, char *reg) {
    assert(regNum < 8);
    sprintf(reg, "r%i", regNum);
    return reg;
}

//str is the stmt in <stmt>
char getOpType(char *str) {
    str = strtok(str, " ");
    assert(str != NULL);
    return str[0];
}

char *getRd(char *str) {
    str = strtok(str, "=+-*");
    assert(str != NULL);
    return str;
}

char *getArgument(char *str) {
    str = strtok(str, "=+-*");
    assert(str != NULL);
    return strtok(NULL, "\0");
}

char *getBool(char *str) {
    assert(str != NULL);
    strtok(str, "(");
    return strtok(NULL, ")");
}

