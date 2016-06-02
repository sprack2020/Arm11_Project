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

void closeFile(File *file) {
    int closeErrorCode = fclose(file);

    if (closeErrorCode == EOF) {
        fprintf(stderr, "Error in io: closeFile: Failed to close file.");
        exit(EXIT_FAILURE);
    }
}

//count the number of lines in a file.
int countLines(FILE *file) {
    char *lineBuff = (char *) malloc(sizeof(char) * MAX_LINE_LENGTH);
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
