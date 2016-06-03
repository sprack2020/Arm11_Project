#include <ctype.h>
#include "symbolTable.h"

void createSymbolTableAndCountInstrs(Assembler *this) {
    char *currLine;
    int instructionlessLabels = 0;
    for (int i = 0, n = this->numLines; i < n; ++i) {
        currLine = this->sourceLines[i];

        handleLabel(this, currLine, i, &instructionlessLabels);
    }
    this->numInstrs = this->numLines - instructionlessLabels;
    this->firstEmptyAddr = this->numInstrs;
}

void handleLabel(
        Assembler *this,
        char *line,
        int lineNo,
        int *instructionlessLabels,
) {
    // get the label
    char *label = strtok(line, LABEL_DELIMITER);
    lineNo *= INSTR_LENGTH;

    // if there is a label
    if (label != NULL) {
        ListMapAdd(this->symbolTable, label, &lineNo);
        char *restOfLine = strtok(NULL, "\n\0");
        if (!hasInstr(restOfLine)) {
            (*instructionlessLabels)++;
        }
    }
}

bool hasInstr(char *line) {
    while (isspace(*line)) {
        line++;
    }
    return (bool) isalpha(*line);
}
