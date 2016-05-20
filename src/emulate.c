#include <stdint.h>
#include <stdlib.h>

#define MEM_SIZE 65536
#define NUM_REGISTERS 17

#define INSTR_LENGTH 4

#define MEM state.memory
#define REGFILE state.registers
#define PC state.registers[15]

// put in different file?
typedef struct ARMstate {
    uint8_t *memory;
    uint32_t *registers;
} ARMstate;

// contains the state of the ARM system we are emulating
ARMstate state;

int main(int argc, char **argv) {
    // zero out memory and registers
    MEM = calloc(MEM_SIZE, sizeof(uint8_t));
    REGFILE = calloc(NUM_REGISTERS, sizeof(uint32_t));

    while(PC) {
        // fetch current instruction and increment PC to point to the next instrution
        uint8_t currInstr = MEM[PC];
        PC += INSTR_LENGTH;

        // just to supress unnused variable warnings for now
        currInstr += 0;

        // if (cond of currInstr is false) {
        //     continue;
        // }
    }

    // print the final system state

    return EXIT_SUCCESS;
}
