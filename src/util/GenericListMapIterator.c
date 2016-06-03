//
// Created by Shiraz Butt on 03/06/2016.
//

#include "GenericListMapIterator.h"

#define GEN_LISTMAP_ITERATOR(K, V)\
ListMapIterator_##K##V *ListMapIteratorInitWithListMap_##K##V (\
        ListMapIterator_##K##V *this,\
        ListMap_##K##V *listMap\
) {\
    assert(listMap != NULL);\
    this->current = listMap->first;\
    this->currentPtr = &listMap->first;\
    if (this->current != NULL) {\
        this->next = this->current->next;\
    }\
    return this;\
}\
\
ListMapIterator_##K##V *ListMapIteratorDeinit_##K##V (\
        ListMapIterator_##K##V *this\
) {\
    return this;\
}\
\
ListMapNode_##K##V *ListMapIteratorNext_##K##V (\
        ListMapIterator_##K##V *this\
)  {\
    ListMapNode_##K##V *ret = this->current;\
    if (ret == NULL) {\
        return ret;\
    }\
    this->current = ret->next;\
    this->currentPtr = &ret->next;\
    return ret;\
}