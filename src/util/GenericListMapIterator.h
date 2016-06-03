//
// Created by Shiraz Butt on 03/06/2016.
//

#ifndef ARM11_39_GENERICLISTMAPITERATOR_H
#define ARM11_39_GENERICLISTMAPITERATOR_H

#define GEN_LISTMAP_ITERATOR_H(K, V)
struct ListMap_##K##V;\
\
typedef struct ListMapIterator_##K##V {\
    ListMapNode_##K##V **currentPtr;\
    ListMapNode_##K##V *current;\
    ListMapNode_##K##V *next;\
} ListMapIterator_##K##V;\
\
ListMapIterator_##K##V *ListMapIteratorInitWithListMap_##K##V(\
        ListMapIterator_##K##V *this,\
        struct ListMap_##K##V *listMap\
);\
\
ListMapIterator_##K##V *ListMapIteratorDeinit_##K##V(\
        ListMapIterator_##K##V *this\
);\
\
ListMapNode_##K##V *ListMapIteratorNext_##K##V(\
        ListMapIterator_##K##V *this\
);\

#endif //ARM11_39_GENERICLISTMAPITERATOR_H
