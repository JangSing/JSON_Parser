#include "FindElementFunction.h"
#include "LinkedList.h"
#include "Token.h"
#include "compareFunction.h"
#include "IteratorFunction.h"

#include <malloc.h>
#include <stdio.h>
#include <assert.h>

//*** Find Element function start here ***
ListElement *listFind(LinkedList *list, void *value, int(*compare)(void *,void *)){
  if(list==NULL){
    return NULL;
  }
  else{
    ListElement *ptr;
    ptr=list->head;

    if(value==NULL || (compare(ptr ->value , value)==-1)){
      return NULL;
    }

    else{
      //if they are not the same then continue looping
      while (compare(ptr ->value , value)==1){
        ptr =ptr->next;

        if(ptr==NULL){
          return NULL;
        }
      }
      return ptr;
    }
  }
}

ListElement *keyFind(LinkedList *list, void *value, int(*compare)(void *,void *)){
  if(list==NULL){
    return NULL;
  }
  else{
    ListElement *ptr;
    ptr=list->head;

    if(value==NULL || (compare(ptr ->value , value)==-1)){
      return NULL;
    }

    else{
      ptr=ptr->next;
      //if they are not the same then continue looping
      while (compare(((IdentifierToken *)(((OperatorToken *)(ptr ->value))->token[0]))->name , value)==1){
        ptr =ptr->next;
        if (ptr==NULL){
          return ptr;
        }
        if((((OperatorToken *)(ptr ->value))->token[0])==NULL){
          ptr=ptr->next;
        }
      }
      return ptr;
    }
  }
}