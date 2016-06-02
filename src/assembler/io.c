#include <assembler/io.h>

//open the source file in read only text-mode, and report any errors
FILE *openFile(char *path, char *mode) {
    FILE *filePtr = fopen(path, mode);
    if (!filePtr) {
        fprintf(stderr, "Error opening source file: %s\n", path);
        exit(EXIT_FAILURE);
    }

    return filePtr;
}

//count the number of lines in a file.
int countLines(FILE *file) {
    char* lineBuff = (char *) malloc(sizeof(char) * MAX_LINE_LENGTH);
    int numLines = 0;

    //while fgets does not return a NULL pointer (indicating EOF)
    while (fgets(lineBuff, MAX_LINE_LENGTH, file) != NULL) {
        ++numLines;
    }

    return numLines;
}


/*  writes length (big endian) instructions to file (as little endian)
 *  returns 1 if any errors occured, 0 otherwise.
 *  NOTE: modifies instrs by swapping endianness */
int writeInstrs(FILE *file, uint32_t *instrs, int length) {
    //swap endianness of all instructions
    for (int i = 0; i < length; ++i) {
        swapEndianness(instrs + i);
    }

    //write instructions to file and return 1 if any objects failed to write
    return fwrite(instrs, sizeof(uint32_t), length, file) < length ? 1 : 0;
}

//read all the lines (delimited by \n) in file to an array of strings
void initSourceLines(Assembler *assembler) {
    //open the source file in read text mode.
    FILE *sourceFile = openFile(assembler->sourcePath, "rt");

    // get number of lines and allocate space for lines array.
    int numLines = countLines(sourceFile);
    assembler->numLines = numLines;
    assembler->sourceLines = malloc(sizeof(char*) * numLines);

    // allocate space for and read in each line
    for (unsigned int i = 0; i < numLines; ++i) {
        char* str = malloc(sizeof(char) * MAX_LINE_LENGTH);

        if (fgets(str, MAX_LINE_LENGTH, sourceFile)) {
            fprintf(stderr, "Error reading line %u\n", i);
            exit(EXIT_FAILURE);
        }

        //put the string pointer into sourceLines
        assembler->sourceLines[i] = str;
    }
    fclose(sourceFile);
}
