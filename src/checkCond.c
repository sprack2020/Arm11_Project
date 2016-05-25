//
// Created by drspaceship on 22/05/16.
//

#include "checkCond.h"

// PRE: instr is not the halt instruction and in big endian
// behavior: infers the COND part of the instruction
// based on the value of COND it checks the NZCV flags from register 16 and returns a bool

bool checkCond(uint32_t instr) {

    bool N, Z, V;
    N = (bool) extractBit(CPSR, Nbit);
    Z = (bool) extractBit(CPSR, Zbit);
    V = (bool) extractBit(CPSR, Vbit);

    Cond cond;
    cond.c0 = (bool) extractBit(instr, cond0);
    cond.c321 = (uint8_t) extractBits(instr, cond3, cond1);

    switch (cond.c321) {
        case eqORne: return cond.c0 ^ Z;
        case geORlt: return cond.c0 ^ (N == V);
        case gtORle: return (cond.c0 == Z || N != V);
        case always: return true;
        default: return false;
    }

}
