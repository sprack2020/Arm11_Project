//
// Created by drspaceship on 30/05/16.
//

#include <elf.h>
#include "ListMapTests.h"

int strPtrCmp(void *x, void *y) {
    return strcmp((char*)x, (char*)y);
}

int intPtrCmp(void *x, void *y) {
    return *(int *) x != *(int *) y;
}

void ListMapTestInit() {
    ListMap lm;
    ListMapInit(&lm);
    assert(lm.first == NULL);
}

static bool strEquals(void *s1, void *s2) {
    return strcmp((char *) s1, (char *) s2) == 0;
}

static int one(void) {
    return 1;
}

static int two(void) {
    return 2;
}

static int three(void) {
    return 3;
}

void ListMapTestStringInt() {
    ListMap lm;
    ListMapInit(&lm);
    char *strs[] = {
            "list",
            "map",
            "poo"
    };
    for (int i = 0; i < 3; ++i) {
        ListMapAdd(&lm, strs[i], (void *) (intptr_t) i);
    }
    for (int i = 0; i < 3; ++i) {
        assert((int) (intptr_t) ListMapGet(&lm, strs[i], &strEquals) == i);
    }
    ListMapDeinit(&lm, NULL);
}

void ListMapTestStringToFunc() {
    ListMap lm;
    ListMapInit(&lm);
    char *strs[] = {
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
        ListMapAdd(&lm, strs[i], &fs[i]);
    }
    for (int i = 0; i < 3; ++i) {
        int (**fPtr)(void) = ListMapGet(&lm, strs[i], &strEquals);
        assert(*fPtr == fs[i]);
        assert((*fPtr)() == i + 1);
    }
    ListMapDeinit(&lm, NULL);
}

void itemNotInEmptyMap(void) {
//    ListMap *lm = ListMapNew();
//    assert(get(lm, TESTSTR, &strPtrCmp) == NULL);
}

void retrieveItemIsSame(void) {
//    ListMap *lm = ListMapNew();
//    int testint = TESTINT;
//    add(lm, &testint, &testint);
//    assert(*(int*)get(lm, &testint, &intPtrCmp) == TESTINT);
}

void retrieveItemFromMultiple(void) {
//    ListMap *lm = ListMa/*pNew();
//    for (int i = 'a'; i < 'c'; i++) {
        // int *j = &i;
//        add(lm, malloc(sizeof(char)), malloc(sizeof(char) * 2));
//    }
//    assert(strcmp(get(lm*/, "sd", &strPtrCmp), "fd") == 0);
}
