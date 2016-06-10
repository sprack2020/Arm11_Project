//
// Created by drspaceship on 31/05/16.
//

#include "tokenizer.h"
#include "io.h"

void getTokens(char **buffer, int numTokens, char *line) {
    assert(numTokens >= 0);

    //strip any label and comments from the line
    line = stripLabel(line);
    stripComments(line);
    //separate the mnemonic
    buffer[0] = strtok(line, " ");
    //get rest of tokens
    for (int i = 1; i < numTokens - 2; ++i) {
        buffer[i] = skipSpace(strtok(NULL, ",\n"));
    }
    //split the last but one token on a space
    buffer[numTokens - 2] = skipSpace(strtok(NULL, " "));
    buffer[numTokens - 1] = skipSpace(strtok(NULL, "\n\0"));
}

//strips a label from a line. line must not be null.
char *stripLabel(char *line) {
    assert(line != NULL);

    char *res = line;
    int i = 0;
    //while we are not at the null character, check if we are the end of a label
    while (line[i]) {
        if (line [i] == ':') {
            //if we are, set result to the first char after skipping all space
            res = skipSpace(&line[++i]);
        }
        ++i;
    }

    return res;
}

//skips any leading space in a line
char *skipSpace(char *line) {
    if (line == NULL) {
        return line;
    }

    while (isspace(*line)) {
        line++;
    }

    return line;
}

//strips any comments from a line. line must not be null.
void stripComments(char *line) {
    while (*line != '\0') {
        if (*line == ';') {
            *line = '\0';
            return;
        }
        ++line;
    }
}
