#ifndef ARM11_39_DATAPROCESS_H
#define ARM11_39_DATAPROCESS_H

#include <stdint.h>
#include <stdbool.h>
#include <util/util.h>
#include <emulator/getOperand2.h>
#include <emulate.h>

#define and 0x0
#define eor 0x1
#define sub 0x2
#define rsb 0x3
#define add 0x4
#define tst 0x8
#define teq 0x9
#define cmp 0xa
#define orr 0xc
#define mov 0xd

void dataProcess(uint32_t instr);

#endif //ARM11_39_DATAPROCESS_H
