#include "emulate.h"

// prototypes
static void printUsageMsg(void);
static uint32_t getNextInstr(void);
static void initialiseARMstate(void);
static void deallocARMState(void);

int main(int argc, char **argv) {
    // allocate and zero out memory and registers
    initialiseARMstate();

    // ensure correct number of args
    if (argc != 2) {
        printUsageMsg();
        return EXIT_FAILURE;
    }

    // open inary file
    FILE *instrFile = fopen(argv[1], "r");
    if (instrFile == NULL) {
        printUsageMsg();
        return EXIT_FAILURE;
    }

    // load instructions into memory
    size_t numRead = fread(MEM, MEM_WORD_SIZE, MEM_SIZE, instrFile);
    if (numRead == 0) {
        fputs("Error: Could not read binary file", stderr);
        printUsageMsg();
        return EXIT_FAILURE;
    }

    if (!feof(instrFile)) {
        fputs("Error: Ran out of memory to hold instructions.", stderr);
        return EXIT_FAILURE;
    }

    // close the binary file
    if (fclose(instrFile)) {
        fputs("Warning: failed to close binary file.", stderr);
    }

    // initialise fetched and current instruction
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

static void printUsageMsg(void) {
    fputs("Usage: ./emulate <binary file>", stderr);
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
    state.onPins = 0;
}
