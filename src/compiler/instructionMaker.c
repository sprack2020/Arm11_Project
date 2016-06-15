//
// Created by drspaceship on 15/06/16.
//

#include "instructionMaker.h"


void makeLdr(Compiler_t *this, int Rd, unsigned int expr) {
    sprintf(this->assemblyProgram[this->instrAddr], "ldr r%i, =%i", Rd, expr);
    this->instrAddr++;
}
void makeArithmeticWithExpr(Compiler_t *this, char *mnem, int Rd, int Rn, int expr) {
    sprintf(this->assemblyProgram[this->instrAddr], "%s r%i, r%i, #%i", mnem, Rd, Rn, expr);
    this->instrAddr++;
}
void makeArithmetic(Compiler_t *this, char *mnem, int Rd, int Rn, int Rm) {
    sprintf(this->assemblyProgram[this->instrAddr], "%s r%i, r%i, r%i", mnem, Rd, Rn, Rm);
    this->instrAddr++;
}
void makeStr(Compiler_t *this, int Rd, int Rn, int shift) {
    sprintf(this->assemblyProgram[this->instrAddr], "str r%i, [r%i, #%i]", Rd, Rn, shift);
    this->instrAddr++;
}
void makeCmp(Compiler_t *this, int Rd) {
    sprintf(this->assemblyProgram[this->instrAddr], "cmp r%i, #0", Rd);
    this->instrAddr++;
}