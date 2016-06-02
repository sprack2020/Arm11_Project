//
// Created by drspaceship on 31/05/16.
//

#include <util/util.h>
#include "tokenHandlers.h"

static uint32_t getValue(char *expr);
static uint32_t handleOperand2(char **tokens, bool *imm);
static int getFirstOnePos(uint32_t num);
static bool isValidImmediate(
        uint32_t num,
        int firstOnePos,
        uint32_t *shiftAmount
);
static uint32_t calculateShiftAmount(int n);
static uint32_t generateShift(char **tokens);



uint32_t handleDataProcessing(Assembler assembler, char **tokens) {

}
uint32_t handleMultiply(Assembler assembler, char **tokens) {

}
uint32_t handleSDT(Assembler assembler, char **tokens) {

}
uint32_t handleBranch(Assembler assembler, char **tokens) {

}
uint32_t handleHalt(Assembler assembler, char **tokens) {

}
uint32_t handleLSL(Assembler assembler, char **tokens) {

}


static uint32_t getValue(char *expr) {

    long value;
    if (expr[0] == '#' || expr[0] == 'r') {
        value = strtol(&expr[1], NULL, 0);
        if (value >= (1 << 8)) {
            fprintf(stderr, "expr exceeds 8 bits");
            exit(EXIT_FAILURE);
        }
        return (uint32_t) value;
    }
    value = strtol(expr, NULL, 0);
    if (value >= (1 << 26)) {
        fprintf(stderr, "expr exceeds 26 bits");
        exit(EXIT_FAILURE);
    }
    return (uint32_t) value;
}

// PRE: tokens points to the first string argument of operand2
static uint32_t handleOperand2(char **tokens, bool *imm) {

    if (tokens[0][0] == '#') {
        *imm = true;
        uint32_t value = getValue(tokens[0]);
        if (value >= (1 << 8)) {
            int firstOnePos = getFirstOnePos(value);
            uint32_t shiftAmount;
            bool isValid = isValidImmediate(value, firstOnePos, &shiftAmount);
            if (!isValid) {
                fprintf(stderr, "cannot fit value into operand2");
                exit(EXIT_FAILURE);
            }
            return binaryShift(value, ROR, 32 - shiftAmount).result;
        }
        else {
            return value;
        }
    }
    else if (tokens[0][0] == 'r') {
        uint32_t Rm = getValue(tokens[0]);
        uint32_t shift = generateShift(&tokens[1]);
        return shift << 4 | Rm;
    }
}
// PRE: num is not 0
static int getFirstOnePos(uint32_t num) {
    for (int i = 31; i >= 0; --i) {
        if (extractBit(num, i)) {
            return i;
        }
    }
    // should never return -1
    return -1;
}

static bool isValidImmediate(uint32_t num, int firstOnePos, uint32_t *shiftAmount) {
    int zeroCount = 0;
    bool currBit;
    int currPos = firstOnePos;
    while (currPos != firstOnePos - 1) {
        currBit = extractBit(num, currPos);
        if (currBit) {
            zeroCount = 0;
        }
        else {
            zeroCount++;
        }

        if (zeroCount >= 24) {
            *shiftAmount = calculateShiftAmount(currPos + 1);
            return true;
        }

        currPos = (currPos + 1) % 32;
    }
    return false;
}

// 32 is the intwidth and 7 is the target position of the shift
static uint32_t calculateShiftAmount(int n) {
    return (uint32_t) (n + 32 - 7) % 32;
}

static uint32_t generateShift(char **tokens) {
    if (tokens[0] == NULL) {
        return 0;
    }
    shiftType shiftType = strToShiftType(tokens[0]);
    if (tokens[1][0] == '#') {
        uint32_t shiftAmount = getValue(tokens[1]);
        return shiftAmount << 3 | shiftType << 1;
    } else if (tokens[1][0] == 'r') {
        uint32_t shiftReg = getValue(tokens[1]);
        return shiftReg << 4 | shiftType << 1 | 1;
    } else {
        fprintf(stderr, "invalid shift argument");
        exit(EXIT_FAILURE);
    }
}
