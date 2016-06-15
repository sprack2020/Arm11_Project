//
// Created by drspaceship on 14/06/16.
//

#include "expressionHandlers.h"

//[v1,v2..vn]
void variableHandler(Compiler_t *this, char *declaration) {
    char *varStringList = removeBrackets(declaration);
    char *varString;
    //max size reg string is "rx\0"
    char reg[3];

    varString = strtok(varStringList, ",");
    ListMapAdd(this->variableTable, varString, getFreeReg(0, reg));

    int i = 1;
    while ((varString = strtok(NULL, ",")) != NULL) {
        ListMapAdd(this->variableTable, varString, getFreeReg(i, reg));
        i++;
    }
}

//<I =n> or
//<I 'op'n> where op is +,-,*  or
//<I =Pn>
//<Continue>
void assignmentHandler(Compiler_t *this, char *assignment) {
    char *assign = removeBrackets(assignment);
}
void ifHandler(Compiler_t *this, char *stmt) {

}
void whileHandler(Compiler_t *this, char *stmt) {

}