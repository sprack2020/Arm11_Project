//
// Created by drspaceship on 23/05/16.
//
#include "getOperand2.h"
#include "util.h"

// PRE: instr is a dataProcess or dataTransfer instruction
// POST: returns a 32 bit int for operand2 as described in spec

uint32_t getOperand2(uint32_t instr, bool immediate) {

    uint32_t operand2;

    if (immediate) {
        uint32_t rotAmount = extractBits(instr, 11, 8) * 2;
        uint32_t imVal = extractBits(instr, 7, 0);
        operand2 = binaryShift(imVal, ROR, rotAmount).result;
    }
    else {
        
    }

    return operand2;
}