//
// Created by drspaceship on 22/05/16.
//
#include "printState.h"

// gets the correct spacing to put before the ':'
// this is so all colons line up, thus they must appear as the fifth character
// of the line as CPSR is the longest register name and four letters long
int getCorrectSpacing(int32_t reg) {
    if (reg < 0 || reg > LAST_GENERAL_REGISTER) {
        fprintf(stderr, "Exception in printState: correctSpacing(): "
                "Attempting to print register that should not be printed: $%d",
                reg);
        exit(2);
    }

    // string representation of register number, allocate max possible space
    // it could need
    int maxSize = strlen(LONGEST_REGISTER_NAME);
    char regString[maxSize + 1];

    // convert reg into string stored in regString
    sprintf(regString, "%d", reg);

    return maxSize - strlen(regString) - 1;
}

// PRE: last instruction was halt
// behavior: outputs the state of the registers
void printState(void) {
    // print general purpose registers
    printf("Registers:\n");

    uint32_t reg;
    for (int i = 0; i <= LAST_GENERAL_REGISTER; i++) {
        reg = REGFILE[i];

        printf("$%d%*s:          %d (0x%0*x)\n", i, getCorrectSpacing(i), "",
                reg, HEX_PADDING, reg);
    }

    // print PC and CPSR
    printf("PC  :          %d (0x%0*x)\n", PC, HEX_PADDING, PC);
    printf("CPSR:          %d (0x%0*x)\n", CPSR, HEX_PADDING, CPSR);

    // print memory
    printf("Non-zero memory:\n");

    //TODO: GET BETTER NAMES FOR THIS AND MEM_PRINTING_INTERVAL
    uint32_t memLocationsToPrint;
    for (int i = 0; i < MEM_SIZE; i += MEM_PRINTING_INTERVAL) {
        read32Bits(&memLocationsToPrint, MEM + i);

        if (memLocationsToPrint != 0) {
            printf("0x%0*x: 0x%0*x\n", HEX_PADDING, i, HEX_PADDING
                    , memLocationsToPrint);
        }
    }

}
