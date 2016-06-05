//
// Created by Shiraz Butt on 03/06/2016.
//

#ifndef ARM11_39_GENERICLISTMAP_H
#define ARM11_39_GENERICLISTMAP_H

#define ListMapNode(K, V) ___ListMapNode__##K__##V

#define ListMapNodeNewWithKV(K, V) ListMapNode(K, V)___NewWithKV

#define ListMapNodeInitWithKV(K, V) ListMapNode(K, V)___InitWithKV

#define ListMapNodeDelete(K, V) ListMapNode(K, V)___Delete

#define ListMapNodeDeinit(K, V) ListMap(K, V)___Deinit

#define INCL_LISTMAP_NODE(K, V) \
 \
ListMapNode(K, V) *ListMapNodeNewWithKV(K, V)(K key, V value); \
 \
ListMapNode(K, V) *ListMapNodeInitWithKV(K, V)(\
        ListMapNode(K, V) *this,\
        K key,\
        V value;\
);\
\
void ListMapNodeDelete(K, V)(\
        ListMapNode(K, V) *this,\
        void (*deleter)(K *, V *)\
);\
\
ListMapNode(K, V) *ListMapNodeDeinit(K, V)(\
        ListMapNode(K, V) *this,\
        void (*deleter)(K *, V *)\
);

#define GEN_LISTMAP_NODE(K, V) \
INCL_LISTMAP_NODE(K, V) \
typedef struct ListMapNode(K, V) { \
    K key; \
    V value; \
    struct ListMapNode(K, V) *next; \
} ListMapNode(K, V); \
 \
/*generate a new node with a given key and value */ \
ListMapNode(K, V) *ListMapNodeNewWithKV(K, V)(K key, V value) { \
    ListMapNode(K, V) *this = malloc(sizeof(ListMapNode(K, V))); \
    assert(this != NULL); \
    return ListMapNodeInitWithKV(K, V)(this, key, value); \
} \
 \
/* initialise a node */ \
ListMapNode(K, V) *ListMapNodeInitWithKV(K, V)( \
        ListMapNode(K, V) *this, \
        K key, \
        V value; \
) { \
    this->key = key; \
    this->value = value; \
    this->next = NULL; \
    return this; \
} \
 \
/*use a deleter function to free memory for a node */ \
void ListMapNodeDelete(K, V)( \
        ListMapNode(K, V) *this, \
        void (*deleter)(K *, V *) \
) { \
    ListMapNodeDeinit_##K##V(this, deleter); \
    free(this); \
}\
\
ListMapNode(K, V) *ListMapNodeDeinit(K, V)( \
        ListMapNode(K, V) *this, \
        void (*deleter)(K *, V *) \
) { \
    if (deleter != NULL) { \
        deleter(&this->key, &this->value); \
    } \
    return this; \
}

#endif //ARM11_39_GENERICLISTMAP_H
