#ifndef ARM11_39_LISTMAPITERATOR_H
#define ARM11_39_LISTMAPITERATOR_H

#include <stddef.h>
#include "ListMapNode.h"

struct ListMap;

typedef struct ListMapIterator {
    ListMapNode **currentPtr;
    ListMapNode *current;
    ListMapNode *next;
} ListMapIterator;

ListMapIterator *ListMapIteratorInitWithListMap(
        ListMapIterator *this,
        struct ListMap *listMap
);

ListMapIterator *ListMapIteratorDeinit(
        ListMapIterator *this
);

ListMapNode *ListMapIteratorNext(
        ListMapIterator *this
);

#endif //ARM11_39_LISTMAPITERATOR_H
