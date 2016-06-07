//
// Created by Shiraz Butt on 03/06/2016.
//

#include <assert.h>
#include <util/GenericListMap.h>
#include <string.h>

typedef int (*testFunc)(void);
typedef char* String

GEN_LIST_MAP(String, testFunc);

static int one(void) {
    return 1;
}

static int two(void) {
    return 2;
}

static int three(void) {
    return 3;
}

void ListMapTestStringToFunc() {
    ListMap_StringtestFunc lm;
    ListMapInit_StringtestFunc(&lm);
    String strs[] = {
            "one",
            "two",
            "three"
    };
    int (*fs[])(void) = {
            &one,
            &two,
            &three
    };
    for (int i = 0; i < 3; ++i) {
        ListMapAdd_StringtestFunc(&lm, strs[i], &fs[i]);
    }
    for (int i = 0; i < 3; ++i) {
        testFunc fPtr = ListMapGet_StringtestFunc(&lm, strs[i], &strcmp);
        assert(fPtr == fs[i]);
        assert(fPtr() == i + 1);
    }
    ListMapDeinit_StringtestFunc(&lm, NULL);
}

int main(void) {

}