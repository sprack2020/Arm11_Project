//
// Created by drspaceship on 14/06/16.
//

#include <compiler/compilerStruct.h>

#ifndef ARM11_39_EXPRESSIONHANDLERS_H
#define ARM11_39_EXPRESSIONHANDLERS_H

#include <assembler/tokenizer.h>
#include <compiler/compilerTokenizer.h>
#include <compiler/instructionMaker.h>
#include <compiler/variableStruct.h>
#include <compiler/variable.h>
#include <compiler/compiler.h>

void variableHandler(Compiler_t *this, char *declaration);
void assignmentHandler(Compiler_t *this, char *assignment);
void ifHandler(Compiler_t *this, char *stmt, int whileID, int ifID);
void whileHandler(Compiler_t *this, char *stmt, int whileID, int ifID);

#endif //ARM11_39_EXPRESSIONHANDLERS_H
