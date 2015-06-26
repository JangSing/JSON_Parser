#ifndef LinkedList_H
#define LinkedList_H

#include "JSON.h"

typedef enum{
  WAIT_FOR_TOKEN,
  OBJECT,
  WAIT_FOR_OPERATOR2,
  VALUE,
  ARRAY,
  NUMBER,
  STRING,
  END_OR_CON,
  END,
  ERROR,
}ListState;


typedef struct ListElement_t{
  struct ListElement_t *next;
  int value;
}ListElement;

typedef struct {
  ListElement *head;
  ListElement *tail;
  int length;
  ListState state;
}LinkedList;

ListElement *createListElement(int value);

LinkedList *createLinkedList();

void addList(ListElement *NewEle,LinkedList *List );

void stackAdd(LinkedList *stack,ListElement *NewElem);

ListElement *stackRemove(LinkedList *stack);

ListElement *RemoveLast(LinkedList *List);

LinkedList *DetermineState();

#endif // LinkedList_H
