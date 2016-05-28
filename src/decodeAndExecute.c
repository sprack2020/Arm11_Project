//
// Created by drspaceship on 20/05/16.
//

#include "decodeAndExecute.h"

// PRE: instr is not the halt instruction
// Behaviour: Decides which of the 4 instruction types instr is and passes it to its subsequent function
// i.e. branch(instr), dataTransfer(instr) etc.
bool decodeAndExecute(uint32_t instr) {

    bool isBranch = (bool) extractBit(instr, bit27);
    bool isDataTransfer = (bool) extractBit(instr, bit26);
    bool mulCheck = (bool) extractBit(instr, bit25);
    uint32_t pattern = extractBits(instr, PATTERN_UPPER, PATTERN_LOWER);

    if (isBranch) {
        // puts("Executing branch instruction\n");
        branch(instr);
        return true;
    }
    else if (isDataTransfer) {
        // puts("Executing data transfer instruction\n");
        dataTransfer(instr);
    }
    else if (mulCheck && pattern == MUL_PATTERN) {
        // puts("Executing multiplier instruction\n");
        iMultiply(instr);
    }
    else {
        // puts("Executing data process instruction\n");
        dataProcess(instr);
    }
        return false;
}
