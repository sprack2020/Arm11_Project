//
// Created by drspaceship on 22/05/16.
//

#include "dataProcess.h"

// PRE: instr is a data process instruction
// assume: PC does not feature in the instruction
// behavior: checks opcode and performs instruction, possibly writes result to register and updates flags

void dataProcess(uint32_t instr) {
    bool I = (bool) extractBit(instr, IMM_BIT);
    uint32_t opcode = extractBits(instr, Opcode_Start, Opcode_End);
    bool S = (bool) extractBit(instr, S_BIT);
    uint32_t RnVal = REGFILE[extractBits(instr, Rn_UPPER, Rn_LOWER)];
    uint32_t Rd = extractBits(instr, Rd_UPPER, Rd_LOWER);
    ShiftResult operand2WC = getOperand2(instr, I);
    uint32_t operand2 = operand2WC.result;
    bool C = operand2WC.carry;
    bool writeResult = true;
    uint32_t result = 0;

    switch (opcode) {
        case tst:
            writeResult = false;
        case and:
            result = RnVal & operand2;
            break;
        case teq:
            writeResult = false;
        case eor:
            result = RnVal ^ operand2;
            break;
        case cmp:
            writeResult = false;
        case sub:
            result = RnVal - operand2;
            C = RnVal >= operand2;
            break;
        case rsb:
            result = operand2 - RnVal;
            C = operand2 >= RnVal;
            break;
        case add:
            result = RnVal + operand2;
            C = extractBit(RnVal, MSB) && extractBit(operand2, MSB);
            break;
        case orr:
            result = RnVal | operand2;
            break;
        case mov:
            result = operand2;
    }


    if (S) {
        updateCPSR(C, Cbit);
        updateCPSR(!result, Zbit);
        updateCPSR((bool) extractBit(result, MSB), Nbit);
    }

    if (writeResult) {
        REGFILE[Rd] = result;
    }

}