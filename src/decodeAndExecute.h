//
// Created by drspaceship on 20/05/16.
//
#ifndef ARM11_39_DECODEANDEXECUTE_H
#define ARM11_39_DECODEANDEXECUTE_H


#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>
#include "util.h"
#include "branch.h"
#include "dataProcess.h"
#include "iMultiply.h"
#include "dataTransfer.h"
#include "emulate.h"


#define PATTERN_UPPER 31
#define PATTERN_LOWER 28
#define MUL_PATTERN 1001
#define bit25 1

void decodeAndExecute(uint32_t instr);


#endif //ARM11_39_DECODEANDEXECUTE_H
