#include "genInstr.h"

//generate a data processing instruction with S set to 0 and a condition of
//always. Assumes all field inputs are of appropriate length
uint32_t genDP(bool immediate, int opcode, bool setCPSR, int rn, int rd,
               int operand2) {
    return DPMASK                   |
           immediate << ISHIFT      |
           opcode    << OPCODESHIFT |
           setCPSR   << SSHIFT      |
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
    char* dpMnems[NUMDPINSTRS] = {"and", "eor", "sub", "rsb", "add", "tst",
                                  "teq", "cmp", "orr", "mov"};
    DPOpcodes opcodes[NUMDPINSTRS] = {AND, EOR, SUB, RSB, ADD, TST, TEQ, CMP,
                                      ORR, MOV};

    for (int i = 0; i < NUMDPINSTRS; ++i) {
        if (equalStrings(dpMnems[i], mnem)) {
            return opcodes[i];
        }
    }
    //if we reached here, we did not match any mnemonic
    fprintf(stderr, "invalid DP mnemonic: %s mnem", mnem);
    exit(EXIT_FAILURE);
}
