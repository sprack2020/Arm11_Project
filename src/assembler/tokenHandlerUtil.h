#ifndef ARM11_39_TOKENHANDLERUTIL_H
#define ARM11_39_TOKENHANDLERUTIL_H

#include <stdbool.h>
#include <stdint.h>

#include <assembler/assemblerStruct.h>
#include <util/util.h>

#define PIPELINE_LENGTH 8
#define REG_FIELD_LENGTH 4

#define MAX_MOV_CONSTANT 0XFF

#include <util/util.h>

uint32_t handleOperand2(char **tokens, bool *imm);
int getLastOnePos(uint32_t num);
uint32_t generateShift(char **tokens);
bool hasNoRd(char *mnem);
bool hasNoRn(char *mnem);
CondCodes mnemToCondCode(char *mnem);
uint32_t getLabelAddress(Assembler *assembler, char *label);
uint32_t calcOffset(Assembler *assembler, uint32_t address, bool reduce);


#endif //ARM11_39_TOKENHANDLERUTIL_H
