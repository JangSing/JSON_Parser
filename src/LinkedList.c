#include "LinkedList.h"
#include "Token.h"
#include "compareFunction.h"
#include "IteratorFunction.h"
#include "FindElementFunction.h"

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

void addFirst(LinkedList *list,ListElement *newElem){

  if(newElem==NULL || list==NULL){}

  else{
    if(list->head==NULL && list->tail==NULL){
      list->head=newElem;
      list->tail=list->head;
    }
    else{
      newElem->next=list->head;
      list->head=newElem;
    }
    (list->length)++;
  }
}

ListElement *removeFirst(LinkedList *list){
  ListElement *remEle;

  if(list->head==NULL && list->tail==NULL){
    return NULL;
  }
  else{
    if(list->head->next==NULL){
      remEle=list->head;
      list->head=NULL;
      list->tail=NULL;
    }
    else{
      remEle=list->head;
      list->head=list->head->next;
    }
    (list->length)--;
  }
  remEle->next=NULL;
  return remEle;
}

ListElement *removeLast(LinkedList *list){
  ListElement *removeEle;
  ListElement *travel;

  if(list->head==NULL && list->tail==NULL){
    return NULL;
  }
  else{
    if(list->head->next==NULL){
      removeEle=list->head;
      list->head=NULL;
      list->tail=NULL;
    }
    else{
      travel=list->head;
      while (travel->next!=NULL){
        list->tail=travel;
        travel=travel->next;
      }
      removeEle=travel;
      list->tail->next=NULL;
    }
    (list->length)--;
  }
  return removeEle;
}






