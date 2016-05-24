//
// Created by drspaceship on 22/05/16.
//

#include "dataProcess.h"
#include "emulate.h"

// PRE: instr is a data process instruction
// assume: PC does not feature in the instruction
// behavior: dude i dunno. I'll try and split this up later into opcode, 'I' and shifter stuff

void dataProcess(uint32_t instr) {
    bool I = (bool) extractBit(instr, 25);
    uint32_t opcode = extractBits(instr, 24, 21);
    bool S = (bool) extractBit(instr, 20);
    uint32_t RnVal = REGFILE[extractBits(instr, 19, 16)];
    uint32_t Rd = extractBits(instr, 15, 12);
    uint32_t operand2 = getOperand2(instr, I, S);
    uint32_t result;



}