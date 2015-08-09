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

void setUp()
{
}

void tearDown()
{
}

void test_iteratorGetNext_given_current_iterator_should_return_next_iterator()
{
  int value[]={1,3,4};

  LinkedList *ptr;
  Iterator *iter;

  ptr=createLinkedList();

  addLast(createListElement(&value[0]),ptr);
  addLast(createListElement(&value[1]),ptr);
  addLast(createListElement(&value[2]),ptr);

  TEST_ASSERT_NOT_NULL(ptr);
  iter=createIterator(ptr);

  TEST_ASSERT_NOT_NULL(iter);
  TEST_ASSERT_NOT_NULL(iter->current->next);
  TEST_ASSERT_EQUAL(1,*((int *)(iter->current->value)));
  iter=iteratorGetNext(iter);

  TEST_ASSERT_NOT_NULL(iter);
  TEST_ASSERT_NOT_NULL(iter->current->next);
  TEST_ASSERT_EQUAL(3,*((int *)(iter->current->value)));
  iter=iteratorGetNext(iter);

  TEST_ASSERT_NOT_NULL(iter);
  TEST_ASSERT_NULL(iter->current->next);
  TEST_ASSERT_EQUAL(4,*((int *)(iter->current->value)));
}
