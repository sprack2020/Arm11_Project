#include "ListMapIterator.h"
#include "ListMap.h"

ListMapIterator *ListMapIteratorInitWithListMap(
        ListMapIterator *this,
        ListMap *listMap
) {
    assert(listMap != NULL);
    this->current = listMap->first;
    this->currentPtr = &listMap->first;
    if (this->current != NULL) {
        this->next = this->current->next;
    }
    return this;
}

ListMapIterator *ListMapIteratorDeinit(
        ListMapIterator *this
) {
    return this;
}

ListMapNode *ListMapIteratorNext(
        ListMapIterator *this
)  {
    ListMapNode *ret = this->current;
    if (ret == NULL) {
        return ret;
    }
    this->current = ret->next;
    this->currentPtr = &ret->next;
    return ret;
}
