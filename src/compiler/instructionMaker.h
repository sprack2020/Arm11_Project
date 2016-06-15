//
// Created by drspaceship on 15/06/16.
//

#ifndef ARM11_39_INSTRUCTIONMAKER_H
#define ARM11_39_INSTRUCTIONMAKER_H

#include <stdio.h>


void makeLdr(char *str, int Rd, int expr);
void makeArithmeticWithExpr(char *str, char *mnem, int Rd, int Rn, int expr);
void makeArithmetic(char *str, char *mnem, int Rd, int Rn, int Rm);
void makeStr(char *str, int Rd, int Rn, int shift);
void makeCmp(char *str, int Rd);



#endif //ARM11_39_INSTRUCTIONMAKER_H
