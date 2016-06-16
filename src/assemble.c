#define NDEBUG

#include <stdlib.h>
#include <stdio.h>
#include <assembler/assemblerStruct.h>
#include <assembler/assembler.h>


int main(int argc, char *argv[]) {
    //check for correct number of arguments
    if (argc != 3) {
        fprintf(stderr, "Usage: assemble <source file> <output file>\n");
        exit(EXIT_FAILURE);
    }

    Assembler assembler;
    assemblerInit(&assembler, argv[1], argv[2]);
    assemble(&assembler);
    assemblerDeInit(&assembler);

    return EXIT_SUCCESS;
}
