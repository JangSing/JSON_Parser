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

/************************************************************************
 * Testing function createLinkedList.                                   *
 * -Initially the head and the tail are pointing to NULL.               *
 * -the starting length of the list has set to zero.                    *
 *                                                                      *
 *    list---+-->head-----+                                             *   
 *           |            |                                             *
 *           +-->tail-----+                                             *
 *                        |                                             *
 *                        v                                             *
 *                       NULL                                           *
 *                                                                      *
 ************************************************************************/
void test_function_createLinkedList()
{
  LinkedList *list;
  list = createLinkedList();

  TEST_ASSERT_NOT_NULL(list);
  TEST_ASSERT_NULL(list->head);
  TEST_ASSERT_NULL(list->tail);
  TEST_ASSERT_EQUAL(0,list->length);
}

/************************************************************************
 * Testing function createListElement given NULL value.                 *
 * -If the passing in address is NULL, the function will return NULL.   *
 *            ____________                                              *
 *           |  newNode  |                                              *
 *           -------------                                              *
 *   value   |    NULL   |                                              *
 *           -------------                                              *
 *           |   next    |---->NULL                                     *
 *           -------------                                              *
 *                                                                      *
 ************************************************************************/
void test_function_createListElement_given_NULL_value_should_return_NULL()
{
  ListElement *newNode;

  newNode = createListElement(NULL);

  TEST_ASSERT_NULL(newNode);
}

/************************************************************************
 * Testing function createListElement for any type of value.            *
 * -This function is able to pass in any type of value.                 *
 * -Initially the next pointer of the function is pointing to NULL.     *   
 *                         ____________                                 *
 *                        |  newNode  |                                 *
 *                        -------------                                 *
 *                        |   value   |                                 *
 *                        -------------                                 *
 *                        |   next    |---->NULL                        *
 *                        -------------                                 *
 *                                                                      *
 *                                                                      *
 *  For Integer Value,                                                  *
 *                         ____________                                 *
 *                        |  newNode  |                                 *
 *                        -------------                                 *
 *               value    |    1      |                                 *
 *                        -------------                                 *
 *                        |   next    |---->NULL                        *
 *                        -------------                                 * 
 *                                                                      *
 *                                                                      *
 *  For String Value,                                                   *
 *                         ____________                                 *
 *                        |  newNode  |                                 *
 *                        -------------                                 *
 *               value    |"JangSing" |                                 *
 *                        -------------                                 *
 *                        |   next    |---->NULL                        *
 *                        -------------                                 * 
 *                                                                      * 
 *                                                                      * 
 *  For Token Value,                                                    *
 *                         ____________                                 *
 *                        |  newNode  |                                 *
 *                        -------------                                 *
 *               value    |  Token    |                                 *
 *                        -------------                                 *
 *                        |   next    |---->NULL                        *
 *                        -------------                                 * 
 *                                                                      * 
 ************************************************************************/
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

/*********************************************************************************
 * Testing function addLast when one element added to the LinkedList.            *
 * -The addLast function will pass in the ListElement and the List.              *
 * -The function will add the Element to the tail of the List.                   *
 * -If either Element or List is pointing to NULL,the function will do nothing.  *
 *                                                                               *
 *                                   ___________                                 *
 *          list---+-->head-------->|  value=5 |                                 *
 *                 |                |__________|---->NULL                        *
 *                 |                    ^                                        *
 *                 |                    |                                        *
 *                 +-->tail-------------+                                        *
 *                                                                               *
 *********************************************************************************/           
void test_Adding_one_element_to_LinkedList_using_function_AddLast()
{
  int value=5;

  LinkedList *list;

  list  = createLinkedList();

  addLast(createListElement(&value),list);

  TEST_ASSERT_NOT_NULL(list);
  TEST_ASSERT_NOT_NULL(list->head);
  TEST_ASSERT_NOT_NULL(list->tail);

  TEST_ASSERT_EQUAL(5,*((int *)(list->head->value)));
  TEST_ASSERT_NULL(list->head->next);
  TEST_ASSERT_EQUAL(5,*((int *)(list->tail->value)));
  TEST_ASSERT_NULL(list->tail->next);
  TEST_ASSERT_EQUAL(1,list->length);
}

void test_addLast_Function_given_NULL_Element_Should_do_nothing()
{
  int i;
  int value1=1;
  int value2=2;

  LinkedList *list;
  
  list=createLinkedList();

  addLast(createListElement(&value1),list);
  addLast(NULL,list);
  addLast(createListElement(&value2),list);

  TEST_ASSERT_NOT_NULL(list);
  TEST_ASSERT_EQUAL(1,*((int *)(list->head->value)));
  TEST_ASSERT_EQUAL_PTR(list->tail,list->head->next);
  TEST_ASSERT_EQUAL(2,*((int *)(list->tail->value)));
  TEST_ASSERT_NULL(list->tail->next);
  TEST_ASSERT_EQUAL(2,list->length);
}

