#include "unity.h"
#include "mock_Token.h"
#include "ErrorObject.h"
#include "CException.h"
#include "compareFunction.h"
#include "createTokenType.h"
#include "FindElementFunction.h"
#include "IteratorFunction.h"
#include "JSON.h"
#include "LinkedList.h"
#include "CustomAssertion.h"

#include <malloc.h>
#include <stdio.h>
#include <assert.h>

void setUp(void)
{
}

void tearDown(void)
{
}

/**
 * Testing function LinkedList.
 *
 *    ptr---+-->head-----+
 *          |            |
 *          +-->tail-----+
 *                       |
 *                       v
 *                      NULL
 */
void test_function_createLinkedList()
{
  LinkedList *ptr;
  ptr = createLinkedList();

  TEST_ASSERT_NOT_NULL(ptr);
  TEST_ASSERT_NULL(ptr->head);
  TEST_ASSERT_NULL(ptr->tail);
  TEST_ASSERT_EQUAL(0,ptr->length);
}

/**
 * Testing function createListElement.
 *            ___________
 *   ptr---->|  value   |
 *           |__________|---->NULL
 *
 */


void test_function_createListElement_for_NULL_value_should_return_NULL()
{
  ListElement *newNode;
  int value=1;

  newNode = createListElement(NULL);

  TEST_ASSERT_NULL(newNode);
}

void test_function_createListElement_for_Integer_value()
{
  ListElement *newNode;
  int value=1;

  newNode = createListElement(&value);

  TEST_ASSERT_NOT_NULL(newNode);
  TEST_ASSERT_NOT_NULL(newNode->value);
  TEST_ASSERT_EQUAL(1,*(int *)newNode->value);
  TEST_ASSERT_NULL(newNode->next);
}

void test_function_createListElement_for_String_value()
{
  ListElement *newNode;
  char *value="JangSing";

  newNode = createListElement(value);

  TEST_ASSERT_NOT_NULL(newNode);
  TEST_ASSERT_NOT_NULL(newNode->value);
  TEST_ASSERT_EQUAL_STRING("JangSing",(char *)newNode->value);
  TEST_ASSERT_NULL(newNode->next);
}

void test_function_createListElement_for_Token_value()
{
  ListElement *newNode;
  IntegerToken *intTok;

  intTok=(IntegerToken *)createIntegerToken(123);
  newNode = createListElement(intTok);

  TEST_ASSERT_NOT_NULL(newNode);
  TEST_ASSERT_NOT_NULL(newNode->value);

  TEST_ASSERT_EQUAL(123,intTok->value);

  TEST_ASSERT_EQUAL(123,((IntegerToken *)(newNode->value))->value);
  TEST_ASSERT_EQUAL(TOKEN_INTEGER_TYPE,((IntegerToken *)(newNode->value))->type);
}

void test_Adding_one_element_to_LinkedList_using_function_AddLast_and_AddFirst()
{
  int firstValue=1;
  int lastValue=5;

  LinkedList *addLastPtr;
  LinkedList *addFirstPtr;

  addLastPtr  = createLinkedList();
  addFirstPtr = createLinkedList();

  addLast(createListElement(&lastValue),addLastPtr);
  addFirst(addFirstPtr,createListElement(&firstValue));

  TEST_ASSERT_NOT_NULL(addLastPtr);
  TEST_ASSERT_NOT_NULL(addLastPtr->head);
  TEST_ASSERT_NOT_NULL(addLastPtr->tail);
  TEST_ASSERT_NOT_NULL(addFirstPtr);
  TEST_ASSERT_NOT_NULL(addFirstPtr->head);
  TEST_ASSERT_NOT_NULL(addFirstPtr->tail);

  //for add last function
  TEST_ASSERT_EQUAL(5,*((int *)(addLastPtr->head->value)));
  TEST_ASSERT_NULL(addLastPtr->head->next);
  TEST_ASSERT_EQUAL(5,*((int *)(addLastPtr->tail->value)));
  TEST_ASSERT_NULL(addLastPtr->tail->next);
  TEST_ASSERT_EQUAL(1,addLastPtr->length);

  //for add first function
  TEST_ASSERT_EQUAL(1,*((int *)(addFirstPtr->head->value)));
  TEST_ASSERT_NULL(addFirstPtr->head->next);
  TEST_ASSERT_EQUAL(1,*((int *)(addFirstPtr->tail->value)));
  TEST_ASSERT_NULL(addFirstPtr->tail->next);
  TEST_ASSERT_EQUAL(1,addFirstPtr->length);
}

