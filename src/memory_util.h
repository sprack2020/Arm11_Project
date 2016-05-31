//
// Created by drspaceship on 30/05/16.
//

#ifndef ARM11_39_MEMORY_UTIL_H
#define ARM11_39_MEMORY_UTIL_H

#define NEW(T)\
do {\
    void *this = malloc(sizeof(T));\
    if (this == NULL) {\
        fprintf(stderr, "failed to allocate\n");\
    }\
    T##Init((T *) this);\
} while (0)

#define DELETE(T, t)\
do {\
    free(T##Deinit(t));\
} while (0)

#endif //ARM11_39_MEMORY_UTIL_H
