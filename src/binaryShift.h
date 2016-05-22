//
// Created by drspaceship on 22/05/16.
//
#include <stdint.h>

#ifndef ARM11_39_BINARYSHIFT_H
#define ARM11_39_BINARYSHIFT_H

#endif //ARM11_39_BINARYSHIFT_H

enum shiftType {LSL, LSR, ASR, ROR};

uint32_t binaryShift(uint32_t int32, enum shiftType st);