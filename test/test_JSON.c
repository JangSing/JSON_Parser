#include "unity.h"
#include "JSON.h"
#include "mock_getToken.h"
#include "LinkedList.h"
#include "stdio.h"
#include "stdlib.h"
#include <ctype.h>


void setUp(void)
{
}

void tearDown(void)
{
}

void test_getToken()
{

  Token *token;
  Token *getToken=malloc(sizeof(Token));
  getToken-> type=TOKEN_OPERATOR_TYPE;
  getToken-> value=OPERATOR1;


	getToken_ExpectAndReturn(getToken);

  token=ReceiveToken();

  TEST_ASSERT_EQUAL(TOKEN_OPERATOR_TYPE,token-> type);
  TEST_ASSERT_EQUAL(OPERATOR1,token-> value);
}

void test_DetermineState()
{
  Token *token0 =malloc(sizeof(Token));
  Token *token1 =malloc(sizeof(Token));
  Token *token2 =malloc(sizeof(Token));
  Token *token3 =malloc(sizeof(Token));
  Token *token4 =malloc(sizeof(Token));
  Token *token5 =malloc(sizeof(Token));
  Token *token6 =malloc(sizeof(Token));
  Token *token7 =malloc(sizeof(Token));

  //when input this will got to state OBJECT
  token1-> type=TOKEN_OPERATOR_TYPE;
  token1-> Operator=OPERATOR1;
  getToken_ExpectAndReturn(token1);

  //when input this will go to state WAIT_FOR_OPERATOR2
  token2-> type=TOKEN_IDENTIFIER_TYPE;
  token2-> value="NAME";
  getToken_ExpectAndReturn(token2);

  //when input this will go to state VALUE
  token3-> type=TOKEN_OPERATOR_TYPE;
  token3-> Operator=OPERATOR2;
  getToken_ExpectAndReturn(token3);

  //when input this will go to state END_OR_CON
  token4-> type=TOKEN_IDENTIFIER_TYPE;
  token4-> value="JS";
  getToken_ExpectAndReturn(token4);

  //when input this will go to state OBJECT
  // token5-> type=TOKEN_OPERATOR_TYPE;
  // token5-> value=OPERATOR1;
  // getToken_ExpectAndReturn(token5);

  //when input this will go to state ARRAY
  // token6-> type=TOKEN_OPERATOR_TYPE;
  // token6-> value=OPERATOR6;
  // getToken_ExpectAndReturn(token6);

  //when input this will go to state END
  token7-> type=TOKEN_OPERATOR_TYPE;
  token7-> Operator=OPERATOR4;
  getToken_ExpectAndReturn(token7);








  token0=(Token *)DetermineState();
  TEST_ASSERT_EQUAL(END,((LinkedList *)token0)->state);


  // printf("\n\n%d",isdigit('9'));
  // printf("\n\n%d",isalpha('A'));


}