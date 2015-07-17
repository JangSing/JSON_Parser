#include "unity.h"
#include "LinkedList.h"
#include "compareFunction.h"
#include "IteratorFunction.h"
#include "FindElementFunction.h"

#include <malloc.h>
#include <stdio.h>
#include <assert.h>

void setUp(void)
{
}

void tearDown(void)
{
}

void test_findElement_integer()
{
	int myValue4 =4;
  int value[]={1,3,4,6,7};

  LinkedList *ptr;
  ListElement *elemFind;

  ptr=createLinkedList();

  addLast(createListElement(&value[0]),ptr);
  addLast(createListElement(&value[1]),ptr);
  addLast(createListElement(&value[2]),ptr);
  addLast(createListElement(&value[3]),ptr);
  addLast(createListElement(&value[4]),ptr);

  elemFind=NULL;
  elemFind=listFind(ptr,&myValue4,intCompare);

  TEST_ASSERT_NOT_NULL(ptr);
  TEST_ASSERT_NOT_NULL(elemFind);
  TEST_ASSERT_NOT_NULL(elemFind->value);
  TEST_ASSERT_EQUAL(4,*(int *)(elemFind->value));

}

void test_findElement_string()
{
	char *myStr4="four";
  char *str[]={"one","three","four","six","seven"};

  LinkedList *ptr;
  ListElement *elemFind;

  ptr=createLinkedList();

  addLast(createListElement(str[0]),ptr);
  addLast(createListElement(str[1]),ptr);
  addLast(createListElement(str[2]),ptr);
  addLast(createListElement(str[3]),ptr);
  addLast(createListElement(str[4]),ptr);

  elemFind=NULL;
  elemFind=listFind(ptr,myStr4,strCompare);

  TEST_ASSERT_NOT_NULL(ptr);
  TEST_ASSERT_NOT_NULL(elemFind);
  TEST_ASSERT_NOT_NULL(elemFind->value);
  TEST_ASSERT_EQUAL("four",(char *)(elemFind->value));
}