#include "unity.h"
#include "CustomAssertion.h"
#include "mock_Token.h"
#include "JSON.h"
#include "LinkedList.h"
#include "compareFunction.h"
#include "IteratorFunction.h"
#include "createTokenType.h"

void setUp()
{
}

void tearDown()
{
}

void test_Custom_Test_Assert_Key_Value()
{
  LinkedList *list;
  Iterator *iter;

  Token *openBrace=createOperatorToken("{");
  Token *closeBrace=createOperatorToken("}");
  Token *colon0=createOperatorToken(":");
  Token *NAME1=createIdentifierToken("NAME1");
  Token *JS=createStringToken("JS");

  getToken_ExpectAndReturn(openBrace);     //"{"
  getToken_ExpectAndReturn(NAME1);         //"NAME1"
  getToken_ExpectAndReturn(colon0);        //":"
  getToken_ExpectAndReturn(JS);            //"JS"
  getToken_ExpectAndReturn(closeBrace);    //"}"
  getToken_ExpectAndReturn(NULL);

  list=jsonParse();
  TEST_ASSERT_EQUAL(END,list->state);

  iter=createIterator(list);
  TEST_ASSERT_EQUAL_STRING("{",((OperatorToken *)(iter->current->value))->symbol);
  iter=iteratorGetNext(iter);

  TEST_ASSERT_NOT_NULL(NAME1);
  TEST_ASSERT_NOT_NULL(JS);
  TEST_ASSERT_NOT_NULL(iter->current);
  TEST_ASSERT_KEY_VALUE(NAME1,JS, iter->current);

  iter=iteratorGetNext(iter);
  TEST_ASSERT_EQUAL_STRING("}",((OperatorToken *)(iter->current->value))->symbol);
}

void test_iteratorGetNext_for_Simple_List()
{
  LinkedList *list;
  Iterator *iter;

  Token *openBrace=createOperatorToken("{");
  Token *closeBrace=createOperatorToken("}");
  Token *coma=createOperatorToken(",");
  Token *colon0=createOperatorToken(":");
  Token *NAME1=createIdentifierToken("NAME1");
  Token *AGE=createIdentifierToken("AGE");
  Token *colon1=createOperatorToken(":");
  Token *JS=createStringToken("JS");
  Token *int20=createIntegerToken(20);

  getToken_ExpectAndReturn(openBrace);    //"{"
  getToken_ExpectAndReturn(NAME1);         //"NAME1"
  getToken_ExpectAndReturn(colon0);        //":"
  getToken_ExpectAndReturn(JS);       //"JS"
  getToken_ExpectAndReturn(coma);         //","
  getToken_ExpectAndReturn(AGE);         //"AGE"
  getToken_ExpectAndReturn(colon1);        //":"
  getToken_ExpectAndReturn(int20);       //20
  getToken_ExpectAndReturn(closeBrace);   //"}"
  getToken_ExpectAndReturn(NULL);

  list=jsonParse();

  TEST_ASSERT_EQUAL(END,list->state);

  iter=createIterator(list);
  TEST_ASSERT_EQUAL_STRING("{",((OperatorToken *)(iter->current->value))->symbol);
  iter=iteratorGetNext(iter);
  TEST_ASSERT_KEY_VALUE(NAME1,JS, iter->current);
  iter=iteratorGetNext(iter);
  TEST_ASSERT_KEY_VALUE(AGE,int20, iter->current);
  iter=iteratorGetNext(iter);
  TEST_ASSERT_EQUAL_STRING("}",((OperatorToken *)(iter->current->value))->symbol);

}
