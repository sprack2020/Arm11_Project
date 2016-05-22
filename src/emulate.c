#include "emulate.h"

// contains the state of the ARM system we are emulating
ARMstate state;

int main(int argc, char **argv) {
    // zero out memory and registers
    MEM = calloc(MEM_SIZE, sizeof(uint8_t));
    REGFILE = calloc(NUM_REGISTERS, sizeof(uint32_t));

    // ensure correct number of args
    if (argc != 2) {
        fprintf(stderr, "Usage: ./emulate <binary file>");
        return 2;
    }

    // open binary file and load instructions into memory
    FILE *instrFile = fopen(argv[1], "r");
    fread(MEM, MEM_SIZE, INSTR_LENGTH, instrFile);

    // load first intruction
    uint32_t currInstr;

    do {
        currInstr = getNextInstr();

        if (checkCond(currInstr)) {
            continue;
        }

        decodeAndExecute(currInstr);
    } while (currInstr);

    printState();

    // free memory used
    free(MEM);
    free(REGFILE);

    return EXIT_SUCCESS;
}

// Once PC = all zeroes, we halt
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
