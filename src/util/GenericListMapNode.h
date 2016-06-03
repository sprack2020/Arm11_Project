//
// Created by Shiraz Butt on 03/06/2016.
//

#ifndef ARM11_39_GENERICLISTMAP_H
#define ARM11_39_GENERICLISTMAP_H

#define GEN_LISTMAP_NODE_H(K, V)\
typedef struct ListMapNode_##K##V {\
    K *key;\
    V *value;\
    struct ListMapNode *next;\
} ListMapNode_##K##V;\
\
ListMapNode_##K##V *ListMapNodeNewWithKV_##K##V(\
        K *key,\
        V *value\
);\
\
ListMapNode_##K##V *ListMapNodeInitWithKV_##K##V(\
        ListMapNode_##K##V *this,\
        K *key,\
        V *value\
);\
\
void ListMapNodeDelete_##K##V(\
        ListMapNode_##K##V *this,\
        void (*deleter)(K *, V *)\
);\
\
ListMapNode *ListMapNodeDeinit_##K##V(\
        ListMapNode_##K##V *this,\
        void (*deleter)(K *, V *)\
);\

#endif //ARM11_39_GENERICLISTMAP_H
