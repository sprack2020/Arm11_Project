//
// Created by drspaceship on 20/05/16.
//
#include "dataTransfer.h"

// prototypes
uint32_t calculateOffset(uint32_t offsetBits, bool isImmediateOffset);
void load(uint32_t toLoadAddr, uint32_t Rd);
void store(uint32_t RnVal, uint32_t Rd);
bool checkValidAddress(uint32_t address);

// PRE: instr is a data transfer instruction
// behavior: Loads/stores access of memory as described in spec
void dataTransfer(uint32_t instr) {
    // get I, l, u, Rn, Rd, P, offset
    bool isImmediateOffset = extractBit(instr, IMM_BIT);
    uint32_t isPreIndex = extractBit(instr, PREPOST_BIT);
    uint32_t isUp = extractBit(instr, UP_BIT);
    uint32_t isLoad = extractBit(instr, LOAD_BIT);
    uint32_t Rn = extractBits(instr, Rn_UPPER, Rn_LOWER);
    uint32_t Rd = extractBits(instr, Rd_UPPER, Rd_LOWER);
    uint32_t offset = calculateOffset(instr, isImmediateOffset);

    // check valid registers used
    if (Rd == PC_INDEX) {
        fprintf(stderr, "Error in dataTransfer: Attempting to use PC as source"
            " / destination register\n");
        exit(2);
    }

    // apply offset to base register
    uint32_t adjustedRnVal = isUp ? REGFILE[Rn] + offset : REGFILE[Rn] - offset;
//    .. = REGFILE[Rn] (isUp ? + offset : REGFILE[Rn] - offset);

    if (isPreIndex) {
        if (isLoad) {
            load(adjustedRnVal, Rd);
        } else {
            store(adjustedRnVal, REGFILE[Rd]);
        }
    } else {
        if (isLoad) {
            load(REGFILE[Rn], Rd);
        } else {
            store(REGFILE[Rn], REGFILE[Rd]);
        }

        // adjust base register
        REGFILE[Rn] = adjustedRnVal;
    }
}

// calculates and returns the offset to add to the base register
uint32_t calculateOffset(uint32_t instr, bool isImmediateOffset) {
    // handling offset bits is equivalent to getting second operand in
    // data process, but with the immediate offset flag negated
    return getOperand2(instr, !isImmediateOffset).result;
}

// Loads the data from MEM[Rn] into Rd
void load(uint32_t toLoadAddr, uint32_t Rd) {
    if (!checkValidAddress(toLoadAddr)) {
        return;
    }

    read32Bits(REGFILE + Rd, MEM + toLoadAddr);
    swapEndianness(REGFILE + Rd);
}

// stores the data from Rn into memory starting at address Rd
void store(uint32_t RnVal, uint32_t toStore) {
    if (!checkValidAddress(RnVal)) {
        return;
    }

    const int n = REG_LENGTH / MEM_LENGTH;

    for (int i = n - 1; i >= 0; i--) {
        MEM[RnVal + i] = extractBits(toStore, (i + 1) * MEM_LENGTH - 1,
                i * MEM_LENGTH);
    }
}

bool checkValidAddress(uint32_t address) {
    bool isValid = true;

    if (address + (REG_LENGTH / MEM_LENGTH) - 1 > MEM_SIZE) {
        printf("Error: Out of bounds memory access at address 0x%08x\n", address);
        isValid = false;
    }

    return isValid;
}