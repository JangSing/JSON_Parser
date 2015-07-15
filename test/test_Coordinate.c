#include "unity.h"
#include "CustomAssertion.h"
#include "mock_Token.h"
#include "JSON.h"
#include "LinkedList.h"
#include "compareFunction.h"
#include "IteratorFunction.h"

void setUp(void)
{
}

void tearDown(void)
{
}

void test_iteratorGetNext_for_Simple_List()
{
  LinkedList *list;
  Iterator *iter;

  Token *openBrace=createOperatorToken("{");
  Token *closeBrace=createOperatorToken("}");
  Token *coma=(Token*)createOperatorToken(",");
  Token *colon=(Token*)createOperatorToken(":");
  Token *key0=(Token*)createIdentifierToken("NAME1");
  Token *key1=(Token*)createIdentifierToken("AGE");
  Token *value0=(Token*)createStringToken("JS");
  Token *value1=(Token*)createIntegerToken(20);

  getToken_ExpectAndReturn(openBrace);    //"{"
  getToken_ExpectAndReturn(key0);         //"NAME1"
  getToken_ExpectAndReturn(colon);        //":"
  getToken_ExpectAndReturn(value0);       //"JS"
  getToken_ExpectAndReturn(coma);         //","
  getToken_ExpectAndReturn(key1);         //"AGE"
  getToken_ExpectAndReturn(colon);        //":"
  getToken_ExpectAndReturn(value1);       //20
  getToken_ExpectAndReturn(closeBrace);   //"}"
  getToken_ExpectAndReturn(NULL);

  list=jsonParse();

  int IntValue[]={10,20,30};

  TEST_ASSERT_EQUAL(END,list->state);

  iter=createIterator(list);
  TEST_ASSERT_EQUAL_STRING("{",((operatorToken *)(iter->current->value))->symbol);
  iter=iteratorGetNext(iter);
  TEST_ASSERT_TREE("NAME1","JS", iter);
  iter=iteratorGetNext(iter);
  TEST_ASSERT_TREE("AGE",&IntValue[1], iter);
  iter=iteratorGetNext(iter);
  TEST_ASSERT_EQUAL_STRING("}",((operatorToken *)(iter->current->value))->symbol);

  // operatorToken *Token = ((operatorToken *)(tempToken->value));

  // operatorToken *token2 = ((operatorToken *)(list->head->next->value));
  // operatorToken *token3 = ((operatorToken *)(list->head->next->next->value));
  // operatorToken *token4 = ((operatorToken *)(list->head->next->next->next->value));

  // TEST_ASSERT_EQUAL_STRING(":",token2->symbol);
  // TEST_ASSERT_EQUAL_STRING("NAME1",((IdentifierToken *)(token2->token[0]))->name);
  // TEST_ASSERT_EQUAL_STRING("JS",((StringToken *)(token2->token[1]))->name);
  // TEST_ASSERT_EQUAL_STRING(":",token3->symbol);
  // TEST_ASSERT_EQUAL_STRING("AGE",((IdentifierToken *)(token3->token[0]))->name);
  // TEST_ASSERT_EQUAL(20,((IntegerToken *)(token3->token[1]))->value);
  // TEST_ASSERT_EQUAL_STRING("}",token4->symbol);


}
