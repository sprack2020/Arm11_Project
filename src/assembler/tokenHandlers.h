//
// Created by drspaceship on 31/05/16.
//

#ifndef ARM11_39_TOKENHANDLERS_H
#define ARM11_39_TOKENHANDLERS_H

#include <stdint.h>
#include <ctype.h>

#include "assembler.h"
#include <util/util.h>
#include <assembler/genInstr.h>
#include <assembler/tokenHandlerUtil.h>

#define NUMCONDCODES 7
#define MAX_MOV_CONSTANT 0XFF

uint32_t handleDataProcessing(Assembler *assembler, char **tokens);
uint32_t handleMultiply(Assembler *assembler, char **tokens);
uint32_t handleSDT(Assembler *assembler, char **tokens);
uint32_t handleBranch(Assembler *assembler, char **tokens);
uint32_t handleHalt(Assembler *assembler, char **tokens);
uint32_t handleLSL(Assembler *assembler, char **tokens);

#endif //ARM11_39_TOKENHANDLERS_H
