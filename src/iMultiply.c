//
// Created by drspaceship on 22/05/16.
//
#include "iMultiply.h"

// PRE: instr is a multiply instruction and in big endian
// behavior: multiplication instruction as in spec

void iMultiply(uint32_t instr) {

    uint32_t Rd = extractBits(instr, Rd_MUL_UPPER, Rd_MUL_LOWER);
    uint32_t RnVal = REGFILE[extractBits(instr, Rn_MUL_UPPER, Rn_MUL_LOWER)];
    uint32_t RsVal = REGFILE[extractBits(instr, Rs_UPPER, Rs_LOWER)];
    uint32_t RmVal = REGFILE[extractBits(instr, Rm_UPPER, Rm_LOWER)];
    bool Abit = extractBit(instr, A_BIT);
    bool Sbit = extractBit(instr, S_BIT);
    uint32_t acc = 0;
    uint32_t result;

    if (Abit) {
        acc = RnVal;
    }
    result = RmVal * RsVal + acc;


    if (Sbit) {
        //Nbit = bit 31 of result
        updateCPSR(extractBit(result, Nbit), Nbit);
        updateCPSR(result != 0, Zbit);
    }

    REGFILE[Rd] = result;
}