void test_AddFirst_and_AddLast_given_Element_equal_NULL_Should_do_nothing()
{
  int i;
  int firstValue=1;
  int lastValue=3;

  LinkedList *addLastPtr;
  LinkedList *addFirstPtr;

  addFirstPtr=createLinkedList();
  addLastPtr=createLinkedList();

  addFirst(addFirstPtr,createListElement(&firstValue));
  addFirst(addFirstPtr,NULL);
  addFirst(addFirstPtr,createListElement(&lastValue));

  TEST_ASSERT_NOT_NULL(addFirstPtr);
  TEST_ASSERT_EQUAL(3,*((int *)(addFirstPtr->head->value)));
  TEST_ASSERT_EQUAL_PTR(addFirstPtr->tail,addFirstPtr->head->next);
  TEST_ASSERT_EQUAL(1,*((int *)(addFirstPtr->tail->value)));
  TEST_ASSERT_NULL(addFirstPtr->tail->next);
  TEST_ASSERT_EQUAL(2,addFirstPtr->length);

  addLast(createListElement(&firstValue),addLastPtr);
  addLast(NULL,addLastPtr);
  addLast(createListElement(&lastValue),addLastPtr);

  TEST_ASSERT_NOT_NULL(addLastPtr);
  TEST_ASSERT_EQUAL(1,*((int *)(addLastPtr->head->value)));
  TEST_ASSERT_EQUAL_PTR(addLastPtr->tail,addLastPtr->head->next);
  TEST_ASSERT_EQUAL(3,*((int *)(addLastPtr->tail->value)));
  TEST_ASSERT_NULL(addLastPtr->tail->next);
  TEST_ASSERT_EQUAL(2,addLastPtr->length);
}

void test_addLast_Function_for_no_List_Passing_in_Should_do_nothing()
{
  int value[]={1,2};

  LinkedList *ptr;
  ptr=createLinkedList();

  addLast(createListElement(&value[0]),NULL);
  addLast(createListElement(&value[1]),ptr);

  TEST_ASSERT_NOT_NULL(ptr);
  TEST_ASSERT_NOT_NULL(ptr->head);
  TEST_ASSERT_NOT_NULL(ptr->tail);

  TEST_ASSERT_EQUAL(2,*((int *)(ptr->head->value)));
  TEST_ASSERT_NULL(ptr->head->next);
  TEST_ASSERT_EQUAL(2,*((int *)(ptr->tail->value)));
  TEST_ASSERT_NULL(ptr->tail->next);
  TEST_ASSERT_EQUAL(1,ptr->length);
}

void test_addFirst_Function_for_no_List_Passing_in_Should_do_nothing()
{
  int value[]={1,2};

  LinkedList *ptr;
  ptr=createLinkedList();

  addFirst(NULL,createListElement(&value[0]));
  addFirst(ptr,createListElement(&value[1]));

  TEST_ASSERT_NOT_NULL(ptr);
  TEST_ASSERT_NOT_NULL(ptr->head);
  TEST_ASSERT_NOT_NULL(ptr->tail);

  TEST_ASSERT_EQUAL(2,*((int *)(ptr->head->value)));
  TEST_ASSERT_NULL(ptr->head->next);
  TEST_ASSERT_EQUAL(2,*((int *)(ptr->tail->value)));
  TEST_ASSERT_NULL(ptr->tail->next);
  TEST_ASSERT_EQUAL(1,ptr->length);
}

void test_Adding_two_element_to_LinkedList_using_function_AddLast()
{
  int i;
  int value[]={1,2};

  LinkedList *ptr;
  ptr=createLinkedList();

  for(i=0;i<2;i++){
    addLast(createListElement(&value[i]),ptr);
  }

  TEST_ASSERT_EQUAL(1,*((int *)(ptr->head->value)));
  TEST_ASSERT_NOT_NULL(ptr->head);
  TEST_ASSERT_NOT_NULL(ptr->tail);
  TEST_ASSERT_EQUAL_PTR(ptr->tail,ptr->head->next);
  TEST_ASSERT_EQUAL(2,*((int *)(ptr->tail->value)));
  TEST_ASSERT_NULL(ptr->tail->next);
  TEST_ASSERT_EQUAL(2,ptr->length);
}

