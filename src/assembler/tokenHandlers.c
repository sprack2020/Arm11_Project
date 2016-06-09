//
// Created by drspaceship on 31/05/16.
//

#include <string.h>
#include "tokenHandlers.h"

uint32_t handleDataProcessing(Assembler *assembler, char **tokens) {
    bool imm = false;
    int opcode = (int) mnemToOpcode(tokens[0]);

    if (hasNoRd(tokens[0])) {
        uint32_t operand2 = handleOperand2(&tokens[2], &imm);
        uint32_t Rn = getValue(tokens[1]);
        return genDP(imm, opcode, true, Rn, 0, operand2);
    } else if (hasNoRn(tokens[0])) {
        uint32_t operand2 = handleOperand2(&tokens[2], &imm);
        uint32_t Rd = getValue(tokens[1]);
        return genDP(imm, opcode, false, 0, Rd, operand2);
    } else {
        uint32_t operand2 = handleOperand2(&tokens[3], &imm);
        uint32_t Rd = getValue(tokens[1]);
        uint32_t Rn = getValue(tokens[2]);
        return genDP(imm, opcode, false, Rn, Rd, operand2);
    }
}

uint32_t handleMultiply(Assembler *assembler, char **tokens) {
    uint32_t Rd = getValue(tokens[1]);
    uint32_t Rm = getValue(tokens[2]);
    uint32_t Rs = getValue(tokens[3]);
    uint32_t Rn;
    if (equalStrings(tokens[0], "mla")) {
        Rn = getValue(tokens[4]);
        return genMul(true, Rd, Rn, Rs, Rm);
    } else {
        Rn = 0;
    }

    return genMul(false, Rd, 0, Rs, Rm);
}

uint32_t handleSDT(Assembler *assembler, char **tokens) {
    //set fields to default. Should these not be ints of fixed with and/or
    // unsigned ?
    bool load = equalStrings(tokens[0], "ldr");
    int Rd = getValue(tokens[1]);
    bool immediate = false;
    bool preIndexing = true;
    bool up = true;
    int Rn = 0xF;
    int offset = 0;

    if (tokens[2][0] == '=') {  //numeric constant
        immediate = false;
        uint32_t constant = getValue(tokens[2]);
        if (constant <= MAX_MOV_CONSTANT) {
            tokens[0] = "mov";
            tokens[2][0] = '#';
            return handleDataProcessing(assembler, tokens);
        } else {
            assembler->binaryProgram[(assembler->firstEmptyAddr) / INSTR_LENGTH]
                    = constant;
            offset = calcOffset(assembler,
                                (unsigned int) assembler->firstEmptyAddr, false);
            assembler->firstEmptyAddr += INSTR_LENGTH;
        }

    } else {
        preIndexing = (tokens[2][3] != ']' && tokens[2][4] != ']')
                        || tokens[3] == NULL;
        Rn = getValue(&tokens[2][1]);
        if (tokens[3] != NULL) {
            if (tokens[3][1] == '-') {
                up = false;

                //change negative at start of Rm to #
                tokens[3][1] = '#';

                //make token 3 start at last #
                tokens[3] = &tokens[3][1];
            }
            // offset is handled similarly to operand2, but with immediate
            // negated after
            offset = handleOperand2(&tokens[3], &immediate);
            immediate = !immediate;
        }
    }

    return genSDT(immediate, preIndexing, up, load, Rn, Rd, offset);
}

uint32_t handleBranch(Assembler *assembler, char **tokens) {
    CondCodes cond = mnemToCondCode(&tokens[0][1]);
    uint32_t address = isalpha(tokens[1][0]) ?
                       //address starts with a char so is a label
                       getLabelAddress(assembler, tokens[1]) :
                       //else it's a numeric value
                       getValue(tokens[1]);
    uint32_t offset = calcOffset(assembler, address, true);

    return genBranch(cond, offset);
}

uint32_t handleBranchIndirect(Assembler *assembler, char **tokens) {
    uint32_t rn = getValue(tokens[1]);
    return genBranchIndirect(AL, rn);
}

uint32_t handleHalt(Assembler *assembler, char **tokens) {
    return 0;
}

uint32_t handleLSL(Assembler *assembler, char **tokens) {
    //rearrange tokens and pass to DP handler.
    tokens[0] = "mov";
    tokens[4] = tokens[2];
    tokens[2] = tokens[1];
    tokens[3] = "lsl";

    return handleDataProcessing(assembler, tokens);
}


