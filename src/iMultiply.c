//
// Created by drspaceship on 22/05/16.
//
#include "iMultiply.h"

// PRE: instr is a multiply instruction
// behavior: multiplication instruction as in spec

void iMultiply(uint32_t instr) {
    if (checkCond(instr)) {
        rd = extractBits(instr, 11, 8)
        rn = extractBits(instr, 23, 20)
        rs = extractBits(instr, 19, 16)
        rm = extractBits(instr, 27, 24)
        if (extractBits(instr, 13, 13) != 0) {
            //assuming extractBits returns a uint32_t
            //rd = rm*rs + rn
        }
        else {
            //rd = rm*rs
        }
        if (extractBits(instr, 12, 12) != 0) {
            //r16[31] = rd[31]
            //if (rd == 0) then r16[30] = 1 else r16[30] = 0;
        }
    }
}