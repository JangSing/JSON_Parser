#ifndef FindElementFunction_H
#define FindElementFunction_H

#include "Token.h"
#include "LinkedList.h"

ListElement *keyFind(LinkedList *list, void *key, int(*compare)(void *,void *));
Token *getElementValue(ListElement *findKey);

#endif // FindElementFunction_H
