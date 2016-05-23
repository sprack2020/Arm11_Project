//
// Created by drspaceship on 20/05/16.
//
#include <stdint.h>
#include <stdio.h>
#include "util.h"

#ifndef ARM11_39_BRANCH_H
#define ARM11_39_BRANCH_H
#endif //ARM11_39_BRANCH_H

#define OFFSET_SIZE 24
#define SHIFT_TO_OFFSET 2

void branch(uint32_t instr);
