
#include "symbolTable.h"

void createSymbolTableAndCountInstrs(Assembler *this) {
    char *currLine;
    int instructionlessLabels = 0;
    for (int i = 0, n = this->numLines; i < n; ++i) {
        currLine = this->sourceLines[i];

        handleLabel(this, currLine, i, &instructionlessLabels);
    }
    //reset current instruction address.
    this->currInstrAddr = 0;
    this->numInstrs = this->numLines - instructionlessLabels;
    this->firstEmptyAddr = this->numInstrs * INSTR_LENGTH;
}

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
    int instrAddress = this->currInstrAddr;

    // if there is a label
    if (strcmp(line, label)) {
        ListMapAdd(this->symbolTable, label, &instrAddress);
        char *restOfLine = strtok(NULL, "\n\0");
        if (!hasInstr(restOfLine)) {
            (*instructionlessLabels)++;
        } else {
            this->currInstrAddr++;
        }
    } else {
        free(label);
        this->currInstrAddr++;
    }
}

bool hasInstr(char *line) {
    while (line != NULL && isspace(*line)) {
        line++;
    }
    return line == NULL ? false : (bool) isalpha(*line);
}
