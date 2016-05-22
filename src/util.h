//
// Created by drspaceship on 22/05/16.
//
#include <stdint.h>
#include <stdbool.h>

#ifndef ARM11_39_BINARYSHIFT_H
#define ARM11_39_BINARYSHIFT_H

#endif //ARM11_39_BINARYSHIFT_H

enum shiftType {LSL, LSR, ASR, ROR};

typedef struct {
  uint32_t result;
  bool carry;
} ShiftResult;

ShiftResult binaryShift(uint32_t shiftee, enum shiftType st, uint32_t amount);
uint32_t rightShiftCarry(uint32_t shiftee, uint32_t amount);
uint32_t extractBits(uint32_t binaryNumber, int i, int j);
