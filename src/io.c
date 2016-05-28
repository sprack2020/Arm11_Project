#include <stdio.h>
#include <stdint.h>
#include "util.c"

#define MAXLINE 512 //maximum line length including newline/EOF

FILE* openFile(char* path, char* mode);
char** readLines(FILE* file);
int writeInstrs(FILE* file, uint32_t* instrs, int length);

//open the source file in read only text-mode, and report any errors
FILE* openFile(char* path, char* mode) {
    FILE* filePtr = fopen(path, mode);
    if (filePtr == NULL) {
        fprintf(stderr, "Error opening source file: %s\n", path);
        exit(EXIT_FAILURE);
    }

    return filePtr;
}

//count the number of lines in a file.
int countLines(FILE* file) {
    char* lineBuff = (char*) malloc(sizeof(char) * MAXLINE);
    int numLines = 0;

    //while fgets does not return a NULL pointer (indicating EOF)
    while (fgets(lineBuff, MAXLINE, file) != NULL) {
        ++numLines;
    }

    return numLines;
}

//read all the lines (delimited by \n) in file to an array of strings
char** readLines(FILE* file) {
    int numLines = countLines(file);
    char** lines = malloc(sizeof(char*) * numLines);

    for (unsigned int i = 0; i < numLines; ++i) {
        char* str = malloc(sizeof(char) * MAXLINE);
        if (fgets(str, MAXLINE, file)) {
            fprintf(stderr, "Error reading line %u", i);
            break;
        }
    }

    return lines;
}

/*  writes length (big endian) instructions to file (as little endian)
 *  returns 1 if any errors occured, 0 otherwise.
 *  NOTE: modifies instrs by swapping endianness */
int writeInstrs(FILE* file, uint32_t* instrs, int length) {
    //swap endianness of all instructions
    for (int i = 0; i < length; ++i) {
        instrs[i] = swapEndianness(instrs[i]);
    }

    //write instructions to file and return 1 if any objects failed to write
    return fwrite(instrs, sizeof(uint32_t), length, file) < length ? 1 : 0;
}
