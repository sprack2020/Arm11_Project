
#include "symbolTable.h"

void createSymbolTableAndCountInstrs(Assembler *this) {
    char *currLine;
    int instructionlessLabels = 0;
    for (int i = 0, n = this->numLines; i < n; ++i) {
        currLine = this->sourceLines[i];

        handleLabel(this, currLine, i, &instructionlessLabels);
    }
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
    int instrAddress = lineNo * INSTR_LENGTH;

    // if there is a label
    if (strcmp(line, label)) {
        ListMapAdd(this->symbolTable, label, &instrAddress);
        char *restOfLine = strtok(NULL, "\n\0");
        if (!hasInstr(restOfLine)) {
            (*instructionlessLabels)++;
        }
    } else {
        free(label);
    }
}

bool hasInstr(char *line) {
    while (line != NULL && isspace(*line)) {
        line++;
    }
    return line == NULL ? false : (bool) isalpha(*line);
}
