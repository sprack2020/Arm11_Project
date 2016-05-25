//
// Created by drspaceship on 20/05/16.
//
#ifndef ARM11_39_EMULATE_H
#define ARM11_39_EMULATE_H


#include <stdint.h>
#include <stdlib.h>

#include "checkCond.h"
#include "decodeAndExecute.h"
#include "printState.h"
#include "util.h"

#define MEM_SIZE 65536
#define NUM_REGISTERS 17

#define INSTR_LENGTH 4
#define MEM_WORD_SIZE 1

#define MEM state.memory
#define REGFILE state.registers
#define PC state.registers[15]
#define CPSR state.registers[16]

#define Nbit 7
#define Zbit 6
#define Cbit 5
#define Vbit 4

typedef struct ARMstate {
    uint8_t *memory;
    uint32_t *registers;
} ARMstate;

extern ARMstate state;

// prototypes
uint32_t getNextInstr(void);
void initialiseARMstate(void);
void deallocARMState(void);


#endif
