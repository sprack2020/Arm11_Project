//
// Created by drspaceship on 22/05/16.
//
#include "iMultiply.h"
#include "emulate.h"

// PRE: instr is a multiply instruction
// behavior: multiplication instruction as in spec

void iMultiply(uint32_t instr) {
    if (checkCond(instr)) {
        uint32_t rd = extractBits(instr, 11, 8); uint32_t *rdp = &rd;
        uint32_t rn = extractBits(instr, 23, 20); uint32_t *rnp = &rn;
        uint32_t rs = extractBits(instr, 19, 16); uint32_t *rsp = &rs;
        uint32_t rm = extractBits(instr, 27, 24); uint32_t *rmp = &rm;
        if (extractBit(instr, 13) != 0) {
            *rdp = *rmp * *rsp + *rnp;
        }
        else {
            *rdp = *rmp * *rsp;
        }
        if (extractBit(instr, 12) != 0) {
            updateCPSR((bool)extractBit(rd, 31), Nbit);
            if (rd == 0) {
                updateCPSR(1, 6);
            } 
            else {
                updateCPSR(0, 6);
            }
        }
    }
}