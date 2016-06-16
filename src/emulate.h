#ifndef ARM11_39_EMULATE_H
#define ARM11_39_EMULATE_H

#define NDEBUG

#include <stdint.h>
#include <stdlib.h>

#include <emulator/checkCond.h>
#include <emulator/decodeAndExecute.h>
#include <emulator/printState.h>
#include <util/util.h>

// contains ARMState state, what we are emulating on
#include <emulator/global_state.h>

#define INSTR_LENGTH 4
#define MEM_WORD_SIZE 1

#define MEM state.memory
#define REGFILE state.registers
#define PC_INDEX 15
#define CPSR_INDEX 16
#define PC state.registers[PC_INDEX]
#define CPSR state.registers[CPSR_INDEX]

#define Nbit 31
#define Zbit 30
#define Cbit 29
#define Vbit 28

#endif
