#include "util_test.h"

char *getResultString(bool testResult) {
    return testResult ? "passed" : "failed";
}

void printResult(char *testName, bool correctResult, bool correctCarry) {
    printf("%s: Result test %s, carry test %s\n", testName,
           getResultString(correctResult), getResultString(correctCarry));
}

int main(void) {
//    Test *t1 = newTest(3867, 9, 3, 99);
//    Test *t2 = newTest(291437, 20, 11, 142);
//    Test *t3 = newTest(320, 31, 0, 320);
//    Test *t4 = newTest(7483, 0, 0, 1);
//    Test *t5 = newTest(90352543, 31, 31, 0);
//
//    printf("%s: Test %s\n", toString(t1), runTest(t1) ? "passed!" : "failed!");
//    printf("%s: Test %s\n", toString(t2), runTest(t2) ? "passed!" : "failed!");
//    printf("%s: Test %s\n", toString(t3), runTest(t3) ? "passed!" : "failed!");
//    printf("%s: Test %s\n", toString(t4), runTest(t4) ? "passed!" : "failed!");
//    printf("%s: Test %s\n", toString(t5), runTest(t5) ? "passed!" : "failed!");
//
//    free(t1);
//    free(t2);
//    free(t3);
//    free(t4);
//    free(t5);

    uint32_t word;
    uint8_t bytes[4] = {0x12, 0x34, 0x56, 0x78};
    uint32_t expectedResult = 0x12345678;
    read32Bits(&word, bytes);
    printf("read32bits test returned: 0x%08x, test %s\n",
           word, word == expectedResult ? "passed" : "failed");

    uint8_t moreBytes[4] = {0x3e, 0x22, 0x5f, 0x11};
    expectedResult = 0x3e225f11;
    read32Bits(&word, moreBytes);
    printf("read32bits test 2 returned : 0x%08x, test %s\n",
            word, word == expectedResult ? "passed" : "failed");

//    ShiftResult LSL_test = binaryShift(0x01100111, LSL, 16);
//    bool correctResult = LSL_test.result == 0x01110000;
//    bool correctCarry = LSL_test.carry == true;
//    printf("LSL test 1: Result test %s, carry test %s\n",
//           getResultString(correctResult), getResultString(correctCarry));
//
//    ShiftResult LSL_test2 = binaryShift(0x01100111, LSL, 4);
//    correctResult = LSL_test2.result == 0x11001110;
//    correctCarry = LSL_test2.carry == false;
//    printf("LSL test 2: Result test %s, carry test %s\n",
//           getResultString(correctResult), getResultString(correctResult));
//
//    ShiftResult LSR_test = binaryShift(0xc83fe38a, LSR, 24);
//    correctResult = LSR_test.result == 0x000000c8;
//    correctCarry = LSR_test.carry == false;
//    printResult("LSR test 1", correctResult, correctCarry);
//
//    ShiftResult LSR_test2 = binaryShift(0xffffffff, LSR, 12);
//    correctResult = LSR_test2.result == 0x000fffff;
//    correctCarry = LSR_test2.carry == true;
//    printResult("LSR test 2", correctResult, correctCarry);
//
//    ShiftResult ASR_test1 = binaryShift(0xf0ffffff, ASR, 12);
//    correctResult = ASR_test1.result == 0xffff0fff;
//    correctCarry = ASR_test1.carry == true;
//    printResult("ASR test 1", correctResult, correctCarry);
//
//    ShiftResult ASR_test2 = binaryShift(0x00000000, ASR, 8);
//    correctResult = ASR_test2.result == 0x00000000;
//    correctCarry = ASR_test2.carry == false;
//    printResult("ASR test 2", correctResult, correctCarry);
//
//    ShiftResult ROR_test1 = binaryShift(0x0bf00f5f, ROR, 16);
//    correctResult = ROR_test1.result == 0x0f5f0bf0;
//    correctCarry = ROR_test1.carry == false;
//    printResult("ROR test 1", correctResult, correctCarry);
//
//    ShiftResult ROR_test2 = binaryShift(0x0ebfffbf, ROR, 24);
//    correctResult = ROR_test2.result == 0xbfffbf0e;
//    correctCarry = ROR_test2.carry == true;
//    printResult("ROR test 2", correctResult, correctCarry);

    uint8_t x = 130;
    int8_t y = x;
    printf("%d casted to signed is %d\n", x, y);
}
