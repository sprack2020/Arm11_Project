#include "emulate.h"

int main(int argc, char **argv) {
    // allocate and zero out memory and registers
    initialiseARMstate();

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
    fread(MEM, MEM_SIZE, MEM_WORD_SIZE, instrFile);

    if (!feof(instrFile)) {
        fprintf(stderr, "Error: Ran out of memory to hold instructions.\n");
        exit(2);
    }

    // close the binary file
    if (fclose(instrFile)) {
        printf("Warning: failed to close binary file.\n");
    }

    uint32_t fetchedInstr = getNextInstr();
    uint32_t currInstr = fetchedInstr;

    // loop until next instruction is 0 (halt instruction)
    while (currInstr) {
        // gets next instruction and increments PC
        currInstr = fetchedInstr;
        fetchedInstr = getNextInstr();

        // skip this instruction if condition says to
        if (!checkCond(currInstr)) {
            continue;
        }

        // decode and execute the instruction
        bool wasBranch = decodeAndExecute(currInstr);

        if (wasBranch) {
            fetchedInstr = getNextInstr();
        }
    }

    // print the final system state
    printState();

    // free memory used
    deallocARMState();

    return EXIT_SUCCESS;
}

// Gets the next instruction from memory and increments PC
uint32_t getNextInstr(void) {
    uint32_t nextInstr = 0;

    read32Bits(&nextInstr, &MEM[PC]);

    PC += INSTR_LENGTH;

    return nextInstr;
}

// frees all the memory we used to store the system state
void deallocARMState(void) {
    free(MEM);
    free(REGFILE);
}

// allocates and zeroes out the ARMstate
void initialiseARMstate(void) {
    MEM = calloc(MEM_SIZE, sizeof(uint8_t));
    REGFILE = calloc(NUM_REGISTERS, sizeof(uint32_t));
    state.controlBitsGPIO0To9 = 0;
    state.controlBitsGPIO10To19 = 0;
    state.controlBitsGPIO20To29 = 0;
    state.clearPins = 0;
    state.writePins = 0;
}
