//
// Created by drspaceship on 30/05/16.
//

#ifndef ARM11_39_LISTMAPTESTS_H
#define ARM11_39_LISTMAPTESTS_H

#include <string.h>
#include <util/ListMap.h>

#define TESTSTR "created by dr spaceship"
#define TESTINT 42

void ListMapTestInit(void);
void ListMapTestStringInt(void);

void itemNotInEmptyMap(void);
void retrieveItemIsSame(void);
void retrieveItemNotInserted(void);
void retrieveItemFromMultiple(void);


#endif //ARM11_39_LISTMAPTESTS_H
