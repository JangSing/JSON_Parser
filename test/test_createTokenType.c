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

/********************************************************************************
 * This test is to test that whether the Token is created correctly.            *
 * For all type of Token created will return as Token.                          *
 * The expected Token element is as shown below.                                *
 *  e.g.                                                                        *
 *  For OperatorToken,                                                          *
 *              ______________________                                          *
 *             |       opTok         |                                          *
 *             -----------------------                                          *
 *     type    | TOKEN_OPERATOR_TYPE |                                          *
 *             -----------------------                                          *
 *    symbol   |       "{"           |                                          *
 *             -----------------------                                          *
 *    length   |        1            |                                          *
 *             -----------------------                                          *
 *             | Token[0] | Token[1] |                                          *
 *             -----------------------                                          *
 *                  |          |                                                *
 *                  v          v                                                *
 *                NULL        NULL                                              *
 *                                                                              *
 *                                                                              *
 *  For IdentifierToken,                                                        *
 *              ________________________                                        *
 *             |       idenTok         |                                        *
 *             -------------------------                                        *
 *     type    | TOKEN_IDENTIFIER_TYPE |                                        *
 *             -------------------------                                        *
 *     name    |       "NAME"          |                                        *
 *             -------------------------                                        *
 *    length   |          4            |                                        *
 *             -------------------------                                        *
 *                                                                              *
 *                                                                              *
 *  For IntegerToken,                                                           *
 *              ________________________                                        *
 *             |       intTok          |                                        *
 *             -------------------------                                        *
 *     type    |  TOKEN_INTEGER_TYPE   |                                        *
 *             -------------------------                                        *
 *     value   |          20           |                                        *
 *             -------------------------                                        *
 *    length   |          2            |                                        *
 *             -------------------------                                        *
 *                                                                              *
 *                                                                              *
 *  For StringToken,                                                            *
 *              ________________________                                        *
 *             |       strTok          |                                        *
 *             -------------------------                                        *
 *     type    |   TOKEN_STRING_TYPE   |                                        *
 *             -------------------------                                        *
 *     name    |        "JS"           |                                        *
 *             -------------------------                                        *
 *    length   |          2            |                                        *
 *             -------------------------                                        *
 *                                                                              *
 * The test for the Token above are as shown below,                             *
 *                                                                              *
 ********************************************************************************/

void test_create_Token_passing_in_NULL_should_return_NULL()
{
	Token *opTok=createOperatorToken(NULL);

  TEST_ASSERT_NULL(opTok);
}

void test_create_Operator_Token_passing_in_Operator_should_return_Token()
{
	Token *opTok=createOperatorToken("{");

  TEST_ASSERT_NOT_NULL(opTok);
  TEST_ASSERT_EQUAL(TOKEN_OPERATOR_TYPE,((OperatorToken *)(opTok))->type);
  TEST_ASSERT_EQUAL_STRING("{",((OperatorToken *)(opTok))->symbol);
  TEST_ASSERT_NULL(((OperatorToken *)(opTok))->token[0]);
  TEST_ASSERT_NULL(((OperatorToken *)(opTok))->token[1]);
  TEST_ASSERT_EQUAL(1,((OperatorToken *)(opTok))->length);
}

void test_create_Identifier_Token_passing_in_key_should_return_Token()
{
	Token *idenTok=createIdentifierToken("NAME");

  TEST_ASSERT_NOT_NULL(idenTok);
  TEST_ASSERT_EQUAL(TOKEN_IDENTIFIER_TYPE,((IdentifierToken *)(idenTok))->type);
  TEST_ASSERT_EQUAL_STRING("NAME",((IdentifierToken *)(idenTok))->name);
  TEST_ASSERT_EQUAL(4,((IdentifierToken *)(idenTok))->length);
}

void test_create_Integer_Token_passing_in_value_should_return_Token()
{
	Token *intTok=createIntegerToken(20);

  TEST_ASSERT_NOT_NULL(intTok);
  TEST_ASSERT_EQUAL(TOKEN_INTEGER_TYPE,((IntegerToken *)(intTok))->type);
  TEST_ASSERT_EQUAL(20,((IntegerToken *)(intTok))->value);
  TEST_ASSERT_EQUAL(2,((IntegerToken *)(intTok))->length);
}

void test_create_String_Token_passing_in_value_should_return_Token()
{
	Token *strTok=createStringToken("JS");

  TEST_ASSERT_NOT_NULL(strTok);
  TEST_ASSERT_EQUAL(TOKEN_STRING_TYPE,((StringToken *)(strTok))->type);
  TEST_ASSERT_EQUAL_STRING("JS",((StringToken *)(strTok))->name);
  TEST_ASSERT_EQUAL(2,((StringToken *)(strTok))->length);
}
