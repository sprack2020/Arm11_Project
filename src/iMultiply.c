//
// Created by drspaceship on 22/05/16.
//
#include "iMultiply.h"

// PRE: instr is a multiply instruction
// behavior: multiplication instruction as in spec

void iMultiply(uint32_t instr) {
    if (checkCond(instr)) {
        uint32_t rd = extractBits(instr, 11, 8); uint32_t rdp = &rd;
        uint32_t rn = extractBits(instr, 23, 20); uint32_t rnp = &rn;
        uint32_t rs = extractBits(instr, 19, 16); uint32_t rsp = &rs;
        uint32_t rm = extractBits(instr, 27, 24); uint32_t rmp = &rm;
        if (extractBit(instr, 13) != 0) {
            *rdp = *rmp * *rsp + *rnp;
        }
        else {
            *rdp = *rmp * *rsp;
        }
        if (extractBit(instr, 12) != 0) {
            //NEED TO DISCUSS how updateCSPR works, other than that this is ready
            //r16[31] = rd[31]
            //if (rd == 0) then r16[30] = 1 else r16[30] = 0;
        }
    }
}