#ifndef ARM11_39_PRINTSTATE_H
#define ARM11_39_PRINTSTATE_H

#include <string.h>
#include "emulate.h"

#define LAST_GENERAL_REGISTER 12
#define HEX_PADDING 8
#define MAX_INT_PRINTING_SPACE 10
#define LONGEST_REGISTER_NAME "CPSR"
#define MEM_PRINTING_INTERVAL 4

void printState(void);


#endif //ARM11_39_PRINTSTATE_H
