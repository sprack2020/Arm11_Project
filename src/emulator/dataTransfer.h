#ifndef ARM11_39_DATATRANSFER_H
#define ARM11_39_DATATRANSFER_H

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <emulate.h>
#include <emulator/getOperand2.h>
#include <util/util.h>

#define REG_LENGTH 32
#define MEM_LENGTH 8
#define MAX_PIN 29
#define CONTROL_PORT_WIDTH 10

typedef enum {
    NOTGPIO = 0,
    CONTROL0_9 = 0x20200000,
    CONTROL10_19 = 0x20200004,
    CONTROL20_29 = 0x20200008,
    CLEAR_PORTS  = 0x20200028,
    ON_PORTS  = 0x2020001c
} GPIOAddressType;

void dataTransfer(uint32_t instr);

#endif //ARM11_39_DATATRANSFER_H
