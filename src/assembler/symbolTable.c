
#include "symbolTable.h"

// Creates the symbol table of labels to addresses
void createSymbolTableAndCountInstrs(Assembler *this) {
    char *currLine;
    int instructionlessLabels = 0;

    // iterate over all source lines looking for labels
    for (int i = 0, n = this->numLines; i < n; ++i) {
        currLine = this->sourceLines[i];

        handleLabel(this, currLine, i, &instructionlessLabels);
    }

    //reset current instruction address.
    this->currInstrAddr = 0;
    this->numInstrs = this->numLines - instructionlessLabels;
    this->firstEmptyAddr = this->numInstrs * INSTR_LENGTH;
}

// Adds the label to the symbol table
void handleLabel(
        Assembler *this,
        char *line,
        int lineNo,
        int *instructionlessLabels
) {
    // get the label
    char *label = malloc(sizeof(char) * MAX_LINE_LENGTH);
    strcpy(label, line);
    label = strtok(label, LABEL_DELIMITER);
    int *instrAddress = malloc(sizeof(int));
    *instrAddress = this->currInstrAddr;

    // if there is a label add it to the symbol table
    if (strcmp(line, label)) {
        ListMapAdd(this->symbolTable, label, instrAddress);
        char *restOfLine = strtok(NULL, "\n\0");

        // account for possible instruction after label on same line
        if (!hasInstr(restOfLine)) {
            (*instructionlessLabels)++;
        } else {
            this->currInstrAddr+= INSTR_LENGTH;
        }
    } else {
        free(label);
        free(instrAddress);
        this->currInstrAddr+= INSTR_LENGTH;
    }
}

// checks if the string has an instruction
bool hasInstr(char *line) {
    while (line != NULL && isspace(*line)) {
        line++;
    }
    return line == NULL ? false : (bool) isalpha(*line);
}

// removes elements from a symbol table
void symbolTableDeleter(void *label, void *address) {
    free(label);
    free(address);
}