void test_addLast_Function_given_NULL_List_Should_do_nothing()
{
  int value[]={1,2};

  LinkedList *list;
  list=createLinkedList();

  addLast(createListElement(&value[0]),NULL);
  addLast(createListElement(&value[1]),list);

  TEST_ASSERT_NOT_NULL(list);
  TEST_ASSERT_NOT_NULL(list->head);
  TEST_ASSERT_NOT_NULL(list->tail);

  TEST_ASSERT_EQUAL(2,*((int *)(list->head->value)));
  TEST_ASSERT_NULL(list->head->next);
  TEST_ASSERT_EQUAL(2,*((int *)(list->tail->value)));
  TEST_ASSERT_NULL(list->tail->next);
  TEST_ASSERT_EQUAL(1,list->length);
}

/**********************************************************************************
 * Testing function addLast when two element added to the LinkedList.             *
 *                                                                                *
 *                      1st Ele         2nd Ele                                   *
 *                      _________      _________                                  *
 *   list---+-->head-->| value=1|     | value=2|                                  *
 *          |          |________|---->|________|---->NULL                         *
 *          |                             ^                                       *
 *          |                             |                                       *
 *          +-->tail----------------------+                                       *
 *                                                                                *
 **********************************************************************************/ 
void test_Adding_two_element_to_LinkedList_using_function_addLast()
{
  int i;
  int value[]={1,2};

  LinkedList *list;
  list=createLinkedList();

  for(i=0;i<2;i++){
    addLast(createListElement(&value[i]),list);
  }

  TEST_ASSERT_EQUAL(1,*((int *)(list->head->value)));
  TEST_ASSERT_NOT_NULL(list->head);
  TEST_ASSERT_NOT_NULL(list->tail);
  TEST_ASSERT_EQUAL_PTR(list->tail,list->head->next);
  TEST_ASSERT_EQUAL(2,*((int *)(list->tail->value)));
  TEST_ASSERT_NULL(list->tail->next);
  TEST_ASSERT_EQUAL(2,list->length);
}

/**********************************************************************************
 * Testing function AddLast when three element added to the LinkedList.           *
 *                                                                                *
 *                     1st Ele        2nd Ele        3rd Ele                      *
 *                    _________      _________      _________                     *
 * list---+-->head-->| value=1|     | value=2|     | value=3|                     *
 *        |          |________|---->|________|---->|________|---->NULL            *
 *        |                                            ^                          *
 *        |                                            |                          *
 *        +-->tail-------------------------------------+                          *
 *                                                                                *
 **********************************************************************************/
void test_Adding_three_element_to_LinkedList_using_function_addLast()
{
  int i;
  int value[]={1,2,3};

  LinkedList *list;
  Iterator *iter;
  list=createLinkedList();

  for(i=0;i<3;i++){
    addLast(createListElement(&value[i]),list);
  }

  TEST_ASSERT_NOT_NULL(list);
  iter=createIterator(list);
  TEST_ASSERT_EQUAL(*((int *)(list->head->value)),*((int *)(iter->current->value)));
  TEST_ASSERT_EQUAL(1,*((int *)(iter->current->value)));
  iter=iteratorGetNext(iter);
  TEST_ASSERT_EQUAL(2,*((int *)(iter->current->value)));
  iter=iteratorGetNext(iter);
  TEST_ASSERT_EQUAL(*((int *)(list->tail->value)),*((int *)(iter->current->value)));
  TEST_ASSERT_EQUAL(3,*((int *)(iter->current->value)));
  iter=iteratorGetNext(iter);
  TEST_ASSERT_NULL(iter->current);
  TEST_ASSERT_EQUAL(3,list->length);
}


void test_Adding_five_element_to_LinkedList_using_function_addLast()
{
  int i;
  int value[]={95,100,14,111,123};

  LinkedList *list;
  Iterator *iter;
  list = createLinkedList();

  for(i=0;i<5;i++){
    addLast(createListElement(&value[i]),list);
  }

  TEST_ASSERT_NOT_NULL(list);
  iter=createIterator(list);
  TEST_ASSERT_EQUAL(95  ,*((int *)(iter->current->value)));
  iter=iteratorGetNext(iter);
  TEST_ASSERT_EQUAL(100 ,*((int *)(iter->current->value)));
  iter=iteratorGetNext(iter);
  TEST_ASSERT_EQUAL(14  ,*((int *)(iter->current->value)));
  iter=iteratorGetNext(iter);
  TEST_ASSERT_EQUAL(111 ,*((int *)(iter->current->value)));
  iter=iteratorGetNext(iter);
  TEST_ASSERT_EQUAL(123 ,*((int *)(iter->current->value)));
  iter=iteratorGetNext(iter);
  TEST_ASSERT_NULL(iter->current);
  TEST_ASSERT_EQUAL(5,list->length);
}






