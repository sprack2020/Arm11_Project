//
// Created by drspaceship on 13/06/16.
//

#include "compiler.h"

static void compiler_init_sourceLines(Compiler_t *this);
static void parseInstructions(Compiler_t *this);
static void writeToAssemblyProgram(Compiler_t *this);
static void setupOpToMnem(Compiler_t *this);
static void setupGPIO(Compiler_t *this);

void *init_compiler(Compiler_t *this, char *sourcePath, char *outputPath) {
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
    this->varRegNum = 0;

    setupGPIO(this);

    return this;
}

static void setupOpToMnem(Compiler_t *this) {
    ListMapAdd(this->opToMnem, (void *) '+', "add");
    ListMapAdd(this->opToMnem, (void *) '-', "sub");
    ListMapAdd(this->opToMnem, (void *) '*', "mul");
}

static void setupGPIO(Compiler_t *this) {
    variable_t *gpioState = malloc(sizeof(variable_t));
    init_variable(gpioState, 10);
    ListMapAdd(this->variableTable, "GPIO_STATE", gpioState);

    variable_t *gpioReserved = malloc(sizeof(variable_t));
    init_variable(gpioReserved, 11);
    ListMapAdd(this->variableTable, "GPIO_RESERVED", gpioReserved);

    variable_t *gpioPtr = malloc(sizeof(variable_t));
    init_variable(gpioPtr, 12);
    ListMapAdd(this->variableTable, "GPIO_PTR", gpioPtr);
}

void compile(Compiler_t *this) {
    assert(this != NULL);

    parseInstructions(this);

    writeToAssemblyProgram(this);

}

void *deinit_compiler(Compiler_t *this) {
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

static void parseInstructions(Compiler_t *this) {

    char *currLine;
    char firstChar;

    for (int i = 0; i < this->numLines; ++i) {
        currLine = skipSpace(this->sourceLines[i]);
        firstChar = currLine[0];

        if (firstChar == '[') {
            variableHandler(this, currLine);
        }
        else if (firstChar == '<') {
            assignmentHandler(this, currLine);
        }
        else if (firstChar == 'W') {
            whileHandler(this, currLine);
            return;
        }
        else if (firstChar == 'I') {
            ifHandler(this, currLine);
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

}