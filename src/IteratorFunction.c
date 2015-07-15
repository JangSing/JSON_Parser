#include "IteratorFunction.h"
#include "LinkedList.h"

#include <malloc.h>
#include <stdio.h>
#include <assert.h>

Iterator *createIterator(LinkedList *list){
  Iterator *iter=malloc(sizeof(Iterator));

  if(list==NULL){
    return NULL;
  }
  else{
    iter->current=list->head;
    return iter;
  }
}

Iterator *iteratorGetNext(Iterator *iter){
  iter->current=iter->current->next;
  return iter;
}