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
bool hasNoRd(char* mnem);
bool hasNoRn(char *mnem);

uint32_t handleDataProcessing(Assembler assembler, char **tokens) {
    bool imm = false;
    int opcode = (int) mnemToOpcode(tokens[0]);
    if (hasNoRd(tokens[0])) {
        uint32_t operand2 = handleOperand2(&tokens[2], &imm);
        uint32_t rn = getValue(tokens[1]);
        return genDP(imm, opcode, rn, 0, operand2);
    } else if (hasNoRn(tokens[0])) {
        uint32_t operand2 = handleOperand2(&tokens[2], &imm);
        uint32_t rd = getValue(tokens[1]);
        return genDP(imm, opcode, 0, rd, operand2);
    } else {
        uint32_t operand2 = handleOperand2(&tokens[3], &imm);
        uint32_t rd = getValue(tokens[1]);
        uint32_t rn = getValue(tokens[2]);
        return genDP(imm, opcode, rn, rd, operand2);
    }
}

uint32_t handleMultiply(Assembler assembler, char **tokens) {
    uint32_t rd = getValue(tokens[1]);
    uint32_t rm = getValue(tokens[2]);
    uint32_t rs = getValue(tokens[3]);

    if (strcmp(tokens[0], "mla")) {
        uint32_t rn = getValue(tokens[4]);
        return genMul(true, rd, rn, rs, rm);
    } else {
        return genMul(false, rd, 0, rs, rm);
    }
}

uint32_t handleSDT(Assembler assembler, char **tokens) {
    return 0;
}

uint32_t handleBranch(Assembler assembler, char **tokens) {
    return 0;
}

uint32_t handleHalt(Assembler assembler, char **tokens) {
    return 0;
}

uint32_t handleLSL(Assembler assembler, char **tokens) {
    //rearrange tokens and pass to DP handler.
    tokens[0] = "mov";
    tokens[4] = tokens[2];
    strcpy(tokens[2], tokens[1]);
    tokens[3] = "lsl";

    return handleDataProcessing(assembler,tokens);
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
    } else {
        fprintf(stderr, "invalid operand 2");
        exit(EXIT_FAILURE);
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

bool hasNoRd(char *mnem) {
    return strcmp(mnem, "tst") == 0 ||
           strcmp(mnem, "teq") == 0 ||
           strcmp(mnem, "cmp") == 0;
}

bool hasNoRn(char *mnem) {
    return strcmp(mnem, "mov") == 0;
}

uint32_t calc
