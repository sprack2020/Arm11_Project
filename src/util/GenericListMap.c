//
// Created by Shiraz Butt on 03/06/2016.
//

#include "GenericListMap.h"

#define GEN_LISTMAP_MAP(K, V) \
//initialise a list map\
ListMap_##K##V *ListMapInit_##K##V(ListMap_##K##V *this) {\
    this->first = NULL;\
    return this;\
}\
\
//takes a deleter function pointer and deletes the nodes from first to last\
ListMap_##K##V *ListMapDeinit_##K##V(\
        ListMap_##K##V *this,\
        void (*deleter)(K *key, V *value)\
) {\
    assert(this != NULL);\
    ListMapIterator_##K##V it = ListMapGetIterator_##K##V(this);\
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
}