void test_Adding_two_element_to_LinkedList_using_function_AddFirst()
{
  int i;
  int value[]={1,2};

  LinkedList *ptr;
  ptr=createLinkedList();

  for(i=0;i<2;i++){
    addFirst(ptr,createListElement(&value[i]));
  }

  TEST_ASSERT_NOT_NULL(ptr);
  TEST_ASSERT_EQUAL(2,*((int *)(ptr->head->value)));
  TEST_ASSERT_EQUAL_PTR(ptr->tail,ptr->head->next);
  TEST_ASSERT_EQUAL(1,*((int *)(ptr->tail->value)));
  TEST_ASSERT_NULL(ptr->tail->next);
  TEST_ASSERT_EQUAL(2,ptr->length);
}

void test_Adding_three_element_to_LinkedList_using_function_addLast()
{
  int i;
  int value[]={1,2,3};

  LinkedList *ptr;
  Iterator *iter;
  ptr=createLinkedList();

  for(i=0;i<3;i++){
    addLast(createListElement(&value[i]),ptr);
  }

  TEST_ASSERT_NOT_NULL(ptr);
  iter=createIterator(ptr);
  TEST_ASSERT_EQUAL(*((int *)(ptr->head->value)),*((int *)(iter->current->value)));
  TEST_ASSERT_EQUAL(1,*((int *)(iter->current->value)));
  iter=iteratorGetNext(iter);
  TEST_ASSERT_EQUAL(2,*((int *)(iter->current->value)));
  iter=iteratorGetNext(iter);
  TEST_ASSERT_EQUAL(*((int *)(ptr->tail->value)),*((int *)(iter->current->value)));
  TEST_ASSERT_EQUAL(3,*((int *)(iter->current->value)));
  iter=iteratorGetNext(iter);
  TEST_ASSERT_NULL(iter->current);
  TEST_ASSERT_EQUAL(3,ptr->length);
}


void test_Adding_three_element_to_LinkedList_using_function_AddFirst()
{
  int i;
  int value[]={1,2,3};

  LinkedList *ptr;
  Iterator *iter;
  ptr=createLinkedList();

  for(i=0;i<3;i++){
    addFirst(ptr,createListElement(&value[i]));
  }

  TEST_ASSERT_NOT_NULL(ptr);
  iter=createIterator(ptr);
  TEST_ASSERT_EQUAL(*((int *)(ptr->head->value)),*((int *)(iter->current->value)));
  TEST_ASSERT_EQUAL(3,*((int *)(iter->current->value)));
  iter=iteratorGetNext(iter);
  TEST_ASSERT_EQUAL(2,*((int *)(iter->current->value)));
  iter=iteratorGetNext(iter);
  TEST_ASSERT_EQUAL(*((int *)(ptr->tail->value)),*((int *)(iter->current->value)));
  TEST_ASSERT_EQUAL(1,*((int *)(iter->current->value)));
  iter=iteratorGetNext(iter);
  TEST_ASSERT_NULL(iter->current);
  TEST_ASSERT_EQUAL(3,ptr->length);
}




void test_Five_Element_Added_to_the_List_using_AddLast()
{
  int i;
  int value[]={95,100,14,111,123};

  LinkedList *ptr;
  Iterator *iter;
  ptr = createLinkedList();

  for(i=0;i<5;i++){
    addLast(createListElement(&value[i]),ptr);
  }

  TEST_ASSERT_NOT_NULL(ptr);
  iter=createIterator(ptr);
  TEST_ASSERT_EQUAL(95 		, *((int *)(iter->current->value)));
  iter=iteratorGetNext(iter);
  TEST_ASSERT_EQUAL(100		, *((int *)(iter->current->value)));
  iter=iteratorGetNext(iter);
  TEST_ASSERT_EQUAL(14		, *((int *)(iter->current->value)));
  iter=iteratorGetNext(iter);
  TEST_ASSERT_EQUAL(111		, *((int *)(iter->current->value)));
  iter=iteratorGetNext(iter);
  TEST_ASSERT_EQUAL(123		, *((int *)(iter->current->value)));
  iter=iteratorGetNext(iter);
  TEST_ASSERT_NULL(iter->current);
  TEST_ASSERT_EQUAL(5,ptr->length);
}

