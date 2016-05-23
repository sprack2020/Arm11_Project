//
// Created by drspaceship on 20/05/16.
//

#include <stdint.h>
#include <stdlib.h>

#include "checkCond.h"
#include "decodeAndExecute.h"
#include "printState.h"

#define MEM_SIZE 65536
#define NUM_REGISTERS 17

#define INSTR_LENGTH 4

#define MEM state.memory
#define REGFILE state.registers
#define PC state.registers[15]
#define CPSR state.registers[16]
#define Nbit 31
#define Zbit 30
#define Cbit 29
#define Vbit 28

typedef struct ARMstate {
    uint8_t *memory;
    uint32_t *registers;
} ARMstate;

extern ARMstate state;

uint32_t getNextInstr(void);
