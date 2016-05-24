//
// Created by drspaceship on 20/05/16.
//
#ifndef ARM11_39_DATATRANSFER_H
#define ARM11_39_DATATRANSFER_H


#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include "getOperand2.h"
#include "util.h"

#define IMM_BIT 25
#define PREPOST_BIT 24
#define UP_BIT 23
#define LOAD_BIT 20
#define Rn_UPPER 19
#define Rn_LOWER 16
#define Rd_UPPER 15
#define Rd_LOWER 12
#define OFFSET_UPPER 11
#define OFFSET_LOWER 0

void dataTransfer(uint32_t instr);


#endif //ARM11_39_DATATRANSFER_H
