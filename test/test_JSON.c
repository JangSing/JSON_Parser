#include "unity.h"
#include "JSON.h"
#include "mock_getToken.h"
#include "stdio.h"
#include "stdlib.h"

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
  getToken-> value="{";
  
  
	getToken_ExpectAndReturn(getToken);
  
  token=ReceiveToken();
  
  TEST_ASSERT_EQUAL(TOKEN_OPERATOR_TYPE,token-> type);
  TEST_ASSERT_EQUAL("{",token-> value);
}

void test_DetermineState()
{
  Token *token;
  Token *getToken=malloc(sizeof(Token));
  
  getToken-> type=TOKEN_OPERATOR_TYPE;
  getToken-> value="{";
  
  token=DetermineState(getToken);
  
  
  
  
  
}
