//
// Created by drspaceship on 15/06/16.
//

#ifndef ARM11_39_INSTRUCTIONMAKER_H
#define ARM11_39_INSTRUCTIONMAKER_H

#include <stdio.h>
#include <compiler/compilerStruct.h>

void makeLdr(Compiler_t *this, int Rd, unsigned int expr);
void makeArithmeticWithExpr(Compiler_t *this, char *mnem, int Rd, int Rn, int expr);
void makeArithmetic(Compiler_t *this, char *mnem, int Rd, int Rn, int Rm);
void makeStr(Compiler_t *this, int Rd, int Rn, int shift);
void makeCmp(Compiler_t *this, int Rd);



#endif //ARM11_39_INSTRUCTIONMAKER_H
