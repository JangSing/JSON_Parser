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