#include "assembler.h"


static void parseInstructions(Assembler *this);
static void writeToBinaryFile(Assembler *this);



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
    createSymbolTableAndCountInstrs(this, &symbolTable);

    // do second pass
    parseInstructions(this);

    // write to binary
    writeToBinaryFile(this);
}


void assemblerDeInit(Assembler *this) {
    //something
}


static void parseInstructions(Assembler *this) {
    // initialise ListMap<mneumonic, functions>

    // iterate over each instruction
    //     (lookup mneumonic map) (this, i)
}

static void writeToBinaryFile(Assembler *this) {
    // do some shit
}
