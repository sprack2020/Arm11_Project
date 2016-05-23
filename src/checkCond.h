//
// Created by drspaceship on 22/05/16.
//
#include <stdint.h>
#include <stdbool.h>
#include "util.h"


#ifndef ARM11_39_CHECKCOND_H
#define ARM11_39_CHECKCOND_H

#endif //ARM11_39_CHECKCOND_H

// Cond represented by 4 bits: c3210
typedef struct Cond {
    bool c0;
    uint8_t c321;
} Cond;

bool checkCond(uint32_t instr);