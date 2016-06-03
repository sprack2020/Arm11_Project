//
// Created by Shiraz Butt on 03/06/2016.
//

#include "GenericListMapNode.h"

#define GEN_LISTMAP_NODE(K, V)\
\
//generate a new node with a given key and value\
ListMapNode *ListMapNodeNewWithKV_##K##V(K *key, V *value) {\
    ListMapNode_##K##V *this = malloc(sizeof(ListMapNode_##K##V));\
    assert(this != NULL);\
    return ListMapNodeInitWithKV_##K##V(this, key, value);\
}\
\
//initialise a node\
ListMapNode *ListMapNodeInitWithKV_##K##V(\
        ListMapNode_##K##V *this,\
        K *key,\
        V *value;\
) {\
    this->key = key;\
    this->value = value;\
    this->next = NULL;\
    return this;\
}\
\
//use a deleter function to free memory for a node\
void ListMapNodeDelete_##K##V(\
        ListMapNode_##K##V *this,\
        void (*deleter)(void *, void *)\
) {\
    ListMapNodeDeinit_##K##V(this, deleter);\
    free(this);\
}\
\
ListMapNode_##K##V *ListMapNodeDeinit(\
        ListMapNode_##K##V *this,\
        void (*deleter)(void *, void *)\
) {\
    if (deleter != NULL) {\
        deleter(this->key, this->value);\
    }\
    return this;\
}