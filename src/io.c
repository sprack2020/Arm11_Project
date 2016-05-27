#include "io.h"

#define MAXLINE 512 //maximum line length including newline/EOF

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
