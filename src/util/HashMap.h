#ifndef ARM11_39_HASHMAP_H
#define ARM11_39_HASHMAP_H

#include "util/ListMap.h"

typedef struct HashMap {
    ListMap *buckets;
    int numBuckets;
} HashMap;

HashMap *HashMapInit(
        HashMap *this
);

HashMap *HashMapInitWithBuckets(
        HashMap *this,
        int numBuckets
);

HashMap *HashMapDeinit(
        HashMap *this,
        void (*deleter)(void *, void *)
);

void HashMapPut(
        HashMap *this,
        void *key,
        void *value,
        int (*hash)(void *),
        bool (*equals)(void *, void *)
);

void *HashMapGet(
        HashMap *this,
        void *key,
        int (*hash)(void *),
        bool (*equals)(void *, void *)
);

#endif //ARM11_39_HASHMAP_H
