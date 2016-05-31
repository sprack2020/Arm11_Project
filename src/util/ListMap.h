//
// Created by drspaceship on 30/05/16.
//
#ifndef ARM11_39_LISTMAP_H
#define ARM11_39_LISTMAP_H

#include <assert.h>
#include <errno.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "ListMapNode.h"
#include "ListMapIterator.h"

typedef struct ListMap {
    ListMapNode *first;
} ListMap;

ListMap *ListMapInit(ListMap *this);
ListMap *ListMapDeinit(
        ListMap *this,
        void (*deleter)(void *key, void *value)
);

ListMapIterator ListMapGetIterator(ListMap *this);

void ListMapAdd(
        ListMap *this,
        void *key,
        void *value
);
void *ListMapGet(
        ListMap *this,
        void *key,
        bool (*equals)(void *, void *)
);

#endif //ARM11_39_LISTMAP_H
