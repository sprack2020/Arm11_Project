#include <util/util.h>
#include "tokenHandlerUtil.h"

// PRE: tokens points to the first string argument of operand2
uint32_t handleOperand2(char **tokens, bool *imm) {
    if (tokens[0][0] == '#') {
        *imm = true;
        uint32_t value = getValue(tokens[0]);
        if (value > MAX_MOV_CONSTANT) {
            int lastOnePos = getLastOnePos(value);
            //round lastOnePos down to the nearest multiple of 2.
            lastOnePos &= createMask(1, (sizeof(int) * 8 - 1));
            uint32_t shiftedValue = binaryShift(value, ROR, lastOnePos)
                    .result;
            if (shiftedValue > MAX_MOV_CONSTANT) {
                fprintf(stderr, "cannot fit value into operand2");
                exit(EXIT_FAILURE);
            }

            return ((INTWIDTH - lastOnePos) / 2) << 8 | shiftedValue;

        } else {
            return value;
        }

    } else if (tokens[0][0] == 'r') {
        uint32_t Rm = getValue(tokens[0]);
        uint32_t shift = generateShift(&tokens[1]);
        return shift << REG_FIELD_LENGTH | Rm;

    } else {
        fputs("Error in tokenHandlers: handleOperand2: invalid operand 2",
                stderr);
        exit(EXIT_FAILURE);
    }
}

// PRE: num is not 0
int getLastOnePos(uint32_t num) {
    assert(num != 0);

    for (int i = 0; i < INTWIDTH; ++i) {
        if (extractBit(num, i)) {
            return i;
        }
    }

    fprintf(stderr,
            "Error in tokenHandlers: getLastOnePos: Invalid num %u", num);
    exit(EXIT_FAILURE);
}

// given a first one position, calculates shift needed to move that into
//bit position 7
uint32_t calculateShiftAmount(int n) {
    return (uint32_t) (n + INTWIDTH - 8) % INTWIDTH;
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
        fputs("invalid shift argument", stderr);
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

uint32_t calcOffset(Assembler *assembler, uint32_t address, bool reduce) {
    uint32_t offset = address - (assembler->currInstrAddr + PIPELINE_LENGTH);
    if (!reduce) {
        return offset;
    }
    uint32_t reducedOffset = extractBits(offset, 24, 0) |
                           extractBit(offset, 31) << 25;
    return binaryShift(reducedOffset, LSR, 2).result;
}

uint32_t getLabelAddress(Assembler *assembler, char *label) {
    int *valPtr = (int *) ListMapGet(assembler->symbolTable,
                                    label, strcmpFromVoid);
    if (valPtr == NULL) {
        fprintf(stderr, "couldn't find label %s", label);
        exit(EXIT_FAILURE);
    }
    return (uint32_t) *valPtr;
}
