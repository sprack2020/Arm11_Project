//
// Created by Shiraz Butt on 03/06/2016.
//

#ifndef ARM11_39_GENERICLISTMAP_H
#define ARM11_39_GENERICLISTMAP_H

#include <util/GenericListMapNode.h>
#include <util/GenericListMapIterator.h>

#define ListMap(K, V) ___ListMap__##K__##V

#define ListMapInit(K, V) ListMap(K, V)___Init

#define ListMapDeinit(K, V) ListMap(K, V)___Deinit

#define ListMapGetIterator(K, V) ListMap(K, V)___GetIterator

#define ListMapAdd(K, V) ListMap(K, V)___Add

#define ListMapGet(K, V) ListMap(K, V)___Get

#define GEN_LISTMAP(K, V) \
 \
GEN_LISTMAP_NODE(K, V) \
 \
INCL_LISTMAP_ITERATOR(K, V) \
 \
INCL_LISTMAP(K, V) \
 \
typedef struct ListMap(K, V) {\
    ListMapNode(K, V) *first;\
} ListMap(K, V);\
\
/* initialise a list map */ \
ListMap(K, V) *ListMap(K, V)___Init(ListMap(K, V) *this) {\
    this->first = NULL;\
    return this;\
}\
\
/* takes a deleter function pointer and deletes the nodes from first to last*/\
ListMap(K, V) *ListMap(K, V)___Deinit(\
        ListMap(K, V) *this,\
        void (*deleter)(K *key, V *value)\
) {\
    assert(this != NULL);\
    ListMapIterator(K, V) it = ListMapGetIterator_##K##V(this);\
    ListMapNode_##K##V *curr;\
    while ((curr = ListMapIteratorNext_##K##V(&it)) != NULL) {\
        ListMapNodeDelete_##K##V(curr, deleter);\
    }\
    return this;\
}\
\
ListMapIterator_##K##V ListMapGetIterator_##K##V(ListMap_##K##V *this) {\
    assert(this != NULL);\
    ListMapIterator_##K##V it;\
    ListMapIteratorInitWithListMap_##K##V(&it, this);\
    return it;\
}\
\
void ListMapAdd_##K##V(\
        ListMap_##K##V *this,\
        K *key,\
        V *value\
) {\
    assert(this != NULL);\
    ListMapNode_##K##V *newNode = ListMapNodeNewWithKV_##K##V(key, value);\
    newNode->next = this->first;\
    this->first = newNode;\
}\
\
void *ListMapGet_##K##V(\
        ListMap_##K##V *this,\
        K *key,\
        bool (*equals)(K *, K *)\
) {\
    assert(this != NULL);\
\
    ListMapIterator_##K##V it = ListMapGetIterator_##K##V(this);\
    ListMapNode_##K##V *curr;\
\
    while ((curr = ListMapIteratorNext_##K##V(&it)) != NULL) {\
        if (equals(curr->key, key)) {\
            return curr->value;\
        }\
    }\
\
    return NULL;\
} \
\
GEN_LISTMAP_ITERATOR(K, V)

#endif //ARM11_39_GENERICLISTMAP_H
