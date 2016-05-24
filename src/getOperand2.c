//
// Created by drspaceship on 23/05/16.
//
#include "getOperand2.h"
#include "emulate.h"


// PRE: instr is a dataProcess or dataTransfer instruction
// immediate should be derived from the I bit
// setCPSR should be the S bit for dataProcess or false for dataTransfer
// POST: returns a 32 bit int for operand2 as described in spec

ShiftResult getOperand2(uint32_t instr, bool immediate) {

    ShiftResult operand2;

    if (immediate) {
        uint32_t rotAmount = extractBits(instr, 11, 8) * 2;
        uint32_t imVal = extractBits(instr, 7, 0);
        operand2 = binaryShift(imVal, ROR, rotAmount);
    }
    else {
        bool isRegShift = (bool) extractBit(instr, 4);
        shiftType st = (shiftType) extractBits(instr, 6, 5);
        uint32_t RmVal = REGFILE[extractBits(instr, 3 ,0)];
        uint32_t shiftAmount;
        if (isRegShift) {
            uint32_t Rs = extractBits(instr, 11, 8);
            shiftAmount = extractBits(REGFILE[Rs], 7, 0);
            //gets the bottom byte of the address specified by Rs
        }
        else {
            shiftAmount = extractBits(instr, 11, 7);
        }
        operand2 = binaryShift(RmVal, st, shiftAmount);

    }

    return operand2;
}