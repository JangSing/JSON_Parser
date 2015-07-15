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

void test_iteratorGetNext_for_Simple_List()
{
  LinkedList *list;
  Iterator *iter;

  Token *openBrace=createOperatorToken("{");
  Token *closeBrace=createOperatorToken("}");
  Token *coma=(Token*)createOperatorToken(",");
  Token *colon0=(Token*)createOperatorToken(":");
  Token *NAME1=(Token*)createIdentifierToken("NAME1");
  Token *AGE=(Token*)createIdentifierToken("AGE");
  Token *colon1=(Token*)createOperatorToken(":");
  Token *JS=(Token*)createStringToken("JS");
  Token *int20=(Token*)createIntegerToken(20);

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
  // iter=iteratorGetNext(iter);
  // TEST_ASSERT_KEY_VALUE("AGE",&IntValue[1], iter);
  // iter=iteratorGetNext(iter);
  // TEST_ASSERT_EQUAL_STRING("}",((OperatorToken *)(iter->current->value))->symbol);

}
