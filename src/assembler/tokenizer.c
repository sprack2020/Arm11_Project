//
// Created by drspaceship on 31/05/16.
//

#include "tokenizer.h"
#include "io.h"

void getTokens(char **buffer, int numTokens, char *line) {
    assert(numTokens >= 0);

    line = stripLabel(line);
    buffer[0] = strtok(line, " ");
    for (int i = 1; i < numTokens; ++i) {
        buffer[i] = skipSpace(strtok(NULL, ",\n"));
    }
}

char* stripLabel(char* line) {
    char* res = line;
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

char* skipSpace(char* line) {
    if (line == NULL) {
        return line;
    }

    while (isspace(*line)) {
        line++;
    }

    return line;
}
