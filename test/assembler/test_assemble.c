//
// Created by drspaceship on 30/05/16.
//

#include <stdio.h>
#include "ListMapTests.h"

int main(int argc, char **argv) {
    ListMapTestInit();
    ListMapTestStringInt();
    itemNotInEmptyMap();
    retrieveItemIsSame();
    retrieveItemFromMultiple();

    exit(EXIT_SUCCESS);
}
