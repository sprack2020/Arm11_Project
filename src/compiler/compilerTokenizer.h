//
// Created by drspaceship on 14/06/16.
//

#ifndef ARM11_39_COMPILERTOKENIZER_H
#define ARM11_39_COMPILERTOKENIZER_H

#include <string.h>
#include <compiler/compilerStruct.h>

char *removeBrackets(char *str);
char *getFreeReg(int regNum, char *reg);
char getOpType(char *str);
char *getRd(char *str);
char *getArgument(char *str);

#endif //ARM11_39_COMPILERTOKENIZER_H
