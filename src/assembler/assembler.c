#include "assembler.h"


static void parseInstructions(Assembler *this);
static void writeToBinaryFile(Assembler *this);
static void initSourceLines(Assembler *assembler);


// constructs a new assembler and returns a pointer to it
Assembler *newAssembler(char *sourcePath, char *binaryPath) {
    Assembler *a = malloc(sizeof(Assembler));
    assemblerInit(a, sourcePath, binaryPath);

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

    // TODO: symbol and function tables
}

//read all the lines (delimited by \n) in file to an array of strings
static void initSourceLines(Assembler *this) {
    //open the source file in read text mode.
    FILE *sourceFile = openFile(this->sourcePath, "rt");

    // get number of lines and allocate space for lines array.
    int numLines = countLines(sourceFile);
    this->numLines = numLines;
    this->sourceLines = malloc(sizeof(char*) * numLines);

    // allocate space for and read in each line
    for (int i = 0; i < numLines; ++i) {
        char *str = malloc(sizeof(char) * MAX_LINE_LENGTH);

        if (fgets(str, MAX_LINE_LENGTH, sourceFile)) {
            fprintf(stderr, "Error reading line %u\n", i);
            exit(EXIT_FAILURE);
        }

        //put the string pointer into sourceLines
        this->sourceLines[i] = str;
    }

    closeFile(sourceFile);
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

// deinitialises an assembler
void assemblerDeInit(Assembler *this) {
    // free sourcelines
    for (int i = 0, n = this->numLines; i < n; i++) {
        free(&this->sourceLines[i]);
    }
    free(this->sourceLines);

    // free binary program
    free(this->binaryProgram);

    // TODO: free function/symbol table??

    // don't free(this) i think
}

// ignore this code, its very wrong, am in process of writing it - Shiraz
// parses .sourceLines into instructions stored in .binaryProgram
static void parseInstructions(Assembler *this) {
    // again, are we making the table local to the function or as a field?

    // initialise ListMap<mneumonic, functions>
    functionTable ft;
    functionTableInit(&ft);

    // iterate over each instruction
    //     (lookup mneumonic map) (this, line[i])
    // tokens should be array of strings, how to allocate it?
    char *tokens[NUM_TOKENS];

    // definitely find a more optimal way instead of allocating so much memory
    for (int i = 0; i < NUM_TOKENS; i++) {
        tokens[i] = malloc(MAX_LINE_LENGTH * sizeof(char));
    }

    // for each line, get the tokens and generate the instruction
    for (int i = 0, n = this->numLines; i < n; i++) {
        getTokens(tokens, NUM_TOKENS, this->sourceLines[i]);
        char *mnem = tokens[0];

        functionTableGet(&ft, mnem)(this, this->sourceLines[i]);
    }

    // free tokens
    for (int i = 0; i < NUM_TOKENS; i++) {
        free(tokens[i]);
    }
}

// writes .binaryProgram to the file with name .binaryPath
static void writeToBinaryFile(Assembler *this) {
    int numInstrs = this->numInstrs;
    assert(numInstrs > 0 && this->binaryProgram != NULL);

    FILE *outfile = openFile(this->binaryPath, "wb");

    int numWritten =
            (int) fwrite(this->binaryProgram, sizeof(uint32_t), this->firstEmptyAddr, outfile);
    if (numWritten != numInstrs) {
        fputs("Assembler: Error When writing instructions to binary file.\n",
                stderr);
    }

    if (fclose(outfile) == EOF) {
        fputs("Assembler: Error closing binary file", stderr);
    }
}
