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


#define and 0000
#define eor 0001
#define sub 0010
#define rsb 0011
#define add 0100
#define tst 1000
#define teq 1001
#define cmp 1010
#define orr 1100
#define mov 1101




void dataProcess(uint32_t instr);



#endif //ARM11_39_DATAPROCESS_H

