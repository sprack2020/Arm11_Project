//
// Created by drspaceship on 30/05/16.
//
#include "ListMap.h"

//initialise a list map
ListMap *ListMapInit(ListMap *this) {
    this->first = NULL;
    return this;
}

//takes a deleter function pointer and deletes the nodes from first to last
ListMap *ListMapDeinit(
        ListMap *this,
        void (*deleter)(void *key, void *value)
) {
    assert(this != NULL);
    ListMapIterator it = ListMapGetIterator(this);
    ListMapNode *curr;
    while ((curr = ListMapIteratorNext(&it)) != NULL) {
        ListMapNodeDelete(curr, deleter);
    }
    return this;
}

ListMapIterator ListMapGetIterator(ListMap *this) {
    assert(this != NULL);
    ListMapIterator it;
    ListMapIteratorInitWithListMap(&it, this);
    return it;
}

void ListMapAdd(
        ListMap *this,
        void *key,
        void *value
) {
    assert(this != NULL);
    ListMapNode *newNode = ListMapNodeNewWithKV(key, value);
    newNode->next = this->first;
    this->first = newNode;
}

void *ListMapGet(
        ListMap *this,
        void *key,
        bool (*equals)(void *, void *)
) {
    assert(this != NULL);

    ListMapIterator it = ListMapGetIterator(this);
    ListMapNode *curr;

    while ((curr = ListMapIteratorNext(&it)) != NULL) {
        if (equals(curr->key, key)) {
            return curr->value;
        }
    }

    return NULL;
}
