#ifndef ARM11_39_DECODEANDEXECUTE_H
#define ARM11_39_DECODEANDEXECUTE_H

#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>
#include <util/util.h>
#include <emulator/branch.h>
#include <emulator/dataProcess.h>
#include <emulator/iMultiply.h>
#include <emulator/dataTransfer.h>
#include <emulate.h>

#define PATTERN_UPPER 31
#define PATTERN_LOWER 28
#define MUL_PATTERN 0x9
#define bit25 1

bool decodeAndExecute(uint32_t instr);

#endif //ARM11_39_DECODEANDEXECUTE_H
