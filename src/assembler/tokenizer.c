//
// Created by drspaceship on 31/05/16.
//

#include "tokenizer.h"


void getTokens(char **buffer, int numTokens, char *line) {
    assert(numTokens >= 0);
    
    buffer[0] = strtok(line, " ");
    for (int i = 1; i < numTokens; ++i) {
        buffer[i] = strtok(NULL, ",");
    }
}
