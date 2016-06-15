//
// Created by drspaceship on 15/06/16.
//

#include "instructionMaker.h"

void makeLdr(char *str, int Rd, int expr) {
    sprintf(str, "ldr r%i, =%i", Rd, expr);
}
void makeArithmeticWithExpr(char *str, char *mnem, int Rd, int Rn, int expr) {
    sprintf(str, "%s r%i, r%i, #%i", mnem, Rd, Rn, expr);
}
void makeArithmetic(char *str, char *mnem, int Rd, int Rn, int Rm) {
    sprintf(str, "%s r%i, r%i, r%i", mnem, Rd, Rn, Rm);
}
void makeStr(char *str, int Rd, int Rn, int shift) {
    sprintf(str, "str r%i, [r%i, #%i]", Rd, Rn, shift);
}
void makeCmp(char *str, int Rd) {
    sprintf(str, "cmp r%i, #0", Rd);
}