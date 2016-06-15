//
// Created by drspaceship on 13/06/16.
//

#include "compiler.h"

static void compiler_init_sourceLines(Compiler_t *this);
static void writeToAssemblyProgram(Compiler_t *this);
static void setupOpToMnem(Compiler_t *this);
static void setupGPIO(Compiler_t *this);

void init_compiler(Compiler_t *this, char *sourcePath, char *outputPath) {
    assert(this != NULL);

    this->sourcePath = sourcePath;
    this->outputPath = outputPath;
    compiler_init_sourceLines(this);

    this->variableTable = malloc(sizeof(ListMap));
    ListMapInit(this->variableTable);

    this->opToMnem = malloc(sizeof(ListMap));
    ListMapInit(this->opToMnem);
    setupOpToMnem(this);

    this->assemblyProgram = malloc(sizeof(char**) * MAX_LINES);
    this->instrAddr = 0;
    this->currLineNum = 0;

    setupGPIO(this);

}

static void setupOpToMnem(Compiler_t *this) {
    char *add = malloc(sizeof(char*));
    *add = '+';
    ListMapAdd(this->opToMnem, add, "add");

    char *sub = malloc(sizeof(char*));
    *sub = '-';
    ListMapAdd(this->opToMnem, sub, "sub");

    char *mul = malloc(sizeof(char*));
    *mul = '*';
    ListMapAdd(this->opToMnem, mul, "mul");
}

static void setupGPIO(Compiler_t *this) {
    variable_t *gpioState = malloc(sizeof(variable_t));
    init_variable(gpioState, 10);
    ListMapAdd(this->variableTable, GPIO_STATE, gpioState);
    makeLdr(this, gpioState->regNum, 0);

    variable_t *gpioReserved = malloc(sizeof(variable_t));
    init_variable(gpioReserved, 11);
    ListMapAdd(this->variableTable, GPIO_RESERVED, gpioReserved);
    makeLdr(this, gpioReserved->regNum, 0);

    variable_t *gpioPtr = malloc(sizeof(variable_t));
    init_variable(gpioPtr, 12);
    makeLdr(this, gpioPtr->regNum, 0x20200000);
    ListMapAdd(this->variableTable, GPIO_PTR, gpioPtr);


}

void compile(Compiler_t *this) {
    assert(this != NULL);

    parseInstructions(this, 0, 0);

    writeToAssemblyProgram(this);

}

void deinit_compiler(Compiler_t *this) {
    assert(this != NULL);

//    // free sourceLines
//    for (int i = 0; i < this->numLines; i++) {
//        free(this->sourceLines[i]);
//    }
//    free(this->sourceLines);

}

//read all the lines (delimited by \n) in file to an array of strings
static void compiler_init_sourceLines(Compiler_t *this) {
    assert(this != NULL);

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

void parseInstructions(Compiler_t *this, int whileID, int ifID) {

    char *currLine;
    char firstChar;

    for (int i = this->currLineNum; i < this->numLines; ++i) {
        currLine = skipSpace(this->sourceLines[i]);
        firstChar = currLine[0];

        if (firstChar == '[') {
            variableHandler(this, currLine);
        }
        else if (firstChar == '<') {
            this->currLineNum = i + 1;
            assignmentHandler(this, currLine, whileID);
        }
        else if (firstChar == 'W') {
            this->currLineNum = i + 1;
            whileHandler(this, currLine, whileID, ifID);
            return;
        }
        else if (firstChar == 'I') {
            ifHandler(this, currLine, whileID, ifID);
            return;
        }
        else if (firstChar == '}') {
            return;
        }
        else {
            //ignore
            printf("ignored %s", currLine);
        }
    }
}

static void writeToAssemblyProgram(Compiler_t *this) {
    // write to the first empty address
    int numToWrite = this->instrAddr;
    assert(numToWrite > 0 && this->assemblyProgram != NULL);

    FILE *outfile = openFile(this->outputPath, "wt");

    for (int i = 0; i < numToWrite; ++i) {
        fprintf(outfile, "%s\n", this->assemblyProgram[i]);
    }

    // close the outfile
    if (fclose(outfile) == EOF) {
        fputs("Assembler: Error closing binary file", stderr);
    }
}