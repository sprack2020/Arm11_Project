//
// Created by drspaceship on 20/05/16.
//
#include "branch.h"


// PRE: instr is a branch instruction
// behavior: adds the offset to PC
void branch(uint32_t instr) {
    // Here, offset is a signed integer, as we may increase or decrease PC with
    // the branch, but extractBits returns an unsigned int
    int32_t offset = (int32_t) extractBits(instr, OFFSET_SIZE - 1, 0);

    // I need to sign extend offset as well, are we building a shift function
    // capable of that?
    offset <<= 2;

    // does this work since PC is unsigned and offset is signed?
    PC += offset;
}
