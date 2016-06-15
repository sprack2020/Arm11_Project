//
// Created by drspaceship on 14/06/16.
//

#include "compilerTokenizer.h"

//PRE: stmt is [something] or <something>
//']' could be any bracket
//return something
//needs free
char *removeBrackets(char *stmt) {

    //stmt + 1 removes first bracket
    return strtok(strdup(stmt + 1), ">])");
}

//makes reg string for var->reg map
char *getFreeReg(int regNum, char *reg) {
    assert(regNum < 8);
    sprintf(reg, "r%i", regNum);
    return reg;
}

//str is the stmt in <stmt>
char getOpType(char *str) {
    while (!isspace(*str)) {
        str++;
    }
    return *(str + 1);
}

//needs free
char *getRd(char *str) {
    assert(str != NULL);
    return strtok(strdup(str), " ");
}

//needs free
char *getArgument(char *str) {
    assert(str != NULL);
    strtok(strdup(str), "=+-*");
    return strtok(NULL, "\0");
}

//needs free
char *getBool(char *str) {
    assert(str != NULL);
    strtok(strdup(str), "(");
    return strtok(NULL, ")");
}

