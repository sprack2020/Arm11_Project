//
// Created by drspaceship on 20/05/16.
//

#include "decodeAndExecute.h"



// PRE: instr is not the halt instruction
// Behaviour: Decides which of the 4 instruction types instr is and passes it to its subsequent function
// i.e. branch(instr), dataTransfer(instr) etc.

void decodeAndExecute(uint32_t instr) {

    bool isBranch = (bool) extractBit(instr, bit27);
    bool isDataTransfer = (bool) extractBit(instr, bit26);
    bool b25 = (bool) extractBit(instr, 25);
    uint32_t bs7to4 = extractBits(instr, 7, 4);

    if (isBranch) {
        branch(instr);
    }
    else if (isDataTransfer) {
        dataTransfer(instr);
    }
    else if (b25 && bs7to4 == 1001) {
        iMultiply(instr);
    }
    else {
        dataProcess(instr);
    }


}
