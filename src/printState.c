//
// Created by drspaceship on 22/05/16.
//
#include "printState.h"
#include "emulate.h"

// gets the correct spacing to put before the ':'
// this is so all colons line up, thus they must appear as the fifth character
// of the line as CPSR is the longest register name and four letters long
void setCorrectSpacing(int reg, char *spacing) {
    if (reg <= LAST_SINGLE_DIGIT) {
        spacing = "  ";
    } else if (reg <= LAST_GENERAL_REGISTER) {
        spacing = " ";
    } else {
        fprintf(stderr, "Exception in printState: correctSpacing(): "
                "Attempting to print register that should not be printed: $%d",
                reg);
        exit(2);
    }
}

// PRE: last instruction was halt
// behavior: outputs the state of the registers
void printState(void) {
    // print registers
    printf("Registers:\n");

    char *correctSpacing = "";

    uint32_t reg;
    for (int i = 0; i <= LAST_GENERAL_REGISTER; i++) {
        reg = REGFILE[i];
        setCorrectSpacing(reg, correctSpacing);

        printf("$%d%s:          %d (0x%08x)\n", i, correctSpacing, reg, reg);
    }

    // print PC and CPSR
    printf("PC  :          %d (0x%08x)\n", PC, PC);
    printf("CPSR:          %d (0x%08x)\n", CPSR, CPSR);

    // print memory
    printf("Non-zero memory:\n");
    for (int i = 0; i < MEM_SIZE; i++) {
        if (MEM[i] != 0) {
            printf("0x%08x: 0x%08x\n", i, MEM[i]);
        }
    }
}
