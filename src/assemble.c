#include <stdlib.h>
#include <stdio.h>
#include <assembler/assembler.h>

int main(int argc, char **argv) {
    //check for correct number of arguments
    if (argc != 3) {
        fprintf(stderr, "Usage: assemble <source file> <output file>\n");
        exit(EXIT_FAILURE);
    }

    Assembler *assembler = newAssembler(argv);
    assemble(assembler);
    assemblerDeInit(assembler);

    return EXIT_SUCCESS;
}
