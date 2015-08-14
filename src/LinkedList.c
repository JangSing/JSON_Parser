#include "ErrorObject.h"
#include "CException.h"
#include "compareFunction.h"
#include "createTokenType.h"
#include "FindElementFunction.h"
#include "IteratorFunction.h"
#include "JSON.h"
#include "LinkedList.h"
#include "Token.h"
#include "CustomAssertion.h"

#include <malloc.h>
#include <stdio.h>
#include <assert.h>

LinkedList *createLinkedList(){
  LinkedList *list;
  list = malloc(sizeof(LinkedList));
  assert(list != NULL);

  list-> head   = NULL;
  list-> tail   = NULL;
  list-> length = 0;
  list-> state  = WAIT_FOR_TOKEN;

  return list;
}

ListElement *createListElement(void *value){

  ListElement *newNode= malloc(sizeof(ListElement));
  assert(newNode != NULL);
  if(value==NULL)
    return NULL;
  newNode -> value = value;
  newNode -> next = NULL;

  return newNode;
}

void addLast(ListElement *newEle,LinkedList *list ){

  Iterator *iter;

  if(newEle==NULL || list==NULL){}

  else {
    iter=createIterator(list);
    if(iter->current == NULL){
      list->head=newEle;
      list->tail=list->head;
    }
    else{
      iter->current=list->tail;
      iter=iteratorGetNext(iter);
      iter->current=newEle;
      list->tail->next=iter->current;
      list->tail=list->tail->next;
    }
    (list->length)++;
  }
}


