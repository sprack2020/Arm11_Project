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
Assembler *newAssembler(char *srcPath) {
    Assembler *a = malloc(sizeof(Assembler));
    Assembler_init(a, srcPath);

    return a;
}

// initiates an assembler
void Assembler_init(Assembler *this, char *sourceFile) {
    this->sourceFile = openFile(sourceFile, "rt");
    this->numLines = 0;
    this->firstEmptyAddr = 0;
    this->currInstrAddr = 0;
    initSourceLines(this);
}

//read all the lines (delimited by \n) in file to an array of strings
static void initSourceLines(Assembler *assembler) {
    // get number of lines and allocate space for lines sourcefile
    int numLines = countLines(assembler->sourceFile);
    assembler->numLines = numLines;
    assembler->sourceFile = malloc(sizeof(char *) * numLines);

    // allocate space for and read in each line
    for (unsigned int i = 0; i < numLines; ++i) {
        char* str = malloc(sizeof(char) * MAX_LINE_LENGTH);

        if (fgets(str, MAX_LINE_LENGTH, assembler->sourceFile)) {
            fprintf(stderr, "Error reading line %u\n", i);
            exit(EXIT_FAILURE);
        }
    }
}

void AssemblerDeinit(Assembler *this) {
    fclose(this->sourceFile);
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

static void handleLabel(
        Assembler *this,
        char *line,
        int lineNo,
        ListMap *symbolTable
) {
    // get the label
    char *label = strtok(line, LABEL_DELIMITER);

    // if there is a label
    if (label != NULL) {
        ListMapAdd(symbolTable, label, lineNo * INSTR_LENGTH); // check warning
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
