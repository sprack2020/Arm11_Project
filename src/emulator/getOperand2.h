//
// Created by drspaceship on 23/05/16.
//
#ifndef ARM11_39_GETOPERAND2_H
#define ARM11_39_GETOPERAND2_H

#include <stdint.h>
#include <stdbool.h>
#include "util/util.h"
#include "updateCPSR.h"
#include "emulate.h"


ShiftResult getOperand2(uint32_t instr, bool immediate);



#endif //ARM11_39_GETOPERAND2_H
