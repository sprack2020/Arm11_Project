//
// Created by drspaceship on 31/05/16.
//

#ifndef ARM11_39_TOKENIZER_H
#define ARM11_39_TOKENIZER_H

#include <ctype.h>
#include <string.h>
#include <assert.h>

void getTokens(char **buffer, int numTokens, char *line);

char *stripLabel(char* line);
char *skipSpace(char* line);
void stripComments(char *line);

#endif //ARM11_39_TOKENIZER_H
