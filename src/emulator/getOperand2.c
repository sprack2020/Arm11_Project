#include "getOperand2.h"

// PRE: instr is a dataProcess or dataTransfer instruction
// immediate should be derived from the I bit
// POST: returns a 32 bit int for operand2 and a carry value
ShiftResult getOperand2(uint32_t instr, bool immediate) {
    ShiftResult operand2;

    if (immediate) {
        uint32_t rotAmount = extractBits(instr, ROT_UPPER, ROT_LOWER) << 1;
        uint32_t imVal = extractBits(instr, IMM_VAL_UPPER, IMM_VAL_LOWER);
        operand2 = binaryShift(imVal, ROR, rotAmount);
    }
    else {
        bool isRegShift = extractBit(instr, REG_SHIFT_BIT);
        shiftType st = (shiftType) extractBits(instr, SHIFT_TYPE_UPPER, SHIFT_TYPE_LOWER);
        uint32_t RmVal = REGFILE[extractBits(instr, Rm_UPPER , Rm_LOWER)];
        uint32_t shiftAmount;

        if (isRegShift) {
            //gets the bottom byte of the address specified by Rs
            uint32_t Rs = extractBits(instr, Rs_UPPER, Rs_LOWER);
            shiftAmount = extractBits(REGFILE[Rs], LSB_UPPER, LSB_LOWER);
        } else {
            shiftAmount = extractFragmentedBits(instr, CONST_UPPER, CONST_LOWER);
        }

        operand2 = binaryShift(RmVal, st, shiftAmount);
    }

    return operand2;
}
