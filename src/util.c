//
// Created by drspaceship on 22/05/16.
//

#include "util.h"
#include <stdlib.h>

#define INTWIDTH 32

// POST: returns a 32bit int shifted based on shiftType
ShiftResult binaryShift(uint32_t shiftee, enum shiftType st, uint32_t amount) {
    ShiftResult* sr;
    sr = (ShiftResult*) malloc(sizeof(ShiftResult));

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

    return *sr;
}

//gets the carry for any right shift by shifting it by one less, making the
//first bit the carry we require.
uint32_t rightShiftCarry(uint32_t shiftee, uint32_t amount) {
    return (shiftee >> (amount - 1)) & 1;
}
