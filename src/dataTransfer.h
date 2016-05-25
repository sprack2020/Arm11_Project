//
// Created by drspaceship on 20/05/16.
//
#ifndef ARM11_39_DATATRANSFER_H
#define ARM11_39_DATATRANSFER_H


#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include "emulate.h"
#include "getOperand2.h"
#include "util.h"



#define REG_LENGTH 32
#define MEM_LENGTH 8

void dataTransfer(uint32_t instr);
uint32_t calculateOffset(uint32_t offsetBits, bool isImmediateOffset);
void load(uint32_t Rn, uint32_t Rd);
void store(uint32_t Rn, uint32_t Rd);


#endif //ARM11_39_DATATRANSFER_H
