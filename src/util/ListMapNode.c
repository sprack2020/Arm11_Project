#include <stdlib.h>
#include <assert.h>
#include "ListMapNode.h"

//generate a new node with a given key and value
ListMapNode *ListMapNodeNewWithKV(void *key, void *value) {
    ListMapNode *this = malloc(sizeof(ListMapNode));
    assert(this != NULL);
    return ListMapNodeInitWithKV(this, key, value);
}

//initialise a node
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

//use a deleter function to free memory for a node
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
