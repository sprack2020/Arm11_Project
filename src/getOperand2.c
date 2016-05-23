//
// Created by drspaceship on 23/05/16.
//
#include "getOperand2.h"
#include "emulate.h"


// PRE: instr is a dataProcess or dataTransfer instruction
// immediate should be derived from the I bit
// setCPSR should be the S bit for dataProcess or false for dataTransfer
// POST: returns a 32 bit int for operand2 as described in spec

uint32_t getOperand2(uint32_t instr, bool immediate, bool setCPSR) {

    uint32_t operand2;

    if (immediate) {
        uint32_t rotAmount = extractBits(instr, 11, 8) * 2;
        uint32_t imVal = extractBits(instr, 7, 0);
        operand2 = binaryShift(imVal, ROR, rotAmount).result;
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
        ShiftResult sr = binaryShift(RmVal, st, shiftAmount);
        operand2 = sr.result;
        if (setCPSR) {
            updateCPSR(sr.carry, Cbit);
        }
    }

    return operand2;
}