//
// Created by drspaceship on 20/05/16.
//
#include "branch.h"
#include "emulate.h"

// PRE: instr is a branch instruction
// behavior: adds the offset to PC
void branch(uint32_t instr) {
    // Here, offset is a signed integer, as we may increase or decrease PC with
    // the branch, but extractBits returns an unsigned int
    int32_t offset = extractFragmentedBits(instr, OFFSET_UPPER, OFFSET_LOWER);

    // sign extend and shift offset
    signExtend(&offset, OFFSET_SIZE);
    offset <<= 2 ^ SHIFT_TO_OFFSET;

    // add the offset to PC
    int32_t newPC = ((int32_t) PC) + offset;

    // check new value of PC is valid
    if (newPC < 0) {
        fprintf(stderr, "Error in branch instruction: attempted to add "
                "offset %d to PC = %d", offset, PC);
        exit(2);
    }

    PC = (uint32_t) newPC;
}
