#ifndef LinkedList_H
#define LinkedList_H

#include "Token.h"

typedef enum{
  WAIT_FOR_TOKEN,
  OBJECT,
  WAIT_FOR_COLON,
  value,
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

//*** initialize LinkedList function start here***
LinkedList *createLinkedList();
ListElement *createListElement(void *value);

//*** Adding Element function start here ***
void addLast(ListElement *newEle,LinkedList *list );
void addFirst(LinkedList *list,ListElement *newElem);

//*** Removing Element function start here ***
ListElement *removeFirst(LinkedList *list);
ListElement *removeLast(LinkedList *list);


#endif // LinkedList_H
