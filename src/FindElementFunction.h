#ifndef FindElementFunction_H
#define FindElementFunction_H

#include "Token.h"
#include "LinkedList.h"

ListElement *listFind(LinkedList *list,void *value, int(*compare)(void *,void *));
ListElement *keyFind(LinkedList *list, void *value, int(*compare)(void *,void *));

#endif // FindElementFunction_H