//
// Created by drspaceship on 13/06/16.
//

#ifndef ARM11_39_COMPILER_H
#define ARM11_39_COMPILER_H


#include <compiler/compilerStruct.h>
#include <assembler/io.h>
#include <assembler/tokenizer.h>
#include <compiler/compilerFunctionTable.h>
#include <compiler/expressionHandlers.h>

#define MAX_LINES 512
#define MAX_LINE_SIZE 256

#define GPIO_STATE "GPIO_STATE"
#define GPIO_RESERVED "GPIO_PTR"
#define GPIO_PTR "GPIO_PTR"

#define SHIFT_CLEAR 28
#define SHIFT_WRITE 40


void *init_compiler(
        Compiler_t *this,
        char *sourcePath,
        char *assembledPath
);

void compile(
        Compiler_t *this
);

void *deinit_compiler(
        Compiler_t *this
);

void parseInstructions(
        Compiler_t *this,
        int whileID,
        int ifID
);


#endif //ARM11_39_COMPILER_H
