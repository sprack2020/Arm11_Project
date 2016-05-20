//
// Created by drspaceship on 20/05/16.
//

#include <stdint.h>
#include <stdlib.h>
#include "decodeAndExecute.h"


#define MEM_SIZE 65536
#define NUM_REGISTERS 17

#define INSTR_LENGTH 4

#define MEM state.memory
#define REGFILE state.registers
#define PC state.registers[15]


typedef struct ARMstate {
    uint8_t *memory;
    uint32_t *registers;
} ARMstate;

extern ARMstate state;

