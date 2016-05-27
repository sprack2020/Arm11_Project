//
// Created by drspaceship on 22/05/16.
//
#ifndef ARM11_39_BINARYSHIFT_H
#define ARM11_39_BINARYSHIFT_H


#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#define INTWIDTH 32
#define WORD_SIZE 1

// keeping the instructions in little endian
#define MSB 7
#define A_BIT 13
#define S_BIT 12
#define LSB_UPPER 31
#define LSB_LOWER 24
#define IMM_BIT 1
#define PREPOST_BIT 0
#define UP_BIT 15
#define LOAD_BIT 12
#define Rn_UPPER 11
#define Rn_LOWER 8
#define Rd_UPPER 23
#define Rd_LOWER 20
#define Rs_UPPER 19
#define Rs_LOWER 16
#define Rm_UPPER 27
#define Rm_LOWER 24
#define ROT_UPPER 19
#define ROT_LOWER 16
#define CONST_UPPER 19
#define CONST_LOWER 31
#define IMM_VAL_UPPER 31
#define IMM_VAL_LOWER 24
#define SHIFT_TYPE_UPPER 30
#define SHIFT_TYPE_LOWER 29
#define REG_SHIFT_BIT 28
#define OFFSET_UPPER 8    // for branch instr, don't know if these are right?
#define OFFSET_LOWER 31
#define OPCODE_UPPER 0
#define OPCODE_LOWER 13
#define bit27 3
#define bit26 2

#define SWAP_INDEX_ENDIANNESS(BIT) CHAR_BIT * (3 - (BIT) / CHAR_BIT) \
                                    + (BIT) % CHAR_BIT

typedef enum {LSL = 00, LSR = 01, ASR = 10, ROR = 11} shiftType;

typedef struct {
  uint32_t result;
  bool carry;
} ShiftResult;

ShiftResult binaryShift(uint32_t shiftee, shiftType st, uint32_t amount);
uint32_t rightShiftCarry(uint32_t shiftee, uint32_t amount);
uint32_t createMask(unsigned int i, unsigned int j);
uint32_t extractBits(uint32_t binaryNumber, int j, int i);
uint32_t extractBit (uint32_t binaryNumber, int i);
void read32Bits(uint32_t *dest, uint8_t *src);
uint32_t extractFragmentedBits(uint32_t instr, int upperBit, int lowerBit);
void signExtend(int32_t *i, int n);

#endif //ARM11_39_BINARYSHIFT_H
