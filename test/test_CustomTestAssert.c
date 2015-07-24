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

void test_Custom_Test_Assert_Key_Value()
{
  LinkedList *list;
  Iterator *iter;
  JsonObject *jsonObj;
  Token *jsonTok;

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

  jsonObj=createJsonObject();
  jsonTok=jsonParse(jsonObj);

  TEST_ASSERT_EQUAL(END,jsonObj->state);

  iter=createIterator(((JsonToken *)jsonTok)->list);
  TEST_ASSERT_EQUAL_STRING("{",((OperatorToken *)(iter->current->value))->symbol);
  iter=iteratorGetNext(iter);
  TEST_ASSERT_NOT_NULL(NAME1);
  TEST_ASSERT_NOT_NULL(JS);
  TEST_ASSERT_NOT_NULL(iter->current);
  TEST_ASSERT_KEY_VALUE(NAME1,JS, iter->current);
  iter=iteratorGetNext(iter);
  TEST_ASSERT_EQUAL_STRING("}",((OperatorToken *)(iter->current->value))->symbol);
}
