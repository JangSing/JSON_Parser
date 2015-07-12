#ifndef LinkedList_H
#define LinkedList_H

#include "Token.h"

typedef enum{
  WAIT_FOR_TOKEN,
  OBJECT,
  WAIT_FOR_COLON,
  VALUE,
  ARRAY,
  NUMBER,
  STRING,
  END_OR_CON,
  END,
  WAIT_FOR_OPERATOR,
  ERROR,
}JsonState;

typedef struct ListElement_t{
  struct ListElement_t *next;
  void *value;
}ListElement;

typedef struct {
  ListElement *head;
  ListElement *tail;
  int length;
  JsonState state;
}LinkedList;

typedef struct {
   ListElement *current;
} Iterator;


LinkedList *createLinkedList();
ListElement *createListElement(void *value);

//*** Adding Element function start here ***\\

void AddLast(ListElement *NewEle,LinkedList *List );
void AddFirst(LinkedList *stack,ListElement *NewElem);

//*** Removing Element function start here ***\\

ListElement *RemoveFirst(LinkedList *stack);
ListElement *RemoveLast(LinkedList *List);

//*** Find Element function start here ***\\

ListElement *listFind(LinkedList *list,void *value, int(*compare)(void *,void *));
ListElement *KeyFind(LinkedList *list, void *value, int(*compare)(void *,void *));
int intCompare(void *first, void *second);
int strCompare(void *first, void *second);


Iterator *createIterator(LinkedList *list); 
Iterator *iteratorGetNext(Iterator *iter);



#endif // LinkedList_H