void test_AddFirst_adding_five_element_into_LinkedList()
{
  int i;
  int value[]={95,100,14,111,123};

  LinkedList *ptr;
  Iterator *iter;
  ptr=createLinkedList();

  for(i=0;i<5;i++){
    addFirst(ptr,createListElement(&value[i]));
  }

  TEST_ASSERT_NOT_NULL(ptr);
  iter=createIterator(ptr);
  TEST_ASSERT_EQUAL(123,*((int *)(iter->current->value)));
  iter=iteratorGetNext(iter);
  TEST_ASSERT_EQUAL(111,*((int *)(iter->current->value)));
  iter=iteratorGetNext(iter);
  TEST_ASSERT_EQUAL(14,*((int *)(iter->current->value)));
  iter=iteratorGetNext(iter);
  TEST_ASSERT_EQUAL(100,*((int *)(iter->current->value)));
  iter=iteratorGetNext(iter);
  TEST_ASSERT_EQUAL(95,*((int *)(iter->current->value)));
  iter=iteratorGetNext(iter);
  TEST_ASSERT_NULL(iter->current);
  TEST_ASSERT_EQUAL(5,ptr->length);
}

// Testing function removeFirst when there are no element in LinkedList.
void test_removeFirst_given_no_element_in_LinkedList_should_remove_nothing()
{
  LinkedList *ptr;
  ListElement *removedEle;

  ptr=createLinkedList();
  removedEle=removeFirst(ptr);

  TEST_ASSERT_NULL(removedEle);
  TEST_ASSERT_NULL(ptr->head);
  TEST_ASSERT_NULL(ptr->tail);
}

// Testing function removeLast when there are no element in LinkedList.
void test_RemoveLast_given_no_element_in_LinkedList_should_remove_nothing()
{
  LinkedList *ptr;
  ListElement *removedEle;

  ptr=createLinkedList();
  removedEle=removeLast(ptr);

  TEST_ASSERT_NULL(removedEle);
  TEST_ASSERT_NULL(ptr->head);
  TEST_ASSERT_NULL(ptr->tail);
}

void test_RemoveFirst_given_one_element_in_LinkedList_should_remove_head_Element()
{
  int value=1;

  LinkedList *ptr;
  ListElement *removedEle;

  ptr=createLinkedList();
  addFirst(ptr,createListElement(&value));
  removedEle=removeFirst(ptr);

  TEST_ASSERT_NOT_NULL(ptr);
  TEST_ASSERT_EQUAL(1,*((int *)(removedEle->value)));
  TEST_ASSERT_NULL(removedEle->next);

  TEST_ASSERT_NULL(ptr->head);
  TEST_ASSERT_NULL(ptr->tail);
  TEST_ASSERT_EQUAL(0,ptr->length);
}

void test_RemoveLast_given_one_element_in_LinkedList_should_remove_last_Element()
{
  int value=1;

  LinkedList *ptr;
  ListElement *removedEle;

  ptr=createLinkedList();
  addFirst(ptr,createListElement(&value));
  removedEle=removeLast(ptr);

  TEST_ASSERT_NOT_NULL(ptr);
  TEST_ASSERT_EQUAL(1,*((int *)(removedEle->value)));
  TEST_ASSERT_NULL(removedEle->next);

  TEST_ASSERT_NULL(ptr->head);
  TEST_ASSERT_NULL(ptr->tail);
  TEST_ASSERT_EQUAL(0,ptr->length);
}

void test_RemoveFirst_given_three_element_in_LinkedList_should_return_removed_head_Element()
{
  int i;
  int value[]={1,2,3};

  LinkedList *ptr;
  ListElement *removedEle;
  Iterator *iter;

  ptr=createLinkedList();

  for(i=0;i<3;i++){
    addFirst(ptr,createListElement(&value[i]));
  }

  TEST_ASSERT_NOT_NULL(ptr);
  TEST_ASSERT_EQUAL(3,ptr->length);

  removedEle=removeFirst(ptr);

  TEST_ASSERT_EQUAL(3,*((int *)(removedEle->value)));
  TEST_ASSERT_NULL(removedEle->next);

  //the LinkedList after removing
  iter=createIterator(ptr);
  TEST_ASSERT_EQUAL(2,*((int *)(iter->current->value)));
  iter=iteratorGetNext(iter);
  TEST_ASSERT_EQUAL(1,*((int *)(iter->current->value)));
  iter=iteratorGetNext(iter);
  TEST_ASSERT_NULL(iter->current);
  TEST_ASSERT_EQUAL(2,ptr->length);
}

