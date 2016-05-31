//
// Created by drspaceship on 30/05/16.
//

#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <stdbool.h>
#include <assert.h>
#include "ListMapNode.h"

ListMapNode *ListMapNodeNewWithKV(void *key, void *value) {
    ListMapNode *this = malloc(sizeof(ListMapNode));
    assert(this != NULL);
    return ListMapNodeInitWithKV(this, key, value);
}

ListMapNode *ListMapNodeInitWithKV(
        ListMapNode *this,
        void *key,
        void *value
) {
    this->key = key;
    this->value = value;
    this->next = NULL;
    return this;
}

void ListMapNodeDelete(
        ListMapNode *this,
        void (*deleter)(void *, void *)
) {
    ListMapNodeDeinit(this, deleter);
    free(this);
}

ListMapNode *ListMapNodeDeinit(
        ListMapNode *this,
        void (*deleter)(void *, void *)
) {
    if (deleter != NULL) {
        deleter(this->key, this->value);
    }
    return this;
}
