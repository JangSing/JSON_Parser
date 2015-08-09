#ifndef FindElementFunction_H
#define FindElementFunction_H

#include "Token.h"
#include "LinkedList.h"

ListElement *listFind(LinkedList *list,void *value, int(*compare)(void *,void *));
ListElement *keyFind(LinkedList *list, void *key, int(*compare)(void *,void *));
Token *getElementValue(ListElement *findKey);

#endif // FindElementFunction_H
