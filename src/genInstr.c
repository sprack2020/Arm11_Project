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
#define ASHIFT 20
#define SSHIFT 19
#define RNSHIFT 15
#define RDSHIFT 11
#define RSSHIFT 7
#define RMSHIFT 0

//non-input bits mask for a multiply instruction
#define MULMASK AL << CONDSHIFT | 0x9 << 4

//generate a multiply instruction with S set to 0 and condition of always
//assumes register arguments are valid (between 0 and 15 inclusive)
uint32_t genMul(bool accumulate, long int rd, long int rn,
                long int rs, long int rm) {
    return MULMASK                      |
           accumulate << ASHIFT         |
           rd         << RNSHIFT        | //NOTE: in a multiply instruction,
           rn         << RDSHIFT        | //the rd and rn fields are swapped
           rs         << RSSHIFT        |
           rm         << RMSHIFT;

}


