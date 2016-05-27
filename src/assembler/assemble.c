#include <stdlib.h>
#include <stdio.h>
#include "io.h"

int main(int argc, char **argv) {
    //check for correct number of arguments
    if (argc != 3) {
        fprintf(stderr, "Usage: assemble <source file> <output file>\n");
        exit(EXIT_FAILURE);
    }

    //open source file in text mode
    FILE* src = openFile(arg[1], "rt");

    char** lines = readLines(src);
    fclose(src);

    free(lines);
    return EXIT_SUCCESS;
}