void test_RemoveLast_given_three_element_in_LinkedList_should_return_removed_last_Element()
{
  int i;
  int value[]={1,2,3};

  LinkedList *ptr;
  ListElement *removedEle;
  Iterator *iter;

  ptr=createLinkedList();

  for(i=0;i<3;i++){
    addFirst(ptr,createListElement(&value[i]));
  }

  TEST_ASSERT_NOT_NULL(ptr);
  TEST_ASSERT_EQUAL(3,ptr->length);

  removedEle=removeLast(ptr);

  TEST_ASSERT_EQUAL(1,*((int *)(removedEle->value)));
  TEST_ASSERT_NULL(removedEle->next);

  //the LinkedList after removing
  iter=createIterator(ptr);
  TEST_ASSERT_EQUAL(3,*((int *)(iter->current->value)));
  iter=iteratorGetNext(iter);
  TEST_ASSERT_EQUAL(2,*((int *)(iter->current->value)));
  iter=iteratorGetNext(iter);
  TEST_ASSERT_NULL(iter->current);
  TEST_ASSERT_EQUAL(2,ptr->length);
}

void test_All_function_in_one_single_LinkedList()
{
  int value[]={1,2,3,4,5,6};

  LinkedList *ptr;
  ListElement *remLast;
  ListElement *remFirst;
  Iterator *iter,*newIter;

  ptr=createLinkedList();

  addLast(createListElement(&value[0]),ptr);
  addLast(createListElement(&value[1]),ptr);
  addFirst(ptr,createListElement(&value[2]));
  addLast(createListElement(&value[3]),ptr);
  addFirst(ptr,createListElement(&value[4]));

  TEST_ASSERT_NOT_NULL(ptr);
  iter=createIterator(ptr);
  TEST_ASSERT_EQUAL(5,*((int *)(iter->current->value)));
  iter=iteratorGetNext(iter);
  TEST_ASSERT_EQUAL(3,*((int *)(iter->current->value)));
  iter=iteratorGetNext(iter);
  TEST_ASSERT_EQUAL(1,*((int *)(iter->current->value)));
  iter=iteratorGetNext(iter);
  TEST_ASSERT_EQUAL(2,*((int *)(iter->current->value)));
  iter=iteratorGetNext(iter);
  TEST_ASSERT_EQUAL(4,*((int *)(iter->current->value)));
  iter=iteratorGetNext(iter);
  TEST_ASSERT_NULL(iter->current);
  TEST_ASSERT_EQUAL(5,ptr->length);

  //removing last element in the LinkedList
  remLast=removeLast(ptr);

  TEST_ASSERT_EQUAL(4,*((int *)(remLast->value)));
  TEST_ASSERT_EQUAL(2,*((int *)(ptr->tail->value)));
  TEST_ASSERT_NULL(ptr->tail->next);
  TEST_ASSERT_EQUAL(4,ptr->length);

  //removing First element in the LinkedList
  remFirst=removeFirst(ptr);

  TEST_ASSERT_EQUAL(5,*((int *)(remFirst->value)));
  TEST_ASSERT_EQUAL(3,*((int *)(ptr->head->value)));
  TEST_ASSERT_EQUAL(3,ptr->length);

  //adding element to the tail of the LinkedList
  addLast(createListElement(&value[5]),ptr);

  newIter=createIterator(ptr);
  TEST_ASSERT_EQUAL(3,*((int *)(newIter->current->value)));
  newIter=iteratorGetNext(newIter);
  TEST_ASSERT_EQUAL(1,*((int *)(newIter->current->value)));
  newIter=iteratorGetNext(newIter);
  TEST_ASSERT_EQUAL(2,*((int *)(newIter->current->value)));
  newIter=iteratorGetNext(newIter);
  TEST_ASSERT_EQUAL(6,*((int *)(newIter->current->value)));
  newIter=iteratorGetNext(newIter);
  TEST_ASSERT_NULL(newIter->current);
  TEST_ASSERT_EQUAL(4,ptr->length);
}





