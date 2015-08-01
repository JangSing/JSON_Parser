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

void setUp(void)
{
}

void tearDown(void)
{
}

void test_create_Token_passing_in_NULL_should_return_NULL(void)
{
	Token *opTok=createOperatorToken(NULL);

  TEST_ASSERT_NULL(opTok);
}

void test_create_Operator_Token_passing_in_Operator_should_return_Token(void)
{
	Token *opTok=createOperatorToken("{");

  TEST_ASSERT_NOT_NULL(opTok);
  TEST_ASSERT_EQUAL(TOKEN_OPERATOR_TYPE,((OperatorToken *)(opTok))->type);
  TEST_ASSERT_EQUAL_STRING("{",((OperatorToken *)(opTok))->symbol);
}

void test_create_Identifier_Token_passing_in_key_should_return_Token(void)
{
	Token *idenTok=createIdentifierToken("NAME");

  TEST_ASSERT_NOT_NULL(idenTok);
  TEST_ASSERT_EQUAL(TOKEN_IDENTIFIER_TYPE,((IdentifierToken *)(idenTok))->type);
  TEST_ASSERT_EQUAL_STRING("NAME",((IdentifierToken *)(idenTok))->name);
}

void test_create_Integer_Token_passing_in_value_should_return_Token(void)
{
	Token *intTok=createIntegerToken(20);

  TEST_ASSERT_NOT_NULL(intTok);
  TEST_ASSERT_EQUAL(TOKEN_INTEGER_TYPE,((IntegerToken *)(intTok))->type);
  TEST_ASSERT_EQUAL(20,((IntegerToken *)(intTok))->value);
}

void test_create_String_Token_passing_in_value_should_return_Token(void)
{
	Token *strTok=createStringToken("JS");

  TEST_ASSERT_NOT_NULL(strTok);
  TEST_ASSERT_EQUAL(TOKEN_STRING_TYPE,((StringToken *)(strTok))->type);
  TEST_ASSERT_EQUAL_STRING("JS",((StringToken *)(strTok))->name);
}
