#ifndef IteratorFunction_H
#define IteratorFunction_H

#include "LinkedList.h"

typedef struct {
   ListElement *current;
} Iterator;

Iterator *createIterator(LinkedList *list);
Iterator *iteratorGetNext(Iterator *iter);

#endif // IteratorFunction_H
