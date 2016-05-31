//
// Created by shiraz on 30/05/16.
//
#include "assembler.h"

static void createSymbolTable(Assembler *this, ListMap *symbolTable);
static void parseInstructions(Assembler *this);
static void writeToBinaryFile(Assembler *this);
static void initSourceLines(Assembler *assembler);
static void handleLabel(Assembler *this, char *line, int lineNo,
        ListMap *symbolTable);


// constructs a new assembler and returns a pointer to it
Assembler *newAssembler(char **argv) {
    Assembler *a = malloc(sizeof(Assembler));
    assemblerInit(a, argv[1], argv[2]);

    return a;
}

// initiates an assembler
void assemblerInit(Assembler *this, char *sourcePath, char *binaryPath) {
    this->sourcePath = sourcePath;
    this->binaryPath = binaryPath;
    this->numLines = 0;
    this->numInstrs = 0;
    this->firstEmptyAddr = 0;
    this->currInstrAddr = 0;
    initSourceLines(this);
}

// assembles the source file
void assemble(Assembler *this) {
    ListMap symbolTable;
    ListMapInit(&symbolTable);

    // do first pass
    createSymbolTable(this, &symbolTable);

    // do second pass
    parseInstructions(this);

    // write to binary
    writeToBinaryFile(this);
}

//read all the lines (delimited by \n) in file to an array of strings
static void initSourceLines(Assembler *assembler) {
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

void assemblerDeInit(Assembler *this) {
    //something
}

static void handleLabel(
        Assembler *this,
        char *line,
        int lineNo,
        ListMap *symbolTable
) {
    // get the label
    char *label = strtok(line, LABEL_DELIMITER);

    lineNo *= INSTR_LENGTH;
    // if there is a label
    if (label != NULL) {
        ListMapAdd(symbolTable, label, &lineNo); // check warning
    }
}

static void createSymbolTable(Assembler *this, ListMap *symbolTable) {
    char *currLine;
    for (int i = 0, n = this->numLines; i < n; ++i) {
        currLine = this->sourceLines[i];

        handleLabel(this, currLine, i, symbolTable);
    }
}

static void parseInstructions(Assembler *this) {
    // initialise ListMap<mneumonic, functions>

    // iterate over each instruction
    //     (lookup mneumonic map) (this, i)
}

static void writeToBinaryFile(Assembler *this) {
    // do some shit
}
