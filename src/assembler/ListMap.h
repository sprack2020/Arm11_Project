//
// Created by drspaceship on 30/05/16.
//
#ifndef ARM11_39_LISTMAP_H
#define ARM11_39_LISTMAP_H

#include <stdbool.h>

#define NULL (void *)0

#define GEN_LISTMAP(K, V) \
\
typedef struct ListMap { \
    K key; \
    V val; \
} ListMap;\
\
\
ListMap *newListMap() {\
    ListMap *map = malloc(sizeof(ListMap)); \
    ListMap_init(map); \
\
    return map; \
} \

typedef struct ListMapNode {
    void *key;
    void *value;
    struct ListMapNode *next;
} ListMapNode;

typedef struct ListMap {
    ListMapNode *first;
} ListMap;

ListMap *newListMap(void);
ListMapNode *newListMapNode(void);
bool hasNext(ListMapNode *this);
ListMapNode *getNext(ListMapNode *this);
void delete(ListMap *this, void *key);
void add(ListMap *this, void *key, void *value);
void *get(ListMap *this, void *key);


#endif //ARM11_39_LISTMAP_H
