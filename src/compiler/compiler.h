//
// Created by drspaceship on 13/06/16.
//

#ifndef ARM11_39_COMPILER_H
#define ARM11_39_COMPILER_H


#include <compiler/compilerStruct.h>
#include <assembler/io.h>
#include <assembler/tokenizer.h>

Compiler_t *init_compiler(
        Compiler_t *this,
        char *sourcePath,
        char *assembledPath
);

void compile(
        Compiler_t *this
);

Compiler_t *deinit_compiler(
        Compiler_t *this
);

#endif //ARM11_39_COMPILER_H
