//
// Created by drspaceship on 15/06/16.
//

#ifndef ARM11_39_VARIABLESTRUCT_H
#define ARM11_39_VARIABLESTRUCT_H


#include <stdint.h>
#include <stdbool.h>

typedef struct variable {
    uint32_t value;
    bool isPin;
    int controlShift;
    uint32_t updateMask;
} variable_t;

#endif //ARM11_39_VARIABLESTRUCT_H
