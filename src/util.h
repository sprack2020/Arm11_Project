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
#define A_BIT 21
#define S_BIT 20
#define MSB 31
#define BYTE_1_UPPER 7
#define LSB 0
#define IMM_BIT 25
#define PREPOST_BIT 24
#define UP_BIT 23
#define LOAD_BIT 20
#define Rn_UPPER 19
#define Rn_LOWER 16
#define Rd_UPPER 15
#define Rd_LOWER 12
#define Rs_UPPER 11
#define Rs_LOWER 8
#define Rm_UPPER 3
#define Rm_LOWER 0
#define ROT_UPPER 11
#define ROT_LOWER 8
#define CONST_UPPER 11
#define CONST_LOWER 7
#define IMM_VAL_UPPER 7
#define SHIFT_TYPE_UPPER 6
#define SHIFT_TYPE_LOWER 5
#define REG_SHIFT_BIT 4
#define OFFSET_UPPER 11
#define OFFSET_LOWER 0
#define OPCODE_UPPER 24
#define OPCODE_LOWER 21
#define bit27 27
#define bit26 26

typedef enum {LSL = 00, LSR = 01, ASR = 10, ROR = 11} shiftType;

typedef struct {
  uint32_t result;
  bool carry;
} ShiftResult;

ShiftResult binaryShift(uint32_t shiftee, shiftType st, uint32_t amount);
uint32_t rightShiftCarry(uint32_t shiftee, uint32_t amount);
uint32_t createMask(unsigned int i, unsigned int j);

// unsigned -> signed cast of integers of same width is guarenteed not to
// change bit pattern but signed -> unsigned may
uint32_t extractBits(uint32_t binaryNumber, int j, int i);
uint32_t extractBit (uint32_t binaryNumber, int i);
void read32Bits(uint32_t *dest, uint8_t *src);

#endif //ARM11_39_BINARYSHIFT_H
