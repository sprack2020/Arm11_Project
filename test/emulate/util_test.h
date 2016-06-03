#include <stdbool.h>
#include "util/util.h"

#define NO_INSTR_BITS 32

typedef struct {
    uint32_t instr;
    int j;
    int i;
    uint32_t expectedBits;
} Test;

Test * newTest(uint32_t instr, int j, int i, uint32_t expectedBits) {
    Test *test  = malloc(sizeof(Test));
    test->instr = instr;
    test->j     = j;
    test->i     = i;
    test->expectedBits = expectedBits;

    return test;
}

void freeTest(Test *test) {
    free(test);
}

bool runTest(Test *test) {
    return (bool) (test->expectedBits ==
            extractBits(test->instr, test->j, test->i));
}

char * toBoolString(uint32_t number) {
    char *boolString = malloc(sizeof(char) * (NO_INSTR_BITS + 1));
    boolString[NO_INSTR_BITS] = '\0';

    for (int i = NO_INSTR_BITS - 1; i >= 0; --i, number >>= 1) {
        boolString[i] = (number & 1) + '0';
    }

    return boolString;
}

char * toString(Test *test) {
    const int size = (NO_INSTR_BITS + 1 + 1 + 1) * sizeof(char) + sizeof("extractBits(,,)");
    char *string = malloc(size);

    snprintf(string, size, "extractBits(%s, %d, %d)",
            toBoolString(test->instr), test->j, test->i);

    return string;
}
