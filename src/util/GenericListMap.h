//
// Created by Shiraz Butt on 03/06/2016.
//

#ifndef ARM11_39_GENERICLISTMAP_H
#define ARM11_39_GENERICLISTMAP_H

#define GEN_LIST_MAP_H(K, V) \
typedef struct ListMap_##K##V {\
    ListMapNode_##K##V *first;\
} ListMap_##K##V;\
\
ListMap_##K##V *ListMapInit_##K##V(ListMap_##K##V *this);\
\
ListMap_##K##V *ListMapDeinit_##K##V(\
        ListMap_##K##V *this,\
        void (*deleter)(K *key, V *value)\
);\
\
ListMapIterator_##K##V ListMapGetIterator_##K##V(ListMap_##K##V *this);\
\
void ListMapAdd_##K##V(\
        ListMap_##K##V *this,\
        K *key,\
        V *value\
);\
void *ListMapGet_##K##V(\
        ListMap_##K##V *this,\
        K *key,\
        bool (*equals)(K *, K *)\
);\

#endif //ARM11_39_GENERICLISTMAP_H
