#include "emulate.h"

// contains the state of the ARM system we are emulating
ARMstate state;

int main(int argc, char **argv) {
    // zero out memory and registers
    MEM = calloc(MEM_SIZE, sizeof(uint8_t));
    REGFILE = calloc(NUM_REGISTERS, sizeof(uint32_t));

    // ensure correct number of args
    if (argc != 2) {
        fprintf(stderr, "Usage: ./emulate <binary file>\n");
        return 2;
    }

    // open binary file
    FILE *instrFile = fopen(argv[1], "r");
    if (instrFile == NULL) {
        fprintf(stderr, "Failed to open given binary file.\n");
        return 2;
    }

    // load instructions into memory
    fread(MEM, MEM_SIZE, INSTR_LENGTH, instrFile);

    uint32_t currInstr;

    // loop until next instruction is 0 (halt instruction)
    do {
        // gets next instruction and increments PC
        currInstr = getNextInstr();

        // skip this instruction if condition says to
        if (checkCond(currInstr)) {
            continue;
        }

        decodeAndExecute(currInstr);
    } while (currInstr);

    // print the final system state
    printState();

    // free memory used
    deallocARMState();

    return EXIT_SUCCESS;
}

// Gets the next instruction from memory and increments PC
uint32_t getNextInstr(void) {
    uint32_t nextInstr = 0;

    // read the appropriate number of bytes from MEM[PC] onwards
    // to get the next instruction and do shifts to convert endianness
    uint32_t instrBytes[INSTR_LENGTH];
    for (int i = 0; i < INSTR_LENGTH; i++) {
        instrBytes[i] = MEM[PC + i];
        instrBytes[i] <<= i;

        nextInstr |= instrBytes[i];
    }

    PC += INSTR_LENGTH;

    return nextInstr;
}

// frees all the memory we used to store the system state
void deallocARMState(void) {
    free(MEM);
    free(REGFILE);
}
