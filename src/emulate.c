#include "emulate.h"

// contains the state of the ARM system we are emulating
ARMstate state;

int main(int argc, char **argv) {
    // zero out memory and registers
    MEM = calloc(MEM_SIZE, sizeof(uint8_t));
    REGFILE = calloc(NUM_REGISTERS, sizeof(uint32_t));

    while(PC) {
        // fetch current instruction and increment PC to point to the next instruction
        uint8_t currInstr = MEM[PC];
        PC += INSTR_LENGTH;

        // just to suppress unused variable warnings for now
        currInstr += 0;

        // if (cond of currInstr is false) {
        //     continue;
        // }

        //decodeAndExecute(instr)
    }

    // print the final system state

    return EXIT_SUCCESS;
}
