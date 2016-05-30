#include <stdlib.h>
#include <stdio.h>
#include "io.h"

int main(int argc, char **argv) {
    //check for correct number of arguments
    if (argc != 3) {
        fprintf(stderr, "Usage: assemble <source file> <output file>\n");
        exit(EXIT_FAILURE);
    }

    //open source file in text mode and read the lines into an array
    FILE* src = openFile(argv[1], "rt");
    char** lines = readLines(src);
    fclose(src);

    //TODO: turn lines into instructions, somehow

    //write the assembled instructions to output file
    FILE* out = openFile(argv[2], "wb");
    if (writeInstrs(out, NULL, 0)) {
        fprintf(stderr, "Error writing binary file");
        exit(EXIT_FAILURE);
    }
    fclose(out);

    free(lines);
    return EXIT_SUCCESS;
}
