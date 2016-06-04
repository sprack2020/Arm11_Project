#ifndef ARM11_GENINSTR_H
#define ARM11_GENINSTR_H

#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include <assembler/genInstr.h>
#include <util/util.h>


// bit positioning constants
#define CONDSHIFT 28
#define ISHIFT 25
#define PSHIFT 24
#define USHIFT 23
#define OPCODESHIFT 21
#define ASHIFT 21
#define LSHIFT 20
#define SSHIFT 20
#define RNSHIFT 16
#define RDSHIFT 12
#define RSSHIFT 8
#define RMSHIFT 0
#define OP2SHIFT 0
#define SDTOFFSHIFT 0
#define BROFFSHIFT 0

// non-input bit masks (bits that are always have the same value)
// for various instructions
#define DPMASK  AL << CONDSHIFT
#define MULMASK AL << CONDSHIFT | 0x9 << 4
#define SDTMASK AL << CONDSHIFT | 0x1 << 26
#define BRMASK 0xA << 24

uint32_t genDP(bool immediate, int opcode, bool setCPSR, int rn, int rd, int operand2);
uint32_t genMul(bool accumulate, int rd, int rn, int rs, int rm);
uint32_t genSDT(bool immediate, bool preIndexing, bool up, bool load, int rn,
                int rd, int offset);
uint32_t genBranch(int cond, uint32_t offset);
DPOpcodes mnemToOpcode(char *mnem);

#endif //ARM11_GENINSTR_H
