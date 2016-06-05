//
// Created by Shiraz Butt on 03/06/2016.
//

#ifndef ARM11_39_GENERICLISTMAPITERATOR_H
#define ARM11_39_GENERICLISTMAPITERATOR_H

#include <util/GenericListMapNode.h>

#define ListMap(K, V) ___ListMap__##K__##V

#define ListMapIterator(K, V) ListMap(K, V)___Iterator

#define ListMapIteratorInitWithListMap(K, V) ListMapIterator(K, V)___InitWithListMap

#define ListMapIteratorDeinit(K, V) ListMapIterator(K, V)___Deinit

#define ListMapIteratorNext(K, V) ListMapIterator(K, V)___Next

#define INCL_LISTMAP_ITERATOR(K, V) \
 \
struct ListMap(K, V); \
 \
typedef struct ListMapIterator(K, V) { \
    ListMapNode(K, V) *current; \
    ListMapNode(K, V) *next; \
} ListMapIterator(K, V); \
 \
ListMapIterator(K, V) *ListMapIteratorInitWithListMap(K, V) ( \
        ListMapIterator(K, V) *this, \
        struct ListMap(K, V) *listMap \
); \
 \
ListMapIterator(K, V) *ListMapIteratorDeinit(K, V) ( \
        ListMapIterator(K, V) *this \
); \
ListMapNode(K, V) *ListMapIteratorNext(K, V) ( \
        ListMapIterator(K, V) *this \
);

#define GEN_LISTMAP_ITERATOR(K, V) \
INCL_LISTMAP_ITERATOR(K, V) \
ListMapIterator(K, V) *ListMapIteratorInitWithListMap(K, V)( \
        ListMapIterator(K, V) *this, \
        struct ListMap(K, V) *listMap \
) { \
    assert(listMap != NULL); \
    this->current = listMap->first; \
    this->currentPtr = &listMap->first; \
    if (this->current != NULL) { \
        this->next = this->current->next; \
    } \
    return this; \
} \
 \
ListMapIterator(K, V) *ListMapIteratorDeinit(K, V)( \
        ListMapIterator(K, V) *this \
) { \
    return this; \
} \
 \
ListMapNode(K, V) *ListMapIteratorNext(K, V)( \
        ListMapIterator(K, V) *this \
)  { \
    ListMapNode(K, V) *ret = this->current; \
    if (ret == NULL) { \
        return ret; \
    } \
    this->current = ret->next; \
    this->currentPtr = &ret->next; \
    return ret; \
}

#endif //ARM11_39_GENERICLISTMAPITERATOR_H
