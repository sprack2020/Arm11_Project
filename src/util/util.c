#include "util.h"

// POST: returns a 32bit int shifted based on shiftType
ShiftResult binaryShift(uint32_t shiftee, shiftType st, uint32_t amount) {
    ShiftResult sr;

    //save some work and make edge cases easier.
    if (amount == 0) {
        sr.carry = 0;
        sr.result = shiftee;
        return sr;
    }

    //don't shift by more than bits than are in the shiftee
    if (amount > INTWIDTH) {
        return binaryShift(shiftee, st, amount % INTWIDTH);
    }

    switch(st) {
        case LSL:
            //gets the first bit of everything shifted off the left side
            sr.carry = (bool) (shiftee >> (INTWIDTH - amount));
            sr.result = shiftee << amount;
            break;

        case LSR:
            sr.carry = (bool) rightShiftCarry(shiftee, amount);
            sr.result = shiftee >> amount;
            break;

        case ASR:
            sr.carry = extractBit(shiftee, amount - 1);
            bool msb = extractBit(shiftee, INTWIDTH - 1);
            uint32_t resultTop = 0;
            if (msb) {
                resultTop = createMask(INTWIDTH - amount, INTWIDTH - 1);
            }
            sr.result = resultTop | shiftee >> amount;
            break;

        case ROR:
            sr.carry = (bool) rightShiftCarry(shiftee, amount);
            //least significant bits that rotate around
            sr.result = (shiftee << (INTWIDTH - amount)) |
            //everything else
                        (shiftee >> amount);
            break;

        default:
            fprintf(stderr, "Error in binaryShift(): "
                            "unrecognised shift type: %i\n", st);
            exit(2);
    }

    return sr;
}

//gets the carry for any right shift by shifting it by one less, making the
//first bit the carry we require.
uint32_t rightShiftCarry(uint32_t shiftee, uint32_t amount) {
    return (shiftee >> (amount - 1)) & 1;
}

// creates a bit mask to extract the bits i to j by &&-ing with this mask
uint32_t createMask(unsigned int lower, unsigned int upper) {
    uint32_t mask = 0;

    for (unsigned int m = lower; m <= upper; m++) {
        mask |= 1 << m;
    }

    return mask;
}

// Returns the bits at positions UB to LB from the given number.
// unsigned -> signed cast of same width integers is guarenteed not to
// change bit pattern but signed -> unsigned may
uint32_t extractBits(uint32_t binaryNumber, int UB, int LB) {
    // ensure UB >= LB and both LB and UB are positive and both less than the number
    // of bits in the binaryNumber
    const int numBits = sizeof(binaryNumber) * CHAR_BIT - 1;
    if (UB < LB || LB < 0 || UB > numBits) {
        fprintf(stderr, "Error in util: extractBits(): "
                "invalid indexes from which to extract bits. You attempted "
                "extractBits(0x%08x, %d, %d)\n", binaryNumber, UB, LB);
        exit(2);
    }

    uint32_t mask = createMask(LB, UB);
    binaryNumber &= mask;
    binaryNumber >>= LB;

    return binaryNumber;
}

bool extractBit(uint32_t binaryNumber, int i) {
    return (bool) ((binaryNumber & (1 << i )) >> i);
}

// dest: pointer to a 32bit to put the result into
// src:  pointer to a memory address (element of 8 bit array)
// post: Will read four consecutive 8 bit elements from memory starting from
//       address src.
void read32Bits(uint32_t *dest, uint8_t *src) {
    // get number of memory addresses we will have to read to accumulate
    // 32 bits
    const int n = INTWIDTH / CHAR_BIT;

    // declare array of the bytes we will read and zero out the destination
    uint32_t bytesToRead[n];
    *dest = 0;

    for (int i = 0; i < n; i++) {
        bytesToRead[i] = (uint32_t) *(src + i);
        bytesToRead[i] = binaryShift(bytesToRead[i], LSL, (n - i - 1) * CHAR_BIT).result;

        *dest |= bytesToRead[i];
    }
}

// swaps the endianness of an instr
void swapEndianness(uint32_t *number) {
    uint32_t n = *number;
    *number = (n & 0xFF << 0) << 24 |
              (n & 0xFF << 8) << 8  |
              (n & 0xFF << 16) >> 8 |
              (n & 0xFF << 24) >> 24;
}

// Swaps the endianness of instr, converts the indexes and then extracts
// the bits in between those indexes
// PRE: upperBit should be less than lowerBit because the endianness of instrBytes
//      will be swapped.
uint32_t extractFragmentedBits(uint32_t instr, int upperBit, int lowerBit) {
    if (lowerBit < 0 || upperBit > INTWIDTH - 1 || lowerBit < upperBit) {
        fprintf(stderr, "Error in extractFragmentedBits: "
                        "Invalid indexes from which to extract bits. You"
                        " attempted extractFragmentedBits(%d, %d, %d)",
                        instr, upperBit, lowerBit);
        exit(2);
    }

    swapEndianness(&instr);

    upperBit = SWAP_INDEX_ENDIANNESS(upperBit);
    lowerBit = SWAP_INDEX_ENDIANNESS(lowerBit);

    return extractBits(instr, upperBit, lowerBit);
}

// sign extend an n-bit number.
void signExtend(int32_t *num, int n) {
    if (n > INTWIDTH) {
        fprintf(stderr, "Error in util: Attempting to sign extend a %d bit"
                "number to %d bits", n, INTWIDTH);
    }

    const int numPaddingBits = INTWIDTH - n;

    *num <<= numPaddingBits;
    *num = binaryShift(*num, ASR, numPaddingBits).result;
}

shiftType strToShiftType(char* string) {
    if (strcmp(string, "lsl")) {
        return LSL;
    } else if (strcmp(string, "lsr")) {
        return LSR;
    } else if (strcmp(string, "asr")) {
        return ASR;
    } else if (strcmp(string, "ror")) {
        return ROR;
    } else {
        fprintf(stderr, "invalid shift type");
        exit(EXIT_FAILURE);
    }
}

bool strEq(void *str1, void *str2) {
    return strcmp((char *)str1, (char *)str2) == 0;
}


