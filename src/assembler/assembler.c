//
// Created by shiraz on 30/05/16.
//
#include "assembler.h"

static void createSymbolTable(Assembler *this);
static void parseInstructions(Assembler *this);
static void writeToBinaryFile(Assembler *this);

// constructs a new assembler and returns a pointer to it
Assembler *newAssembler(char *srcPath) {
    Assembler *a = malloc(sizeof(Assembler));
    Assembler_init(a, srcPath);

    return a;
}

// initiates an assembler
void Assembler_init(Assembler *a, char *sourceFile) {
    a->sourceFile = openFile(sourceFile, "rt");
    a->numInstrs = 0;
    a->firstEmptyAddr = 0;
    a->currInstrAddr = 0;
}

// assembles
void assemble(Assembler *this) {
    // do first pass
    createSymbolTable(this);

    // do second pass
    parseInstructions(this);

    // write to binary
    writeToBinaryFile(this);
}

void createSymbolTable(Assembler *this) {
    // do some shit
}

void parseInstructions(Assembler *this) {

}

void writeToBinaryFile(Assembler *this) {

}
