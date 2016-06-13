//
// Created by drspaceship on 13/06/16.
//

#include "compiler.h"

static void compiler_init_sourceLines(Compiler_t *this);

Compiler_t *init_compiler(Compiler_t *this, char *sourcePath, char *outputPath) {
    assert(this != NULL);

    this->sourcePath = sourcePath;
    this->outputPath = outputPath;
    compiler_init_sourceLines(this);
}
void compile(Compiler_t *this) {
    assert(this != NULL);
}

Compiler_t *deinit_compiler(Compiler_t *this) {
    assert(this != NULL);

    // free sourceLines
    for (int i = 0; i < this->numLines; i++) {
        free(this->sourceLines[i]);
    }
    free(this->sourceLines);

    return this;
}

//read all the lines (delimited by \n) in file to an array of strings
static void compiler_init_sourceLines(Compiler_t *this) {
    //open the source file in read text mode.
    FILE *sourceFile = openFile(this->sourcePath, "rt");

    // get number of lines and allocate space for lines array.
    int numLines = countLines(sourceFile);
    this->numLines = countLines(sourceFile);
    this->sourceLines = malloc(sizeof(char *) * numLines);

    // allocate space for and read in each line
    for (int i = 0; i < numLines; ++i) {
        char *str = malloc(sizeof(char) * MAX_LINE_LENGTH);

        if (!fgets(str, MAX_LINE_LENGTH, sourceFile)) {
            fprintf(stderr, "Error reading line %d\n", i);
            exit(EXIT_FAILURE);
        }

        //strip leading space on line, and if it was empty, don't count it.
        str = skipSpace(str);
        if (*str != '\0') {
            this->sourceLines[i] = str;
        } else {
            --i;
        }
    }

    closeFile(sourceFile);
}
