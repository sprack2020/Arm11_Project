#include "tokenHandlerUtil.h"

// PRE: tokens points to the first string argument of operand2
uint32_t handleOperand2(char **tokens, bool *imm) {
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

        } else {
            return value;
        }
    } else if (tokens[0][0] == 'r') {
        uint32_t Rm = getValue(tokens[0]);
        uint32_t shift = generateShift(&tokens[1]);
        return shift << REG_FILED_LENGTH | Rm;

    } else {
        fprintf(stderr,
                "Error in tokenHandlers: handleOperand2: invalid operand 2");
        exit(EXIT_FAILURE);
    }
}

// PRE: num is not 0
int getFirstOnePos(uint32_t num) {
    for (int i = 31; i >= 0; --i) {
        if (extractBit(num, i)) {
            return i;
        }
    }

    // should never return -1
    fprintf(stderr,
            "Error in tokenHandlers:  getFirstOnePos: Invalid num %u", num);
    return -1;
}

bool isValidImmediate(uint32_t num, int firstOnePos, uint32_t *shiftAmount) {
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
uint32_t calculateShiftAmount(int n) {
    return (uint32_t) (n + 32 - 7) % 32;
}

uint32_t generateShift(char **tokens) {
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
    return equalStrings(mnem, "tst") ||
           equalStrings(mnem, "teq") ||
           equalStrings(mnem, "cmp");
}

bool hasNoRn(char *mnem) {
    return equalStrings(mnem, "mov");
}

uint32_t calcOffset(Assembler *assembler, uint32_t address) {
    return address - assembler->currInstrAddr - PIPELINE_LENGTH;
}

uint32_t getLabelAddress(Assembler *assembler, char *label) {
    uint32_t *valPtr = (uint32_t*) ListMapGet(assembler->symbolTable,
                                    label, strcmpFromVoid);
    if (valPtr == NULL) {
        fprintf(stderr, "couldn't find label %s", label);
        exit(EXIT_FAILURE);
    }
    return *valPtr;
}
