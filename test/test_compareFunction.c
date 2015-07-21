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
#include <stdio.h>

void setUp()
{
}

void tearDown()
{
}


/**
 *  Compare Function
 *  -if values are equal, function will return 0.
 *  -if either values are NULL, function will return -1.
 *  -else the function will return 1.
 */
void test_function_intCompare()
{
  int value[10]={1212,2121,1556,1556};
  char *str[10]={"JS","HAHAHA","hello","Hello","hello"};

  TEST_ASSERT_EQUAL(1,intCompare(&value[0], &value[1]));
  TEST_ASSERT_EQUAL(0,intCompare(&value[2], &value[3]));

  TEST_ASSERT_EQUAL(1,intCompare(&str[0], &str[1]));
  TEST_ASSERT_EQUAL(1,intCompare(&str[2], &str[3]));
  TEST_ASSERT_EQUAL(0,intCompare(&str[2], &str[4]));
  
  TEST_ASSERT_EQUAL(-1,intCompare(NULL, &value[3]));
  TEST_ASSERT_EQUAL(-1,intCompare(&value[3], NULL));
}

void test_function_strCompare()
{
  int value[10]={1212,2121,1556,1556};
  char *str[10]={"JS","HAHAHA","hello","Hello","hello"};

  TEST_ASSERT_EQUAL(1,strCompare(&value[0], &value[1]));
  TEST_ASSERT_EQUAL(0,strCompare(&value[2], &value[3]));

  TEST_ASSERT_EQUAL(1,strCompare(&str[0], &str[1]));
  TEST_ASSERT_EQUAL(1,strCompare(&str[2], &str[3]));
  TEST_ASSERT_EQUAL(0,strCompare(&str[2], &str[4]));

  TEST_ASSERT_EQUAL(-1,strCompare(NULL, &str[3]));
  TEST_ASSERT_EQUAL(-1,strCompare(&str[3], NULL));
}
