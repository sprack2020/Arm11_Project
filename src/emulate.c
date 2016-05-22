#include "emulate.h"

// contains the state of the ARM system we are emulating
ARMstate state;

int main(int argc, char **argv) {
    // zero out memory and registers
    MEM = calloc(MEM_SIZE, sizeof(uint8_t));
    REGFILE = calloc(NUM_REGISTERS, sizeof(uint32_t));

    while(PC) {
        // fetch current instruction and increment PC to point to the next instruction
        uint8_t currInstr = MEM[PC];  //This is incorrect, instructions are 4 bytes
        PC += INSTR_LENGTH;


        // if (cond of currInstr is false) {  //use checkCond(instr) here
        //     continue;
        // }

        //decodeAndExecute(instr)
    }

    // print the final system state

    return EXIT_SUCCESS;
}
