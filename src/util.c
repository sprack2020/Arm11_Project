//
// Created by drspaceship on 22/05/16.
//
#include "util.h"



// POST: returns a 32bit int shifted based on shiftType
ShiftResult binaryShift(uint32_t shiftee, shiftType st, uint32_t amount) {
    ShiftResult* sr;
    sr = malloc(sizeof(ShiftResult));

    //save some work and make edge cases easier.
    if (amount == 0) {
        sr->carry = 0;
        sr->result = shiftee;
    }

    //don't shift by more than bits than are in the shiftee
    if (amount > INTWIDTH) {
        return binaryShift(shiftee, st, amount % INTWIDTH);
    }

    switch(st) {
        case LSL:
            //gets the first bit of everything shifted off the left side
            sr->carry = (shiftee >> (INTWIDTH - amount)) & 1;
            sr->result = shiftee << amount;
        case LSR:
            sr->carry = rightShiftCarry(shiftee, amount);
            sr->result = shiftee >> amount;
        case ASR:
            sr->carry = rightShiftCarry(shiftee, amount);

            //start with only most significant bit, and repeat it to the left
            uint32_t signBit = shiftee & (1 << (amount - 1));
            for (int i = 0; i < amount; ++i) {
                signBit = signBit | signBit >> 1;
            }
            sr->result = (shiftee >> amount) | signBit;
        case ROR:
            sr->carry = rightShiftCarry(shiftee, amount);
            //least significant bits that rotate around
            sr->result = (shiftee << (INTWIDTH - amount)) |
            //everything else
                        (shiftee >> amount);
    }

    free(sr);
    return *sr;
}

//gets the carry for any right shift by shifting it by one less, making the
//first bit the carry we require.
uint32_t rightShiftCarry(uint32_t shiftee, uint32_t amount) {
    return (shiftee >> (amount - 1)) & 1;
}

// creates a bit mask to extract the bits i to j by &&-ing with this mask
uint32_t createMask(unsigned int i, unsigned int j) {
    uint32_t mask = 0;

    for (unsigned int m = i; m <= j; m++) {
        mask |= 1 << m;
    }

    return mask;
}

// Returns the bits at poisitions j to i from the given number
uint32_t extractBits(uint32_t binaryNumber, int j, int i) {
    // ensure j >= i and both i and j are positive and both less than the number
    // of bits in the binaryNumber
    const int numBits = sizeof(binaryNumber) * CHAR_BIT - 1;
    if (j < i || i < 0 || j > numBits) {
        fprintf(stderr, "Error in util: extractBits(): "
                "invalid indexes from which to extract bits. You attempted "
                "extractBits(0x%08x, %d, %d)\n", binaryNumber, j, i);
        exit(2);
    }

    uint32_t mask = createMask(i, j);
    binaryNumber &= mask;
    binaryNumber >>= i;

    return binaryNumber;
}
