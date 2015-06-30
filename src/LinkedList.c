#include "LinkedList.h"

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

  ListElement *NewNode= malloc(sizeof(ListElement));
  assert(NewNode != NULL);

  NewNode -> value = value;
  NewNode -> next = NULL;

  return NewNode;
}

void AddLast(ListElement *NewEle,LinkedList *List ){

  if(List -> head == NULL && List -> tail == NULL){
    List -> head = NewEle;
    List -> tail = List -> head;
    (List->length)++;
  }
  else if(NewEle==NULL){}

  else {
    List -> tail->next=NewEle;
    List -> tail =List -> tail->next;
    (List->length)++;
  }
}

void AddFirst(LinkedList *stack,ListElement *NewElem){


  if(stack->head==NULL && stack->tail==NULL){
    stack->head=NewElem;
    stack->tail=stack->head;
    (stack->length)++;
  }
  else if(NewElem==NULL){}


  else{
    NewElem->next=stack->head;
    stack->head=NewElem;
    (stack->length)++;
  }
}

ListElement *RemoveFirst(LinkedList *stack){
  ListElement *ptr;

  if(stack->head==NULL && stack->tail==NULL){
    return NULL;
  }
  else if(stack->head->next==NULL){
    ptr=stack->head;
    stack->head=NULL;
    stack->tail=NULL;
    (stack->length)--;
  }
  else{
    ptr=stack->head;
    stack->head=stack->head->next;
    (stack->length)--;
  }

  ptr->next=NULL;
  return ptr;
}

ListElement *RemoveLast(LinkedList *List){
  ListElement *RemoveEle;
  ListElement *travel;

  if(List->head==NULL && List->tail==NULL){
    return NULL;
  }
  else if(List->head->next==NULL){
    RemoveEle=List->head;
    List->head=NULL;
    List->tail=NULL;
    (List->length)--;
  }
  else{
    travel=List->head;
    while (travel->next!=NULL){
      List->tail=travel;
      travel=travel->next;
    }
    RemoveEle=travel;
    List->tail->next=NULL;

    (List->length)--;
  }
  return RemoveEle;
}

//*** Find Element function start here ***\\

int intCompare(void *first, void *second){
  int *ptr=(int *)(first);
  int *ptr1=(int *)(second);

  if(*ptr==*ptr1){
    return 0;
  }
  else if(first==NULL||second==NULL){
    return -1;
  }
  else{
    return 1;
  }
}

int strCompare (void *first, void *second){

  char *ptr=(char *)(first);
  char *ptr1=(char *)(second);

  if(strcmp(ptr,ptr1)==0){
    return 0;
  }
  else if(first==NULL||second==NULL){
    return -1;
  }
  else{
    return 1;
  }

}

ListElement *listFind(LinkedList *list, void *value, int(*compare)(void *,void *)){
  ListElement *ptr;

  ptr=list->head;

  if(list==NULL || value==NULL||(compare(ptr ->value , value)==-1)){
    return NULL;
  }
  else{
    //if they the same then continue looping
    while (compare(ptr ->value , value)){
      ptr =ptr->next;
      if(ptr==NULL){
        return NULL;
      }
    }
    return ptr;
  }
}





