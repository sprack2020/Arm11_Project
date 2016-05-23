//
// Created by drspaceship on 22/05/16.
//

#include "checkCond.h"
#include "emulate.h"

// PRE: instr is not the halt instruction
// behavior: infers the COND part of the instruction
// based on the value of COND it checks the NZCV flags from register 16 and returns a bool

bool checkCond(uint32_t instr) {

    bool N, Z, V;
    N = (bool) extractBits(CPSR, 31, 31);
    Z = (bool) extractBits(CPSR, 30, 30);
    V = (bool) extractBits(CPSR, 28, 28);

    Cond cond;
    cond.c0 = (bool) extractBits(instr, 28, 28);
    cond.c321 = (uint8_t) extractBits(instr, 31, 29);

    switch (cond.c321) {
        case 0: return cond.c0 ^ Z;
        case 101: return cond.c0 ^ (N == V);
        case 110: return (cond.c0 == Z || N != V);
        case 111: return true;
        default: return false;
    }

}
