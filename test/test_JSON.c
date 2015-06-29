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

void test_DetermineState()
{
  LinkedList *List;
  Token *token1 =malloc(sizeof(Token));
  Token *token2 =malloc(sizeof(Token));
  Token *token3 =malloc(sizeof(Token));
  Token *token4 =malloc(sizeof(Token));
  Token *token5 =malloc(sizeof(Token));
  Token *token6 =malloc(sizeof(Token));
  Token *token7 =malloc(sizeof(Token));
  Token *token8 =malloc(sizeof(Token));
  Token *token9 =malloc(sizeof(Token));
  Token *token10 =malloc(sizeof(Token));
  Token *token11 =malloc(sizeof(Token));
  Token *token12 =malloc(sizeof(Token));
  Token *token13 =malloc(sizeof(Token));

  token1-> type=TOKEN_OPERATOR_TYPE;
  ((OperatorToken *)(token1))-> symbol="{";
  getToken_ExpectAndReturn(token1);

  token2-> type=TOKEN_IDENTIFIER_TYPE;
  ((IdentifierToken *)(token2))-> name="NAME";
  getToken_ExpectAndReturn(token2);

  token3-> type=TOKEN_OPERATOR_TYPE;
  ((OperatorToken *)(token3))->symbol=":";
  getToken_ExpectAndReturn(token3);

  // token4-> type=TOKEN_STRING_TYPE;
  // ((StringToken *)(token4))-> name="JS";
  // getToken_ExpectAndReturn(token4);

  // token5-> type=TOKEN_OPERATOR_TYPE;
  // ((OperatorToken *)(token5))-> symbol="{";
  // getToken_ExpectAndReturn(token5);

  // token6-> type=TOKEN_OPERATOR_TYPE;
  // ((OperatorToken *)(token6))-> symbol="[";
  // getToken_ExpectAndReturn(token6);

  token7-> type=TOKEN_INTEGER_TYPE;
  ((IntegerToken *)(token7))-> value=1234;
  getToken_ExpectAndReturn(token7);

  token8-> type=TOKEN_OPERATOR_TYPE;
  ((OperatorToken *)(token8))-> symbol=",";
  getToken_ExpectAndReturn(token8);

  token9-> type=TOKEN_IDENTIFIER_TYPE;
  ((IdentifierToken *)(token9))-> name="NAME2";
  getToken_ExpectAndReturn(token9);

  token10-> type=TOKEN_OPERATOR_TYPE;
  ((OperatorToken *)(token10))->symbol=":";
  getToken_ExpectAndReturn(token10);

  token11-> type=TOKEN_OPERATOR_TYPE;
  ((OperatorToken *)(token11))-> symbol="{";
  getToken_ExpectAndReturn(token11);

  getToken_ExpectAndReturn(NULL);

  List=DetermineState();
  TEST_ASSERT_EQUAL(OBJECT,List->state);


  // printf("\n\n%d",isdigit('9'));
  // printf("\n\n%d",isalpha('A'));


}