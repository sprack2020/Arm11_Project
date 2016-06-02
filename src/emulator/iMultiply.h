#ifndef ARM11_39_IMULTIPLY_H
#define ARM11_39_IMULTIPLY_H


#include <stdint.h>
#include <emulator/checkCond.h>
#include <emulator/updateCPSR.h>
#include <emulate.h>

// Rn and Rd are swapped in multiply instruction
#define Rn_MUL_UPPER 23
#define Rn_MUL_LOWER 20
#define Rd_MUL_UPPER 11
#define Rd_MUL_LOWER 8

void iMultiply(uint32_t instr);


#endif //ARM11_39_IMULTIPLY_H
