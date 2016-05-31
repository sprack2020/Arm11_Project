//
// Created by drspaceship on 30/05/16.
//

#ifndef ARM11_39_LISTMAPNODE_H
#define ARM11_39_LISTMAPNODE_H

#include <stdbool.h>

typedef struct ListMapNode {
    void *key;
    void *value;
    struct ListMapNode *next;
} ListMapNode;

ListMapNode *ListMapNodeNewWithKV(
        void *key,
        void *value
);

ListMapNode *ListMapNodeInitWithKV(
        ListMapNode *this,
        void *key,
        void *value
);

void ListMapNodeDelete(
        ListMapNode *this,
        void (*deleter)(void *, void *)
);

ListMapNode *ListMapNodeDeinit(
        ListMapNode *this,
        void (*deleter)(void *, void *)
);

#endif //ARM11_39_LISTMAPNODE_H
