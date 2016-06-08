#include "updateCPSR.h"

void updateCPSR(bool bit, unsigned int bitnum) {
    if (bitnum > Nbit || bitnum < Vbit) {
        fprintf(stderr, "%s. bitnum = %d",
                "updateCPSR bitnum value is not in range", bitnum);
        exit(2);
    }

    CPSR = updateBit(CPSR, bitnum, bit);
}
