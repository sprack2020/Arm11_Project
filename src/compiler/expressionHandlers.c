//
// Created by drspaceship on 14/06/16.
//

#include "expressionHandlers.h"

void variableHandler(Compiler_t *this, char *declaration) {
    declaration = skipSpace(declaration);
    char *varStringList = removeBrackets(declaration);
    char *varString;
    char reg[4];

    varString = strtok(varStringList, ",");
    ListMapAdd(this->variableTable, varString, getFreeReg(0, reg));

    int i = 1;
    while (varString = strtok(NULL, ",") != NULL) {
        ListMapAdd(this->variableTable, varString, getFreeReg(i, reg));
        i++;
    }
}
void assignmentHandler(Compiler_t *this, char *assignment) {

}
void ifHandler(Compiler_t *this, char *stmt) {

}
void whileHandler(Compiler_t *this, char *stmt) {

}