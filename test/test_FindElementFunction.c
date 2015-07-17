#include "unity.h"
#include "LinkedList.h"
#include "compareFunction.h"
#include "IteratorFunction.h"
#include "FindElementFunction.h"

#include <malloc.h>
#include <stdio.h>
#include <assert.h>

void setUp()
{
}

void tearDown()
{
}

void test_listFind_Function_given_list_is_NULL_should_return_NULL()
{
  ListElement *findEle;
  char *strTest="forTesting";
  
  findEle=listFind(NULL,strTest,strCompare);
  
  TEST_ASSERT_NULL(findEle);
}

void test_keyFind_Function_given_list_is_NULL_should_return_NULL()
{
  ListElement *findEle;
  char *strTest="forTesting";
  
  findEle=keyFind(NULL,strTest,strCompare);
  
  TEST_ASSERT_NULL(findEle);
}

void test_listFind_Function_given_Value_is_NULL_should_return_NULL()
{
  ListElement *findEle;
  LinkedList *list;
  
  list=createLinkedList();
  
  findEle=listFind(list,NULL,strCompare);
  
  TEST_ASSERT_NULL(findEle);
}

void test_keyFind_Function_given_Value_is_NULL_should_return_NULL()
{
  ListElement *findEle;
  LinkedList *list;
  
  list=createLinkedList();
  
  findEle=keyFind(list,NULL,strCompare);
  
  TEST_ASSERT_NULL(findEle);
}










