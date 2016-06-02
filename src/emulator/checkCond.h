#ifndef ARM11_39_CHECKCOND_H
#define ARM11_39_CHECKCOND_H

#include <stdint.h>
#include <stdbool.h>
#include <util/util.h>
#include <emulate.h>

#define cond3 7
#define cond1 5
#define cond0 4
#define eqORne 0
#define geORlt 5
#define gtORle 6
#define always 7


// Cond represented by 4 bits: c3210
typedef struct Cond {
    bool c0;
    uint8_t c321;
} Cond;

bool checkCond(uint32_t instr);

#endif //ARM11_39_CHECKCOND_H
