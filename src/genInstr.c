#include <stdbool.h>

typedef enum {
    AND = 0,
    EOR = 1,
    SUB = 2,
    RSB = 3,
    ADD = 4,
    TST = 8,
    TEQ = 9,
    CMP = 10,
    ORR = 12,
    MOV = 13
} DPOpcodes;

typedef enum {
    EQ = 0,
    NE = 1,
    GE = 10,
    LT = 11,
    GT = 12,
    LE = 13,
    AL = 14
} CondCodes;

//bit positioning constants
#define CONDSHIFT 27
#define ISHIFT 25
#define PSHIFT 24
#define USHIFT 23
#define OPCODESHIFT 21
#define LSHIFT 20
#define ASHIFT 20
#define SSHIFT 19
#define RNSHIFT 15
#define RDSHIFT 11
#define RSSHIFT 7
#define RMSHIFT 0
#define OP2SHIFT 0
#define OFFSETSHIFT 0

//non-input bit masks (bits that are always have the same value)
//for various instructions
#define DPMASK AL << CONDSHIFT
#define MULMASK AL << CONDSHIFT | 0x9 << 4
#define SDTMASK AL << CONDSHIFT | 0x1 << 26

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

uint32_t genSDT(bool immediate, bool preIndexing, bool up, bool load, int rn,
                int rd, int offset) {
    return SDTMASK                   |
           immediate   << ISHIFT     |
           preIndexing << PSHIFT     |
           up          << USHIFT     |
           load        << LSHIFT     |
           rn          << RNSHIFT    |
           rd          << RDSHIFT    |
           offset      << OFFSETSHIFT;
}


