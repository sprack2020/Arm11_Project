//
// Created by drspaceship on 22/05/16.
//
#include "printState.h"
#include "emulate.h"

// PRE: last instruction was halt
// behavior: outputs the state of the registers
void printState(void) {
    // print registers
    printf("Registers:\n");

    for (int i = 0; i < NUM_REGISTERS; i++) {
        printf("Register[%d] = %d\n", i, REGFILE[i]);
    }

    printf("\n-------------\n");

    // print memory
    printf("Memory:\n");

    for (int i = 0; i < MEM_SIZE; i++) {
        printf("Memory[%d] = %d\n", i, MEM[i]);
    }
}
