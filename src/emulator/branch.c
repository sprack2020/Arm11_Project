#include "branch.h"

void clearBit(int32_t *num, int i);

// PRE: instr is a branch instruction
// behavior: adds the offset to PC
void branch(uint32_t instr) {
    // Here, offset is a signed integer, as we may increase or decrease PC with
    // the branch, but extractBits returns an unsigned int
    int32_t offset = extractFragmentedBits(instr, OFFSET_UPPER, OFFSET_LOWER);

    // shift left
    offset <<= SHIFT_TO_OFFSET;

    // truncate back to 24 bits
    clearBit(&offset, OFFSET_SIZE);
    clearBit(&offset, OFFSET_SIZE + 1);

    // sign extend offset
    signExtend(&offset, OFFSET_SIZE);

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

void clearBit(int32_t *num, int i) {
    *num &= ~(1 << i);
}
