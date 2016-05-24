//
// Created by drspaceship on 20/05/16.
//
#include "dataTransfer.h"
#include "emulate.h"

// prototypes
uint32_t calculateOffset(uint32_t offsetBits);
void load(uint32_t Rn, uint32_t Rd);
void store(uint32_t Rn, uint32_t Rd);

// PRE: instr is a data transfer instruction
// behavior: Loads/stores access of memory as described in spec
void dataTransfer(uint32_t instr) {
    // get I, l, u, Rn, Rd, P, offset
    uint32_t isImmediateOffset = extractBit(instr, IMM_BIT);
    uint32_t isPreIndex = extractBit(instr, PREPOST_BIT);
    uint32_t isUp = extractBit(instr, UP_BIT);
    uint32_t isLoad = extractBit(instr, LOAD_BIT);
    uint32_t Rn = extractBits(instr, Rn_UPPER, Rn_LOWER);
    uint32_t Rd = extractBits(instr, Rd_UPPER, Rd_LOWER);
    uint32_t offset = calculateOffset(instr);

    // perform data transfer
    if (isLoad) {
        load(Rn, Rd);
    } else {
        store(Rn, Rd);
    }

    // If instruction is post index, add / subtract the offset to base register
    if (!isPreIndex) {
        if (isUp) {
            Rn += offset;
        } else {
            Rn -= offset;
        }
    }

    // free?
}

// calculates and returns the offset to add to the base register
uint32_t calculateOffset(uint32_t instr) {
    // handling offset bits is equivalent to getting second operand in
    // data process, but with the immediate offset flag negated
    return getOperand2(instr, ! (bool) isImmediateOffset);
}

// Loads the data from MEM[Rn] into Rd
// TODO: fix / finish
void load(uint32_t Rn, uint32_t Rd) {
    // will store consecutive bytes from memory into this array
    const int n = REG_LENGTH / MEM_LENGTH;
    uint32_t toLoad[n];

    // clear Rd
    REGFILE[Rd] = 0;

    for (int i = 0; i < n; i++) {
        toLoad[i] = MEM[Rn + i];
        toLoad[i] <<= (n - i - 1)
    }

    REGFILE[Rd] = MEM[Rn];
}
