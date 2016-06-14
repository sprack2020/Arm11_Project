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

char *getFreeReg(int regNum, char *reg) {
    assert(regNum < 8);
    sprintf(reg, "r%i", regNum);
    return reg;
}
