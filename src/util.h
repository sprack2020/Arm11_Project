//
// Created by drspaceship on 22/05/16.
//
#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#define INTWIDTH 32

#ifndef ARM11_39_BINARYSHIFT_H
#define ARM11_39_BINARYSHIFT_H

#endif //ARM11_39_BINARYSHIFT_H

typedef enum {LSL, LSR, ASR, ROR} shiftType;

typedef struct {
  uint32_t result;
  bool carry;
} ShiftResult;

ShiftResult binaryShift(uint32_t shiftee, shiftType st, uint32_t amount);
uint32_t rightShiftCarry(uint32_t shiftee, uint32_t amount);

// unsigned -> signed cast of integers of same width is guarenteed not to
// change bit pattern but signed -> unsigned may
uint32_t extractBits(uint32_t binaryNumber, int j, int i);
uint32_t extractBit (uint32_t binaryNumber, int i);