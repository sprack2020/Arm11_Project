//
// Created by drspaceship on 31/05/16.
//

#include "tokenHandlers.h"

CondCodes mnemToCondCode(char *mnem);

uint32_t handleDataProcessing(Assembler *assembler, char **tokens) {
    bool imm = false;
    int opcode = (int) mnemToOpcode(tokens[0]);

    if (hasNoRd(tokens[0])) {
        uint32_t operand2 = handleOperand2(&tokens[2], &imm);
        uint32_t rn = getValue(tokens[1]);
        return genDP(imm, opcode, true, rn, 0, operand2);
    } else if (hasNoRn(tokens[0])) {
        uint32_t operand2 = handleOperand2(&tokens[2], &imm);
        uint32_t rd = getValue(tokens[1]);
        return genDP(imm, opcode, false, 0, rd, operand2);
    } else {
        uint32_t operand2 = handleOperand2(&tokens[3], &imm);
        uint32_t rd = getValue(tokens[1]);
        uint32_t rn = getValue(tokens[2]);
        return genDP(imm, opcode, false, rn, rd, operand2);
    }
}

uint32_t handleMultiply(Assembler *assembler, char **tokens) {
    uint32_t rd = getValue(tokens[1]);
    uint32_t rm = getValue(tokens[2]);
    uint32_t rs = getValue(tokens[3]);
    uint32_t rn;
    if (equalStrings(tokens[0], "mla")) {
        rn = getValue(tokens[4]);
        return genMul(true, rd, rn, rs, rm);
    } else {
        rn = 0;
    }

    return genMul(false, rd, 0, rs, rm);
}

uint32_t handleSDT(Assembler *assembler, char **tokens) {
    //set fields to default
    bool load = equalStrings(tokens[0], "ldr");
    int rd = getValue(tokens[1]);
    bool immediate = false;
    bool preIndexing = false;
    bool up = false;
    int rn = 0;
    int offset = 0;

    if (tokens[2][0] == '=') {  //numeric constant
        immediate = true;
        uint32_t constant = getValue(tokens[2]);
        if (constant <= 0xFF) {  //constant will fit in a mov instruction
            tokens[0] = "mov";
            tokens[2][0] = '#';
            return handleDataProcessing(assembler, tokens);
        } else {
            assembler->binaryProgram[(assembler->firstEmptyAddr) / INSTR_LENGTH]
                    = constant;
            offset = calcOffset(assembler,
                                (unsigned int) assembler->firstEmptyAddr);
            ++assembler->firstEmptyAddr;
        }

    } else {
        preIndexing = (tokens[2][3] != ']' && tokens[2][4] != ']')
                        || tokens[3] == NULL;
        rn = getValue(tokens[2]);
        up = true;
        if (tokens[3] != NULL) {
            if (tokens[3][0] == '-') {
                tokens[3] = &tokens[3][1]; //remove negative at start of Rm
            } else {
                up = true;
            };
            //offset is nearly identical to operand2, so use that function.
            offset = handleOperand2(&tokens[3], &immediate);
            immediate = !immediate; //immediate value is reversed for SDT.
        }
    }

    return genSDT(immediate, preIndexing, up, load, rn, rd, offset);
}

uint32_t handleBranch(Assembler *assembler, char **tokens) {
    CondCodes cond = mnemToCondCode(&tokens[0][1]);
    uint32_t address = isalpha(tokens[1][0]) ?
                       //address starts with a char so is a label
                       getLabelAddress(assembler, tokens[1]) :
                       //else it's a numeric value
                       getValue(tokens[1]);
    uint32_t offset = calcOffset(assembler, address);

    return genBranch(cond, offset);
}

uint32_t handleHalt(Assembler *assembler, char **tokens) {
    return 0;
}

uint32_t handleLSL(Assembler *assembler, char **tokens) {
    //rearrange tokens and pass to DP handler.
    tokens[0] = "mov";
    tokens[4] = tokens[2];
    strcpy(tokens[2], tokens[1]);
    tokens[3] = "lsl";

    return handleDataProcessing(assembler,tokens);
}


