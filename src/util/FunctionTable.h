//
// Created by Shiraz Butt on 03/06/2016.
//

#ifndef ARM11_39_FUNCTIONTABLE_H
#define ARM11_39_FUNCTIONTABLE_H

#include <stdint.h>
#include <assembler/assemblerStruct.h>
#include <util/GenericListMap.h>
#include <util/GenericListMapNode.h>
#include <util/GenericListMapIterator.h>


typedef uint32_t (*instructionHandler)(Assembler *, char **);

//GEN_LISTMAP(char *, instructionHandler);

#endif //ARM11_39_FUNCTIONTABLE_H
