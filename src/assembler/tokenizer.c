//
// Created by drspaceship on 31/05/16.
//

#include "tokenizer.h"


void getTokens(char **buffer, char *line) {
    buffer[0] = strtok(line, " ");
    for (int i = 1; i < NUM_TOKENS; ++i) {
        buffer[i] = strtok(NULL, ",");
    }
}
