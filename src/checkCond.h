//
// Created by drspaceship on 22/05/16.
//
#ifndef ARM11_39_CHECKCOND_H
#define ARM11_39_CHECKCOND_H


#include <stdint.h>
#include <stdbool.h>
#include "util.h"
#include "emulate.h"

#define cond3 31
#define cond1 29
#define cond0 28
#define eqORne 000
#define geORlt 101
#define gtORle 110
#define always 111


// Cond represented by 4 bits: c3210
typedef struct Cond {
    bool c0;
    uint8_t c321;
} Cond;

bool checkCond(uint32_t instr);


#endif //ARM11_39_CHECKCOND_H
