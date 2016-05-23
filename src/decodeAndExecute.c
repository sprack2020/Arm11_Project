//
// Created by drspaceship on 20/05/16.
//

#include "decodeAndExecute.h"



// PRE: instr is not the halt instruction
// Behaviour: Decides which of the 4 instruction types instr is and passes it to its subsequent function
// i.e. branch(instr), dataTransfer(instr) etc.

void decodeAndExecute(uint32_t instr) {

    bool i27 = (bool) extractBit(instr, 27);
    bool i26 = (bool) extractBit(instr, 26);
    bool i25 = (bool) extractBit(instr, 25);
    uint32_t i7654 = extractBits(instr, 7, 4);

    if (i27) {
        branch(instr);
    }
    else if (i26) {
        dataTransfer(instr);
    }
    else if (!i25 && i7654 == 1001) {
        iMultiply(instr);
    }
    else {
        dataProcess(instr);
    }


}
