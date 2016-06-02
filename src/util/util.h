#ifndef ARM11_39_BINARYSHIFT_H
#define ARM11_39_BINARYSHIFT_H

#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#define INTWIDTH 32

// keeping the instructions in little endian
#define MSB 7
#define A_BIT 13
#define S_BIT 12
#define LSB_UPPER 7
#define LSB_LOWER 0
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
#define OFFSET_UPPER 15
#define OFFSET_LOWER 24
#define OPCODE_UPPER 0
#define OPCODE_LOWER 13
#define bit27 3
#define bit26 2

#define SWAP_INDEX_ENDIANNESS(BIT) CHAR_BIT * (3 - (BIT) / CHAR_BIT) \
                                    + (BIT) % CHAR_BIT

typedef enum {LSL = 0, LSR = 1, ASR = 2, ROR = 3} shiftType;

typedef struct {
  uint32_t result;
  bool carry;
} ShiftResult;

ShiftResult binaryShift(uint32_t shiftee, shiftType st, uint32_t amount);
uint32_t rightShiftCarry(uint32_t shiftee, uint32_t amount);
uint32_t createMask(unsigned int lower, unsigned int upper);
uint32_t extractBits(uint32_t binaryNumber, int j, int LB);
bool extractBit (uint32_t binaryNumber, int i);
void read32Bits(uint32_t *dest, uint8_t *src);
uint32_t extractFragmentedBits(uint32_t instr, int upperBit, int lowerBit);
void swapEndianness(uint32_t *number);
void signExtend(int32_t *num, int n);
shiftType strToShiftType(char* string);
bool equalStrings(char *s1, char *s2);
bool strEq(void *str1, void *str2);

#endif //ARM11_39_BINARYSHIFT_H
