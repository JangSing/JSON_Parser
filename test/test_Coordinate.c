#include "unity.h"
#include "CustomAssertion.h"
#include "mock_Token.h"
#include "JSON.h"
#include "LinkedList.h"

void setUp(void)
{
}

void tearDown(void)
{
}

void test_iteratorGetNext_for_Simple_List()
{
  LinkedList *List;
  Iterator *Iter;
  
  Token *OpenBrace=createOperatorToken("{");
  Token *CloseBrace=createOperatorToken("}");
  Token *Coma=(Token*)createOperatorToken(",");
  Token *Colon=(Token*)createOperatorToken(":");
  Token *Key0=(Token*)createIdentifierToken("NAME1");
  Token *Key1=(Token*)createIdentifierToken("AGE");
  Token *Value0=(Token*)createStringToken("JS");
  Token *Value1=(Token*)createIntegerToken(20);

  getToken_ExpectAndReturn(OpenBrace);    //"{"
  getToken_ExpectAndReturn(Key0);         //"NAME1"
  getToken_ExpectAndReturn(Colon);        //":"
  getToken_ExpectAndReturn(Value0);       //"JS"
  getToken_ExpectAndReturn(Coma);         //","
  getToken_ExpectAndReturn(Key1);         //"AGE"
  getToken_ExpectAndReturn(Colon);        //":"
  getToken_ExpectAndReturn(Value1);       //20
  getToken_ExpectAndReturn(CloseBrace);   //"}"
  getToken_ExpectAndReturn(NULL);

  List=JsonParse();

  int IntValue[]={10,20,30};
  
  TEST_ASSERT_EQUAL(END,List->state);

  Iter=createIterator(List);
  TEST_ASSERT_EQUAL_STRING("{",((OperatorToken *)(Iter->current->value))->symbol);
  Iter=iteratorGetNext(Iter);
  TEST_ASSERT_TREE("NAME1","JS", Iter);
  Iter=iteratorGetNext(Iter);
  TEST_ASSERT_TREE("AGE",&IntValue[1], Iter);
  Iter=iteratorGetNext(Iter);
  TEST_ASSERT_EQUAL_STRING("}",((OperatorToken *)(Iter->current->value))->symbol);

  // OperatorToken *Token = ((OperatorToken *)(tempToken->value));

  // OperatorToken *Token2 = ((OperatorToken *)(List->head->next->value));
  // OperatorToken *Token3 = ((OperatorToken *)(List->head->next->next->value));
  // OperatorToken *Token4 = ((OperatorToken *)(List->head->next->next->next->value));

  // TEST_ASSERT_EQUAL_STRING(":",Token2->symbol);
  // TEST_ASSERT_EQUAL_STRING("NAME1",((IdentifierToken *)(Token2->token[0]))->name);
  // TEST_ASSERT_EQUAL_STRING("JS",((StringToken *)(Token2->token[1]))->name);
  // TEST_ASSERT_EQUAL_STRING(":",Token3->symbol);
  // TEST_ASSERT_EQUAL_STRING("AGE",((IdentifierToken *)(Token3->token[0]))->name);
  // TEST_ASSERT_EQUAL(20,((IntegerToken *)(Token3->token[1]))->value);
  // TEST_ASSERT_EQUAL_STRING("}",Token4->symbol);


}
