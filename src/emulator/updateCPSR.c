#include "updateCPSR.h"

void updateCPSR(bool bit, unsigned int bitnum) {
    if (bitnum > Nbit || bitnum < Vbit) {
        fprintf(stderr, "%s. bitnum = %d",
                "updateCPSR bitnum value is not in range", bitnum);
        exit(2);
    }

    uint32_t flagMask = binaryShift((uint32_t) bit, LSL, bitnum).result;
    uint32_t upperMask = 0;
    if (bitnum < Nbit) {
        upperMask = extractBits(CPSR, Nbit, bitnum + 1);
        upperMask = binaryShift(upperMask, LSL, bitnum).result;
    }
    CPSR = upperMask |
           extractBits(CPSR, bitnum - 1, 0) |
           flagMask;
}
