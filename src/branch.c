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
    int32_t offset = (int32_t) extractBits(instr, OFFSET_SIZE - 1, 0);
    offset <<= SHIFT_TO_OFFSET;

    // add the offset
    int newPC = ((int32_t) PC) + offset;

    // check new value of PC is valid
    if (newPC < 0) {
        fprintf(stderr, "Error in branch instruction: attempted to add "
                "offset %d to PC = %d", offset, PC);
        exit(2);
    }

    PC = (uint32_t) newPC;
}
