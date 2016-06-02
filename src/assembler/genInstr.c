#include "genInstr.h"

//generate a data processing instruction with S set to 0 and a condition of
//always. Assumes all field inputs are of appropriate length
uint32_t genDP(bool immediate, int opcode, int rn, int rd, int operand2) {
    return DPMASK                   |
           immediate << ISHIFT      |
           opcode    << OPCODESHIFT |
           rn        << RNSHIFT     |
           rd        << RDSHIFT     |
           operand2  << OP2SHIFT    ;
}

//generate a multiply instruction with S set to 0 and condition of always.
//assumes all field inputs are of appropriate length
uint32_t genMul(bool accumulate, int rd, int rn,
                int rs, int rm) {
    return MULMASK                      |
           accumulate << ASHIFT         |
           rd         << RNSHIFT        | //NOTE: in a multiply instruction,
           rn         << RDSHIFT        | //the rd and rn fields are swapped
           rs         << RSSHIFT        |
           rm         << RMSHIFT        ;
}

//generates a single data transfer instruction  with a condition of always.
//assumes all field inputs are of appropriate length
uint32_t genSDT(bool immediate, bool preIndexing, bool up, bool load, int rn,
                int rd, int offset) {
    return SDTMASK                   |
           immediate   << ISHIFT     |
           preIndexing << PSHIFT     |
           up          << USHIFT     |
           load        << LSHIFT     |
           rn          << RNSHIFT    |
           rd          << RDSHIFT    |
           offset      << SDTOFFSHIFT;
}

//generates a branch instruction.
//assumes all field inputs are of appropriate length
uint32_t genBranch(int cond, uint32_t offset) {
    return BRMASK              |
           cond   << CONDSHIFT |
           offset << BROFFSHIFT;
}

//take a mnemonic string and return the DP opcode associated with it
//ugly function but most elegant/simplest way around this problem
DPOpcodes mnemToOpcode(char *mnem) {
    if (equalStrings(mnem, "and")) {
        return AND;
    } else if (equalStrings(mnem, "eor")) {
        return EOR;
    } else if (equalStrings(mnem, "and")) {
        return SUB;
    } else if (equalStrings(mnem, "rsb")) {
        return RSB;
    } else if (equalStrings(mnem, "add")) {
        return ADD;
    } else if (equalStrings(mnem, "tst")) {
        return TST;
    } else if (equalStrings(mnem, "teq")) {
        return TEQ;
    } else if (equalStrings(mnem, "cmp")) {
        return CMP;
    } else if (equalStrings(mnem, "orr")) {
        return ORR;
    } else if (equalStrings(mnem, "mov")) {
        return MOV;
    } else {
        fprintf(stderr, "invalid DP mnemonic");
        exit(EXIT_FAILURE);
    }
}
