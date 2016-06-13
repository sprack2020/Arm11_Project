//
// Created by Shiraz Butt on 13/06/2016.
//

#include "TokenizerTest.h"

static void testLineComment(void);

void runTokenizerTests(void) {
    testLineComment();
}

static void testLineComment(void) {
    // fairly random
    const int numTokens = 3;

    char testLine1[] = ";;; a weird comment";
    char testLine2[] = "; a comment";

    char *tokens[numTokens];

    getTokens(tokens, numTokens, testLine1);
    bool successTest1 = tokens[0] == '\0';
    printf("Test testLineComment: testLine1 %s\n", successTest1 ? "PASSED" :
                                                   "FAILED");

    getTokens(tokens, numTokens, testLine2);
    bool successTest2 = tokens[0] == '\0';
    printf("Test testLineComment: testLine2 %s\n", successTest2 ? "PASSED" :
                                                   "FAILED");
}


