//
// Created by drspaceship on 15/06/16.
//

#include "variable.h"

void init_variable(variable_t *this, int regNum) {
    this->regNum = regNum;
    this->isPin = false;
}
void deinit_variable(variable_t *this) {

}