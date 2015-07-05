#include "unity.h"
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#include "mock_Token.h"
#include "LinkedList.h"
#include "JSON.h"

void setUp(void)
{
}

void tearDown(void)
{
}

void test_getToken()
{

  // Token *token;
  Token *token0=malloc(sizeof(Token));
  Token *token1=malloc(sizeof(Token));
  Token *token2=malloc(sizeof(Token));
  Token *token3=malloc(sizeof(Token));
  Token *token4=malloc(sizeof(Token));

  ((IntegerToken *)(token0))-> value=100;
  ((FloatToken *)(token1))-> value=12.34;
  ((IdentifierToken *)(token2))-> name="JangSing";
  ((StringToken *)(token3))-> name="Wong";
  ((OperatorToken *)(token4))-> symbol="{";

	getToken_ExpectAndReturn(token0);
	getToken_ExpectAndReturn(token1);
	getToken_ExpectAndReturn(token2);
	getToken_ExpectAndReturn(token3);
	getToken_ExpectAndReturn(token4);

  TEST_ASSERT_EQUAL(100,((IntegerToken *)(getToken()))-> value);
  TEST_ASSERT_EQUAL_FLOAT(12.34,((FloatToken *)(getToken()))-> value);
  TEST_ASSERT_EQUAL_STRING("JangSing",((IdentifierToken *)(getToken()))-> name);
  TEST_ASSERT_EQUAL_STRING("Wong",((StringToken *)(getToken()))-> name);
  TEST_ASSERT_EQUAL_STRING("{",((OperatorToken *)(getToken()))-> symbol);
}

void test_createListElement()
{
  ListElement *NewNode;
  IntegerToken *IntTok;

  IntTok=createIntegerToken(123);
  NewNode = createListElement(IntTok);

  TEST_ASSERT_NOT_NULL(NewNode);
  TEST_ASSERT_NOT_NULL(NewNode->value);

  TEST_ASSERT_EQUAL(123,IntTok->value);

  TEST_ASSERT_EQUAL(123,((IntegerToken *)(NewNode->value))->value);
  TEST_ASSERT_EQUAL(TOKEN_INTEGER_TYPE,((IntegerToken *)(NewNode->value))->type);

}

/**
 *  {
 *    "NAME1":"JS",
 *    "NAME2":"STEVEN"
 *  }
 */
void test_Simple_JSON_List()
{
  LinkedList *List;

  Token *OpenBrace=createOperatorToken("{");
  Token *Key=(Token*)createIdentifierToken("NAME1");
  Token *Colon=(Token*)createOperatorToken(":");
  Token *Value=(Token*)createStringToken("JS");
  Token *Coma=(Token*)createOperatorToken(",");
  Token *Key1=(Token*)createIdentifierToken("AGE");
  Token *Colon1=(Token*)createOperatorToken(":");
  Token *Value1=(Token*)createIntegerToken(20);
  Token *CloseBrace=createOperatorToken("}");

  getToken_ExpectAndReturn(OpenBrace);
  getToken_ExpectAndReturn(Key);
  getToken_ExpectAndReturn(Colon);
  getToken_ExpectAndReturn(Value);
  getToken_ExpectAndReturn(Coma);
  getToken_ExpectAndReturn(Key1);
  getToken_ExpectAndReturn(Colon);
  getToken_ExpectAndReturn(Value1);
  getToken_ExpectAndReturn(CloseBrace);

  getToken_ExpectAndReturn(NULL);

  List=DetermineState();


  TEST_ASSERT_EQUAL(END,List->state);
  TEST_ASSERT_EQUAL_STRING("{",((OperatorToken *)(List->head->value))->symbol);
  TEST_ASSERT_EQUAL_STRING(":",((OperatorToken *)(List->head->next->value))->symbol);
  TEST_ASSERT_EQUAL_STRING("NAME1",((StringToken *)(((OperatorToken *)(List->head->next->value))->token[0]))->name);
  TEST_ASSERT_EQUAL_STRING("JS",((StringToken *)(((OperatorToken *)(List->head->next->value))->token[1]))->name);
  TEST_ASSERT_EQUAL_STRING(",",((OperatorToken *)(List->head->next->next->value))->symbol);
  TEST_ASSERT_EQUAL_STRING(":",((OperatorToken *)(List->head->next->next->next->value))->symbol);
  TEST_ASSERT_EQUAL_STRING("AGE",((StringToken *)(((OperatorToken *)(List->head->next->next->next->value))->token[0]))->name);
  TEST_ASSERT_EQUAL(20,((IntegerToken *)(((OperatorToken *)(List->head->next->next->next->value))->token[1]))->value);
  TEST_ASSERT_EQUAL_STRING("}",((OperatorToken *)(List->head->next->next->next->next->value))->symbol);

}
/**
 *{
 *  "NAME1":"JS",
 *  "AGE"  :{"NAME2":"STEVEN"}
 *}
 */
void test_JSON_List_with_Recursion()
{
  LinkedList *List;

  Token *OpenBrace=createOperatorToken("{");
  Token *Key=(Token*)createIdentifierToken("NAME1");
  Token *Colon=(Token*)createOperatorToken(":");
  Token *Value=(Token*)createStringToken("JS");
  Token *Coma=(Token*)createOperatorToken(",");
  Token *Key1=(Token*)createIdentifierToken("AGE");
  Token *Colon1=(Token*)createOperatorToken(":");
  // Token *OpenBrace=createOperatorToken("{");
  Token *Key2=(Token*)createIdentifierToken("NAME2");
  // Token *Colon=(Token*)createOperatorToken(":");
  Token *Value2=(Token*)createStringToken("STEVEN");
  Token *CloseBrace=createOperatorToken("}");
  // Token *CloseBrace=createOperatorToken("}");


  getToken_ExpectAndReturn(OpenBrace);
  getToken_ExpectAndReturn(Key);
  getToken_ExpectAndReturn(Colon);
  getToken_ExpectAndReturn(Value);

  getToken_ExpectAndReturn(Coma);

  getToken_ExpectAndReturn(Key1);
  getToken_ExpectAndReturn(Colon);

  getToken_ExpectAndReturn(OpenBrace);
  getToken_ExpectAndReturn(Key2);
  getToken_ExpectAndReturn(Colon);
  // getToken_ExpectAndReturn(Value2);
  getToken_ExpectAndReturn(CloseBrace);

  getToken_ExpectAndReturn(CloseBrace);

  getToken_ExpectAndReturn(NULL);


  List=DetermineState();

  TEST_ASSERT_EQUAL(END,List->state);

}
