//
// Created by drspaceship on 22/05/16.
//
#ifndef ARM11_39_DATAPROCESS_H
#define ARM11_39_DATAPROCESS_H


#include <stdint.h>
#include <stdbool.h>
#include "util.h"
#include "getOperand2.h"
#include "emulate.h"

#define Opcode_Start 24
#define Opcode_End 21
#define S_BIT 20



void dataProcess(uint32_t instr);



#endif //ARM11_39_DATAPROCESS_H

