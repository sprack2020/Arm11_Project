#include "HashMap.h"

const int DEFAULT_BUCKETS = 16;

HashMap *HashMapInit(
        HashMap *this
) {
    return HashMapInitWithBuckets(this, DEFAULT_BUCKETS);
}

HashMap *HashMapInitWithBuckets(
        HashMap *this,
        int numBuckets
) {
    this->buckets = malloc(numBuckets * sizeof(ListMap));
    for (int i = 0; i < numBuckets; ++i) {
        ListMapInit(this->buckets + i);
    }
    this->numBuckets = numBuckets;
    return this;
}

HashMap *HashMapDeinit(
        HashMap *this,
        void (*deleter)(void *, void *)
) {
    for (int i = 0; i < this->numBuckets; ++i) {
        ListMapDeinit(this, deleter);
    }
    free(this->buckets);
    return this;
}

void HashMapPut(
        HashMap *this,
        void *key,
        void *value,
        int (*hash)(void *),
        bool (*equals)(void *, void *)
) {
    ListMap *bucket = this->buckets + (hash(key) % this->numBuckets);
    ListMapIterator it = ListMapGetIterator(bucket);
    ListMapNode *curr;
    while ((curr = ListMapIteratorNext(&it)) != NULL) {
        if (equals(curr->key, key)) {
            curr->value = value;
            return;
        }
    }
    ListMapAdd(bucket, key, value);
}

void *HashMapGet(
        HashMap *this,
        void *key,
        int (*hash)(void *),
        bool (*equals)(void *, void *)
) {
    ListMap *bucket = this->buckets + (hash(key) % this->numBuckets);
    ListMapIterator it = ListMapGetIterator(bucket);
    ListMapNode *curr;
    while ((curr = ListMapIteratorNext(&it)) != NULL) {
        if (equals(curr->key, key)) {
            return curr->value;
        }
    }
    return NULL;
}
