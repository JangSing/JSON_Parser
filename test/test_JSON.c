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

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

void setUp()
{
}

void tearDown()
{
}

void test_getToken()
{
  Token *INT=createIntegerToken(100);
  Token *IDEN=createIdentifierToken("JangSing");
  Token *STR=createStringToken("Wong");
  Token *OPE=createOperatorToken("{");;

  getToken_ExpectAndReturn(INT);
  getToken_ExpectAndReturn(IDEN);
  getToken_ExpectAndReturn(STR);
  getToken_ExpectAndReturn(OPE);

  TEST_ASSERT_EQUAL(100,((IntegerToken *)(getToken()))-> value);
  TEST_ASSERT_EQUAL_STRING("JangSing",((IdentifierToken *)(getToken()))-> name);
  TEST_ASSERT_EQUAL_STRING("Wong",((StringToken *)(getToken()))-> name);
  TEST_ASSERT_EQUAL_STRING("{",((OperatorToken *)(getToken()))-> symbol);

  free(INT);
  free(IDEN);
  free(STR);
  free(OPE);
}


/**
 * at state WAIT_FOR_TOKEN,
 * Test if Empty String been passed into the list
 *
 */
void test_JSON_List_with_Empty_String_Passed_in_should_Throw_Error()
{
  JsonObject *jsonObj=NULL;
  Token *jsonTok;
  ErrorObject *err;

  TOKEN_DECLARE;

  getToken_ExpectAndReturn(dollarSign);

  jsonObj=createJsonObject();
  Try{
    jsonTok=jsonParse(jsonObj);
    TEST_FAIL_MESSAGE("Expecting ERR_EXPECT_OPERATOR but none thrown.");
  }Catch(err){
    TEST_ASSERT_EQUAL_STRING("ERROR[13]:Empty String passing into the JsonParse.",err->errorMsg);
    TEST_ASSERT_EQUAL(ERR_EMPTY_STRING,err->errorCode);
    free(err);
  }

  free(jsonObj);
  free(jsonTok);

  TOKEN_FREE;
}

/**
 * at state WAIT_FOR_TOKEN,
 * Test only '}' token has been passed into the list
 *
 *  }
 *
 */
void test_Simple_JSON_List_with_only_close_Brace_should_Throw_Error()
{
  JsonObject *jsonObj=NULL;
  Token *jsonTok;
  ErrorObject *err;

  TOKEN_DECLARE;

  getToken_ExpectAndReturn(closeBrace0);   //"}"
  getToken_ExpectAndReturn(dollarSign);

  jsonObj=createJsonObject();
  Try{
    jsonTok=jsonParse(jsonObj);
    TEST_FAIL_MESSAGE("Expecting ERR_EXPECT_OPERATOR but none thrown.");
  }Catch(err){
    TEST_ASSERT_EQUAL_STRING("ERROR[7]:Expected '{' but get '}'.",err->errorMsg);
    TEST_ASSERT_EQUAL(ERR_EXPECT_OPERATOR,err->errorCode);
    free(err);
  }

  free(jsonObj);
  free(jsonTok);

  TOKEN_FREE;
}

/**
 * at state WAIT_FOR_TOKEN,
 * Test unexpected operator passing in beginning of JsonList
 *
 *  }{}{
 *
 */
void test_Simple_JSON_List_with_keep_Passing_Token_after_Error_occur_should_Throw_Error_and_ignore_remain_Token()
{
  JsonObject *jsonObj=NULL;
  Token *jsonTok;
  ErrorObject *err;

  TOKEN_DECLARE;

  getToken_ExpectAndReturn(closeBrace0);    //"}"
  getToken_ExpectAndReturn(openBrace0);     //"{"
  getToken_ExpectAndReturn(closeBrace1);    //"}"
  getToken_ExpectAndReturn(openBrace1);     //"{"
  getToken_ExpectAndReturn(dollarSign);

  jsonObj=createJsonObject();
  Try{
    jsonTok=jsonParse(jsonObj);
    TEST_FAIL_MESSAGE("Expecting ERR_EXPECT_OPERATOR but none thrown.");
  }Catch(err){
    TEST_ASSERT_EQUAL_STRING("ERROR[7]:Expected '{' but get '}'.",err->errorMsg);
    TEST_ASSERT_EQUAL(ERR_EXPECT_OPERATOR,err->errorCode);
    free(err);
  }
  free(jsonObj);
  free(jsonTok);

  TOKEN_FREE;
}

/**
 * at state OBJECT,
 * Test if no token has been passed in after Open Brace Token
 *
 *  {
 *
 */
void test_Simple_JSON_List_with_no_Token_Passed_in_after_open_Brace_Token_should_Throw_Error()
{
  JsonObject *jsonObj=NULL;
  Token *jsonTok;
  ErrorObject *err;

  TOKEN_DECLARE;

  getToken_ExpectAndReturn(openBrace0);   //"{"
  getToken_ExpectAndReturn(dollarSign);

  jsonObj=createJsonObject();
  Try{
    jsonTok=jsonParse(jsonObj);
    TEST_FAIL_MESSAGE("Expecting ERR_ACCESS_DENIED but none thrown.");
  }Catch(err){
    TEST_ASSERT_EQUAL_STRING("ERROR[9]:ACCESS DENIED!!!The Json List is not completed.",err->errorMsg);
    TEST_ASSERT_EQUAL(ERR_ACCESS_DENIED,err->errorCode);
    free(err);
  }
  free(jsonObj);
  free(jsonTok);

  TOKEN_FREE;
}

/**
 * at state OBJECT,
 * Test if JS token has been passed in after Open Brace
 *
 *  { "JS"
 *
 */
void test_Simple_JSON_List_with_String_Token_Passed_in_after_open_Brace_Token_should_Throw_Error()
{
  JsonObject *jsonObj=NULL;
  Token *jsonTok;
  ErrorObject *err;

  TOKEN_DECLARE;

  getToken_ExpectAndReturn(openBrace0);   //"{"
  getToken_ExpectAndReturn(JS);           //"JS"
  getToken_ExpectAndReturn(dollarSign);

  jsonObj=createJsonObject();
  Try{
    jsonTok=jsonParse(jsonObj);
    TEST_FAIL_MESSAGE("Expecting ERR_EXPECT_IDEN but none thrown.");
  }Catch(err){
    TEST_ASSERT_EQUAL_STRING("ERROR[8]:Illegal 'Key'.Expected an Identifier for 'Key'.",err->errorMsg);
    TEST_ASSERT_EQUAL(ERR_EXPECT_IDEN,err->errorCode);
    free(err);
  }
  free(jsonObj);
  free(jsonTok);

  TOKEN_FREE;
}

/**
 * at state WAIT_FOR_COLON,
 * Test if no token has been passed in after NAME1 token
 *
 *  { "NAME1"
 *
 */
void test_Simple_JSON_List_with_no_Token_Passed_in_after_Key_Token_should_Throw_Error()
{
  JsonObject *jsonObj=NULL;
  Token *jsonTok;
  ErrorObject *err;

  TOKEN_DECLARE;

  getToken_ExpectAndReturn(openBrace0);   //"{"
  getToken_ExpectAndReturn(NAME1);        //"NAME1"
  getToken_ExpectAndReturn(dollarSign);

  jsonObj=createJsonObject();
  Try{
    jsonTok=jsonParse(jsonObj);
    TEST_FAIL_MESSAGE("Expecting ERR_ACCESS_DENIED but none thrown.");
  }Catch(err){
    TEST_ASSERT_EQUAL_STRING("ERROR[9]:ACCESS DENIED!!!The Json List is not completed.",err->errorMsg);
    TEST_ASSERT_EQUAL(ERR_ACCESS_DENIED,err->errorCode);
    free(err);
  }
  free(jsonObj);
  free(jsonTok);

  TOKEN_FREE;
}

/**
 * at state WAIT_FOR_COLON,
 * Test if closeBrace token has been passed in after NAME1 token
 *
 *  { "NAME1"}
 *
 */
void test_Simple_JSON_List_with_Close_Brace_Token_Passed_in_after_Key_Token_should_Throw_Error()
{
  JsonObject *jsonObj=NULL;
  Token *jsonTok;
  ErrorObject *err;

  TOKEN_DECLARE;

  getToken_ExpectAndReturn(openBrace0);   //"{"
  getToken_ExpectAndReturn(NAME1);        //"NAME1"
  getToken_ExpectAndReturn(closeBrace0);  //"}"
  getToken_ExpectAndReturn(dollarSign);

  jsonObj=createJsonObject();
  Try{
    jsonTok=jsonParse(jsonObj);
    TEST_FAIL_MESSAGE("Expecting ERR_EXPECT_OPERATOR but none thrown.");
  }Catch(err){
    TEST_ASSERT_EQUAL_STRING("ERROR[7]:Expected ':' but get '}'.",err->errorMsg);
    TEST_ASSERT_EQUAL(ERR_EXPECT_OPERATOR,err->errorCode);
    free(err);
  }
  free(jsonObj);
  free(jsonTok);

  TOKEN_FREE;
}

/**
 * at state WAIT_FOR_COLON,
 * Test if JS token has been passed in after NAME1 token
 *
 *  { "NAME1""JS"
 *
 */
void test_Simple_JSON_List_with_String_Token_Passed_in_after_Key_Token_should_Throw_Error()
{
  JsonObject *jsonObj=NULL;
  Token *jsonTok;
  ErrorObject *err;

  TOKEN_DECLARE;

  getToken_ExpectAndReturn(openBrace0);   //"{"
  getToken_ExpectAndReturn(NAME1);        //"NAME1"
  getToken_ExpectAndReturn(JS);           //"JS"
  getToken_ExpectAndReturn(dollarSign);

  jsonObj=createJsonObject();
  Try{
    jsonTok=jsonParse(jsonObj);
    TEST_FAIL_MESSAGE("Expecting ERR_EXPECT_OPERATOR but none thrown.");
  }Catch(err){
    TEST_ASSERT_EQUAL_STRING("ERROR[7]:Expected ':' but get 'JS'.",err->errorMsg);
    TEST_ASSERT_EQUAL(ERR_EXPECT_OPERATOR,err->errorCode);
    free(err);
  }
  free(jsonObj);
  free(jsonTok);

  TOKEN_FREE;
}

/**
 * at state WAIT_FOR_COLON,
 * Test if int20 token has been passed in after NAME1 token
 *
 *  { "NAME1"20
 *
 */
void test_Simple_JSON_List_with_Integer_Token_Passed_in_after_Key_Token_should_Throw_Error()
{
  JsonObject *jsonObj=NULL;
  Token *jsonTok;
  ErrorObject *err;

  TOKEN_DECLARE;

  getToken_ExpectAndReturn(openBrace0);   //"{"
  getToken_ExpectAndReturn(NAME1);        //"NAME1"
  getToken_ExpectAndReturn(int20);        //"20"
  getToken_ExpectAndReturn(dollarSign);

  jsonObj=createJsonObject();
  Try{
    jsonTok=jsonParse(jsonObj);
    TEST_FAIL_MESSAGE("Expecting ERR_EXPECT_OPERATOR but none thrown.");
  }Catch(err){
    TEST_ASSERT_EQUAL_STRING("ERROR[7]:Expected ':' but get '20'.",err->errorMsg);
    TEST_ASSERT_EQUAL(ERR_EXPECT_OPERATOR,err->errorCode);
    free(err);
  }
  free(jsonObj);
  free(jsonTok);

  TOKEN_FREE;
}

/**
 * at state VALUE,
 * Test if no token has been passed in after colon token
 *
 *  { "NAME1":
 *
 */
void test_Simple_JSON_List_with_no_Token_Passed_in_after_Colon_Token_should_Throw_Error1()
{
  JsonObject *jsonObj=NULL;
  Token *jsonTok;
  ErrorObject *err;

  TOKEN_DECLARE;

  getToken_ExpectAndReturn(openBrace0);   //"{"
  getToken_ExpectAndReturn(NAME1);        //"NAME1"
  getToken_ExpectAndReturn(colon0);       //":"
  getToken_ExpectAndReturn(dollarSign);

  jsonObj=createJsonObject();
  Try{
    jsonTok=jsonParse(jsonObj);
    TEST_FAIL_MESSAGE("Expecting ERR_ACCESS_DENIED but none thrown.");
  }Catch(err){
    TEST_ASSERT_EQUAL_STRING("ERROR[9]:ACCESS DENIED!!!The Json List is not completed.",err->errorMsg);
    TEST_ASSERT_EQUAL(ERR_ACCESS_DENIED,err->errorCode);
    free(err);
  }
  free(jsonObj);
  free(jsonTok);

  TOKEN_FREE;
}

/**
 * at state VALUE,
 * Test if closeBrace token has been passed in after colon token
 *
 *  { "NAME1":}
 *
 */
void test_Simple_JSON_List_with_Operator_Token_Passed_in_after_Colon_Token_should_Throw_Error1()
{
  JsonObject *jsonObj=NULL;
  Token *jsonTok;
  ErrorObject *err;

  TOKEN_DECLARE;

  getToken_ExpectAndReturn(openBrace0);   //"{"
  getToken_ExpectAndReturn(NAME1);        //"NAME1"
  getToken_ExpectAndReturn(colon0);       //":"
  getToken_ExpectAndReturn(closeBrace0);  //"}"
  getToken_ExpectAndReturn(dollarSign);

  jsonObj=createJsonObject();
  Try{
    jsonTok=jsonParse(jsonObj);
    TEST_FAIL_MESSAGE("Expecting ERR_ILLEGAL_VALUE but none thrown.");
  }Catch(err){
    TEST_ASSERT_EQUAL_STRING("ERROR[10]:Illegal 'Value'.Expected an Integer/String/Float for 'Value'.",err->errorMsg);
    TEST_ASSERT_EQUAL(ERR_ILLEGAL_VALUE,err->errorCode);
    free(err);
  }
  free(jsonObj);
  free(jsonTok);

  TOKEN_FREE;
}

/**
 * at state STRING,
 * Test if no token has been passed in after JS token
 *
 *  { "NAME1":"JS"
 *
 */
void test_Simple_JSON_List_with_no_Token_Passed_in_after_String_Token_should_Throw_Error()
{
  JsonObject *jsonObj=NULL;
  Token *jsonTok;
  ErrorObject *err;

  TOKEN_DECLARE;

  getToken_ExpectAndReturn(openBrace0);   //"{"
  getToken_ExpectAndReturn(NAME1);        //"NAME1"
  getToken_ExpectAndReturn(colon0);       //":"
  getToken_ExpectAndReturn(JS);           //"JS"
  getToken_ExpectAndReturn(dollarSign);

  jsonObj=createJsonObject();
  Try{
    jsonTok=jsonParse(jsonObj);
    TEST_FAIL_MESSAGE("Expecting ERR_ACCESS_DENIED but none thrown.");
  }Catch(err){
    TEST_ASSERT_EQUAL_STRING("ERROR[9]:ACCESS DENIED!!!The Json List is not completed.",err->errorMsg);
    TEST_ASSERT_EQUAL(ERR_ACCESS_DENIED,err->errorCode);
    free(err);
  }
  free(jsonObj);
  free(jsonTok);

  TOKEN_FREE;
}

/**
 * at state STRING,
 * Test if caret token has been passed in after JS token
 *
 *  { "NAME1":"JS"^
 *
 */
void test_Simple_JSON_List_with_Caret_Token_Passed_in_after_String_Token_should_Throw_Error()
{
  JsonObject *jsonObj=NULL;
  Token *jsonTok;
  ErrorObject *err;

  TOKEN_DECLARE;

  getToken_ExpectAndReturn(openBrace0);   //"{"
  getToken_ExpectAndReturn(NAME1);        //"NAME1"
  getToken_ExpectAndReturn(colon0);       //":"
  getToken_ExpectAndReturn(JS);           //"JS"
  getToken_ExpectAndReturn(caret);        //"^"
  getToken_ExpectAndReturn(dollarSign);

  jsonObj=createJsonObject();
  Try{
    jsonTok=jsonParse(jsonObj);
    TEST_FAIL_MESSAGE("Expecting ERR_EXPECT_OPERATOR but none thrown.");
  }Catch(err){
    TEST_ASSERT_EQUAL_STRING("ERROR[7]:Expected Operator '}' or ',' but get '^'.",err->errorMsg);
    TEST_ASSERT_EQUAL(ERR_EXPECT_OPERATOR,err->errorCode);
    free(err);
  }
  free(jsonObj);
  free(jsonTok);

  TOKEN_FREE;
}

/**
 * at state STRING,
 * Test if NAME2 token has been passed in after JS token
 *
 *  { "NAME1":"JS""NAME2"
 *
 */
void test_Simple_JSON_List_with_Identifier_Token_Passed_in_after_String_Token_should_Throw_Error()
{
  JsonObject *jsonObj=NULL;
  Token *jsonTok;
  ErrorObject *err;

  TOKEN_DECLARE;

  getToken_ExpectAndReturn(openBrace0);   //"{"
  getToken_ExpectAndReturn(NAME1);        //"NAME1"
  getToken_ExpectAndReturn(colon0);       //":"
  getToken_ExpectAndReturn(JS);           //"JS"
  getToken_ExpectAndReturn(NAME2);        //"NAME2"
  getToken_ExpectAndReturn(dollarSign);

  jsonObj=createJsonObject();
  Try{
    jsonTok=jsonParse(jsonObj);
    TEST_FAIL_MESSAGE("Expecting ERR_EXPECT_OPERATOR but none thrown.");
  }Catch(err){
    TEST_ASSERT_EQUAL_STRING("ERROR[7]:Expected Operator '}' or ',' but get 'NAME2'.",err->errorMsg);
    TEST_ASSERT_EQUAL(ERR_EXPECT_OPERATOR,err->errorCode);
    free(err);
  }
  free(jsonObj);
  free(jsonTok);

  TOKEN_FREE;
}

/**
 * at state STRING,
 * Test if int20 token has been passed in after JS token
 *
 *  { "NAME1":"JS"20
 *
 */
void test_Simple_JSON_List_with_Integer_Token_Passed_in_after_String_Token_should_Throw_Error()
{
  JsonObject *jsonObj=NULL;
  Token *jsonTok;
  ErrorObject *err;

  TOKEN_DECLARE;

  getToken_ExpectAndReturn(openBrace0);   //"{"
  getToken_ExpectAndReturn(NAME1);        //"NAME1"
  getToken_ExpectAndReturn(colon0);       //":"
  getToken_ExpectAndReturn(JS);           //"JS"
  getToken_ExpectAndReturn(int20);        //"20"
  getToken_ExpectAndReturn(dollarSign);

  jsonObj=createJsonObject();
  Try{
    jsonTok=jsonParse(jsonObj);
    TEST_FAIL_MESSAGE("Expecting ERR_EXPECT_OPERATOR but none thrown.");
  }Catch(err){
    TEST_ASSERT_EQUAL_STRING("ERROR[7]:Expected Operator '}' or ',' but get '20'.",err->errorMsg);
    TEST_ASSERT_EQUAL(ERR_EXPECT_OPERATOR,err->errorCode);
    free(err);
  }
  free(jsonObj);
  free(jsonTok);

  TOKEN_FREE;
}

/**
 * at state NUMBER,
 * Test if no token has been passed in after int20 token
 *
 *  { "NAME1":20
 *
 */
void test_Simple_JSON_List_with_no_Token_Passed_in_after_Integer_Token_should_Throw_Error()
{
  JsonObject *jsonObj=NULL;
  Token *jsonTok;
  ErrorObject *err;

  TOKEN_DECLARE;

  getToken_ExpectAndReturn(openBrace0);   //"{"
  getToken_ExpectAndReturn(NAME1);        //"NAME1"
  getToken_ExpectAndReturn(colon0);       //":"
  getToken_ExpectAndReturn(int20);        //"20"
  getToken_ExpectAndReturn(dollarSign);

  jsonObj=createJsonObject();
  Try{
    jsonTok=jsonParse(jsonObj);
    TEST_FAIL_MESSAGE("Expecting ERR_ACCESS_DENIED but none thrown.");
  }Catch(err){
    TEST_ASSERT_EQUAL_STRING("ERROR[9]:ACCESS DENIED!!!The Json List is not completed.",err->errorMsg);
    TEST_ASSERT_EQUAL(ERR_ACCESS_DENIED,err->errorCode);
    free(err);
  }
  free(jsonObj);
  free(jsonTok);

  TOKEN_FREE;
}

/**
 * at state NUMBER,
 * Test if caret token has been passed in after int20 token
 *
 *  { "NAME1":20^
 *
 */
void test_Simple_JSON_List_with_Caret_Token_Passed_in_after_Integer_Token_should_Throw_Error()
{
  JsonObject *jsonObj=NULL;
  Token *jsonTok;
  ErrorObject *err;

  TOKEN_DECLARE;

  getToken_ExpectAndReturn(openBrace0);   //"{"
  getToken_ExpectAndReturn(NAME1);        //"NAME1"
  getToken_ExpectAndReturn(colon0);       //":"
  getToken_ExpectAndReturn(int20);        //"20"
  getToken_ExpectAndReturn(caret);        //"^"
  getToken_ExpectAndReturn(dollarSign);

  jsonObj=createJsonObject();
  Try{
    jsonTok=jsonParse(jsonObj);
    TEST_FAIL_MESSAGE("Expecting ERR_EXPECT_OPERATOR but none thrown.");
  }Catch(err){
    TEST_ASSERT_EQUAL_STRING("ERROR[7]:Expected Operator '}' or ',' but get '^'.",err->errorMsg);
    TEST_ASSERT_EQUAL(ERR_EXPECT_OPERATOR,err->errorCode);
    free(err);
  }
  free(jsonObj);
  free(jsonTok);

  TOKEN_FREE;
}

/**
 * at state NUMBER,
 * Test if JS token has been passed in after int20 token
 *
 *  { "NAME1":20"JS"
 *
 */
void test_Simple_JSON_List_with_String_Token_Passed_in_after_Integer_Token_should_Throw_Error()
{
  JsonObject *jsonObj=NULL;
  Token *jsonTok;
  ErrorObject *err;

  TOKEN_DECLARE;

  getToken_ExpectAndReturn(openBrace0);   //"{"
  getToken_ExpectAndReturn(NAME1);        //"NAME1"
  getToken_ExpectAndReturn(colon0);       //":"
  getToken_ExpectAndReturn(int20);        //"20"
  getToken_ExpectAndReturn(JS);           //"JS"
  getToken_ExpectAndReturn(dollarSign);

  jsonObj=createJsonObject();
  Try{
    jsonTok=jsonParse(jsonObj);
    TEST_FAIL_MESSAGE("Expecting ERR_EXPECT_OPERATOR but none thrown.");
  }Catch(err){
    TEST_ASSERT_EQUAL_STRING("ERROR[7]:Expected Operator '}' or ',' but get 'JS'.",err->errorMsg);
    TEST_ASSERT_EQUAL(ERR_EXPECT_OPERATOR,err->errorCode);
    free(err);
  }
  free(jsonObj);
  free(jsonTok);

  TOKEN_FREE;
}

/**
 * at state NUMBER,
 * Test if JS token has been passed in after int20 token
 *
 *  { "NAME1":20 30
 *
 */
void test_Simple_JSON_List_with_Integer_Token_Passed_in_after_Integer_Token_should_Throw_Error()
{
  JsonObject *jsonObj=NULL;
  Token *jsonTok;
  ErrorObject *err;

  TOKEN_DECLARE;

  getToken_ExpectAndReturn(openBrace0);   //"{"
  getToken_ExpectAndReturn(NAME1);        //"NAME1"
  getToken_ExpectAndReturn(colon0);       //":"
  getToken_ExpectAndReturn(int20);        //"20"
  getToken_ExpectAndReturn(int30);        //"30"
  getToken_ExpectAndReturn(dollarSign);

  jsonObj=createJsonObject();
  Try{
    jsonTok=jsonParse(jsonObj);
    TEST_FAIL_MESSAGE("Expecting ERR_EXPECT_OPERATOR but none thrown.");
  }Catch(err){
    TEST_ASSERT_EQUAL_STRING("ERROR[7]:Expected Operator '}' or ',' but get '30'.",err->errorMsg);
    TEST_ASSERT_EQUAL(ERR_EXPECT_OPERATOR,err->errorCode);
    free(err);
  }
  free(jsonObj);
  free(jsonTok);

  TOKEN_FREE;
}

/**
 * at state OBJECT,
 * Test if no token has been passed in after coma token
 *
 *  { "NAME1":20,
 *
 */
void test_Simple_JSON_List_with_no_Token_Passed_in_after_Coma_Token_should_Throw_Error()
{
  JsonObject *jsonObj=NULL;
  Token *jsonTok;
  ErrorObject *err;

  TOKEN_DECLARE;

  getToken_ExpectAndReturn(openBrace0);   //"{"
  getToken_ExpectAndReturn(NAME1);        //"NAME1"
  getToken_ExpectAndReturn(colon0);       //":"
  getToken_ExpectAndReturn(int20);        //"20"
  getToken_ExpectAndReturn(coma0);        //","
  getToken_ExpectAndReturn(dollarSign);

  jsonObj=createJsonObject();
  Try{
    jsonTok=jsonParse(jsonObj);
    TEST_FAIL_MESSAGE("Expecting ERR_ACCESS_DENIED but none thrown.");
  }Catch(err){
    TEST_ASSERT_EQUAL_STRING("ERROR[9]:ACCESS DENIED!!!The Json List is not completed.",err->errorMsg);
    TEST_ASSERT_EQUAL(ERR_ACCESS_DENIED,err->errorCode);
    free(err);
  }
  free(jsonObj);
  free(jsonTok);

  TOKEN_FREE;
}

/**
 * Test for complete Simple JsonList
 *
 *  {
 *    "NAME1":"JS",
 *    "NAME2":"STEVEN"
 *  }
 */
void test_Simple_JSON_List_for_complete_form()
{
  JsonObject *jsonObj=NULL;
  Token *jsonTok;
  Iterator *iter;
  ErrorObject *err;

  TOKEN_DECLARE;

  getToken_ExpectAndReturn(openBrace0);    //"{"
  getToken_ExpectAndReturn(NAME1);         //"NAME1"
  getToken_ExpectAndReturn(colon0);        //":"
  getToken_ExpectAndReturn(JS);            //"JS"
  getToken_ExpectAndReturn(coma0);          //","
  getToken_ExpectAndReturn(AGE);           //"AGE"
  getToken_ExpectAndReturn(colon1);        //":"
  getToken_ExpectAndReturn(int20);         //20
  getToken_ExpectAndReturn(closeBrace0);   //"}"
  getToken_ExpectAndReturn(dollarSign);

  jsonObj=createJsonObject();
  Try{
    jsonTok=jsonParse(jsonObj);
  }Catch(err){
    TEST_FAIL_JSON("unexpected error occurred =>'%s'",err->errorMsg);
    free(err);
  }

  TEST_ASSERT_EQUAL(END,jsonObj->state);

  iter=createIterator(((JsonToken *)jsonTok)->list);
  TEST_ASSERT_EQUAL_STRING("{",((OperatorToken *)(iter->current->value))->symbol);
  iter=iteratorGetNext(iter);
  TEST_ASSERT_KEY_VALUE(NAME1,JS, iter->current);
  iter=iteratorGetNext(iter);
  TEST_ASSERT_KEY_VALUE(AGE,int20, iter->current);
  iter=iteratorGetNext(iter);
  TEST_ASSERT_EQUAL_STRING("}",((OperatorToken *)(iter->current->value))->symbol);

  free(jsonObj);
  free(jsonTok);
  free(iter);

  TOKEN_FREE;
}

/**
 * Test if Extra Token Passed into complete Simple JsonList
 *
 *  {
 *    "NAME1":"JS",
 *    "NAME2":"STEVEN"
 *  }^
 */
void test_JSON_List_with_Extra_Token_Passed_into_Simple_JSON_List()
{
  JsonObject *jsonObj=NULL;
  Token *jsonTok;
  Iterator *iter;
  ErrorObject *err;

  TOKEN_DECLARE;

  getToken_ExpectAndReturn(openBrace0);    //"{"
  getToken_ExpectAndReturn(NAME1);         //"NAME1"
  getToken_ExpectAndReturn(colon0);        //":"
  getToken_ExpectAndReturn(JS);            //"JS"
  getToken_ExpectAndReturn(coma0);         //","
  getToken_ExpectAndReturn(AGE);           //"AGE"
  getToken_ExpectAndReturn(colon1);        //":"
  getToken_ExpectAndReturn(int20);         //20
  getToken_ExpectAndReturn(closeBrace0);   //"}"
  getToken_ExpectAndReturn(caret);         //"^"
  getToken_ExpectAndReturn(dollarSign);

  jsonObj=createJsonObject();
  Try{
    jsonTok=jsonParse(jsonObj);
    TEST_FAIL_MESSAGE("Expecting ERR_ACCESS_DENIED but none thrown.");
  }Catch(err){
    TEST_ASSERT_EQUAL_STRING("ERROR[9]:ACCESS DENIED!!!The Json List already completed.",err->errorMsg);
    TEST_ASSERT_EQUAL(ERR_ACCESS_DENIED,err->errorCode);
    free(err);
  }

  free(jsonObj);
  free(jsonTok);
  free(iter);

  TOKEN_FREE;
}

/**
 * Test if the Recursion JsonList is not complete
 *
 *  {
 *    "NAME1":"JS",
 *    "AGE"  :{
 *
 */
void test_Recursion_JSON_List_with_not_completed_List_should_Throw_Error()
{
  JsonObject *jsonObj=NULL;
  Token *jsonTok;
  ErrorObject *err;

  TOKEN_DECLARE;

  getToken_ExpectAndReturn(openBrace0);    //"{"
  getToken_ExpectAndReturn(NAME1);         //"NAME1"
  getToken_ExpectAndReturn(colon0);        //":"
  getToken_ExpectAndReturn(JS);            //"JS"
  getToken_ExpectAndReturn(coma0);          //","
  getToken_ExpectAndReturn(AGE);           //"AGE"
  getToken_ExpectAndReturn(colon1);        //":"
  getToken_ExpectAndReturn(openBrace1);    //"{"
  getToken_ExpectAndReturn(dollarSign);

  jsonObj=createJsonObject();
  Try{
    jsonTok=jsonParse(jsonObj);
    TEST_FAIL_MESSAGE("Expecting ERR_ACCESS_DENIED but none thrown.");
  }Catch(err){
    TEST_ASSERT_EQUAL_STRING("ERROR[9]:ACCESS DENIED!!!The Json List is not completed.",err->errorMsg);
    TEST_ASSERT_EQUAL(ERR_ACCESS_DENIED,err->errorCode);
    free(err);
  }

  free(jsonObj);
  free(jsonTok);

  TOKEN_FREE;
}

/**
 * at state OBJECT,
 * Test if STEVEN token has been passed in after openBrace token
 *
 *  {
 *    "NAME1":"JS",
 *    "AGE"  :{"STEVEN"
 *
 */
void test_Recursion_JSON_List_with_String_Token_Passed_in_after_open_Brace_Token_should_Throw_Error()
{
  JsonObject *jsonObj=NULL;
  Token *jsonTok;
  ErrorObject *err;

  TOKEN_DECLARE;

  getToken_ExpectAndReturn(openBrace0);    //"{"
  getToken_ExpectAndReturn(NAME1);         //"NAME1"
  getToken_ExpectAndReturn(colon0);        //":"
  getToken_ExpectAndReturn(JS);            //"JS"
  getToken_ExpectAndReturn(coma0);          //","
  getToken_ExpectAndReturn(AGE);           //"AGE"
  getToken_ExpectAndReturn(colon1);        //":"
  getToken_ExpectAndReturn(openBrace1);    //"{"
  getToken_ExpectAndReturn(STEVEN);        //"STEVEN"
  getToken_ExpectAndReturn(dollarSign);

  jsonObj=createJsonObject();
  Try{
    jsonTok=jsonParse(jsonObj);
    TEST_FAIL_MESSAGE("Expecting ERR_EXPECT_IDEN but none thrown.");
  }Catch(err){
    TEST_ASSERT_EQUAL_STRING("ERROR[8]:Illegal 'Key'.Expected an Identifier for 'Key'.",err->errorMsg);
    TEST_ASSERT_EQUAL(ERR_EXPECT_IDEN,err->errorCode);
    free(err);
  }

  free(jsonObj);
  free(jsonTok);

  TOKEN_FREE;
}

/**
 * at state WAIT_FOR_COLON,
 * Test if no token has been passed in after NAME2 token
 *
 *  {
 *    "NAME1":"JS",
 *    "AGE"  :{"NAME2"
 *
 */
void test_Recursion_JSON_List_with_no_Token_Passed_in_after_Key_Token_should_Throw_Error()
{
  JsonObject *jsonObj=NULL;
  Token *jsonTok;
  ErrorObject *err;

  TOKEN_DECLARE;

  getToken_ExpectAndReturn(openBrace0);    //"{"
  getToken_ExpectAndReturn(NAME1);         //"NAME1"
  getToken_ExpectAndReturn(colon0);        //":"
  getToken_ExpectAndReturn(JS);            //"JS"
  getToken_ExpectAndReturn(coma0);          //","
  getToken_ExpectAndReturn(AGE);           //"AGE"
  getToken_ExpectAndReturn(colon1);        //":"
  getToken_ExpectAndReturn(openBrace1);    //"{"
  getToken_ExpectAndReturn(NAME2);         //"NAME2"
  getToken_ExpectAndReturn(dollarSign);

  jsonObj=createJsonObject();
  Try{
    jsonTok=jsonParse(jsonObj);
    TEST_FAIL_MESSAGE("Expecting ERR_ACCESS_DENIED but none thrown.");
  }Catch(err){
    TEST_ASSERT_EQUAL_STRING("ERROR[9]:ACCESS DENIED!!!The Json List is not completed.",err->errorMsg);
    TEST_ASSERT_EQUAL(ERR_ACCESS_DENIED,err->errorCode);
    free(err);
  }

  free(jsonObj);
  free(jsonTok);

  TOKEN_FREE;
}

/**
 * at state WAIT_FOR_COLON,
 * Test if Caret token has been passed in after NAME2 token
 *
 *  {
 *    "NAME1":"JS",
 *    "AGE"  :{"NAME2"^
 *
 */
void test_Recursion_JSON_List_with_Caret_Token_Passed_in_after_Key_Token_should_Throw_Error()
{
  JsonObject *jsonObj=NULL;
  Token *jsonTok;
  ErrorObject *err;

  TOKEN_DECLARE;

  getToken_ExpectAndReturn(openBrace0);    //"{"
  getToken_ExpectAndReturn(NAME1);         //"NAME1"
  getToken_ExpectAndReturn(colon0);        //":"
  getToken_ExpectAndReturn(JS);            //"JS"
  getToken_ExpectAndReturn(coma0);          //","
  getToken_ExpectAndReturn(AGE);           //"AGE"
  getToken_ExpectAndReturn(colon1);        //":"
  getToken_ExpectAndReturn(openBrace1);    //"{"
  getToken_ExpectAndReturn(NAME2);         //"NAME2"
  getToken_ExpectAndReturn(caret);         //"^"
  getToken_ExpectAndReturn(dollarSign);

  jsonObj=createJsonObject();
  Try{
    jsonTok=jsonParse(jsonObj);
    TEST_FAIL_MESSAGE("Expecting ERR_EXPECT_OPERATOR but none thrown.");
  }Catch(err){
    TEST_ASSERT_EQUAL_STRING("ERROR[7]:Expected ':' but get '^'.",err->errorMsg);
    TEST_ASSERT_EQUAL(ERR_EXPECT_OPERATOR,err->errorCode);
    free(err);
  }

  free(jsonObj);
  free(jsonTok);

  TOKEN_FREE;
}

/**
 * at state WAIT_FOR_COLON,
 * Test if STEVEN token has been passed in after NAME2 token
 *
 *  {
 *    "NAME1":"JS",
 *    "AGE"  :{"NAME2""STEVEN"
 *
 */
void test_Recursion_JSON_List_with_String_Token_Passed_in_after_Key_Token_should_Throw_Error()
{
  JsonObject *jsonObj=NULL;
  Token *jsonTok;
  ErrorObject *err;

  TOKEN_DECLARE;

  getToken_ExpectAndReturn(openBrace0);    //"{"
  getToken_ExpectAndReturn(NAME1);         //"NAME1"
  getToken_ExpectAndReturn(colon0);        //":"
  getToken_ExpectAndReturn(JS);            //"JS"
  getToken_ExpectAndReturn(coma0);          //","
  getToken_ExpectAndReturn(AGE);           //"AGE"
  getToken_ExpectAndReturn(colon1);        //":"
  getToken_ExpectAndReturn(openBrace1);    //"{"
  getToken_ExpectAndReturn(NAME2);         //"NAME2"
  getToken_ExpectAndReturn(STEVEN);        //"STEVEN"
  getToken_ExpectAndReturn(dollarSign);

  jsonObj=createJsonObject();
  Try{
    jsonTok=jsonParse(jsonObj);
    TEST_FAIL_MESSAGE("Expecting ERR_EXPECT_OPERATOR but none thrown.");
  }Catch(err){
    TEST_ASSERT_EQUAL_STRING("ERROR[7]:Expected ':' but get 'STEVEN'.",err->errorMsg);
    TEST_ASSERT_EQUAL(ERR_EXPECT_OPERATOR,err->errorCode);
    free(err);
  }

  free(jsonObj);
  free(jsonTok);

  TOKEN_FREE;
}

/**
 * at state WAIT_FOR_COLON,
 * Test if int20 token has been passed in after NAME2 token
 *
 *  {
 *    "NAME1":"JS",
 *    "AGE"  :{"NAME2"20
 *
 */
void test_Recursion_JSON_List_with_Integer_Token_Passed_in_after_Key_Token_should_Throw_Error()
{
  JsonObject *jsonObj=NULL;
  Token *jsonTok;
  ErrorObject *err;

  TOKEN_DECLARE;

  getToken_ExpectAndReturn(openBrace0);    //"{"
  getToken_ExpectAndReturn(NAME1);         //"NAME1"
  getToken_ExpectAndReturn(colon0);        //":"
  getToken_ExpectAndReturn(JS);            //"JS"
  getToken_ExpectAndReturn(coma0);          //","
  getToken_ExpectAndReturn(AGE);           //"AGE"
  getToken_ExpectAndReturn(colon1);        //":"
  getToken_ExpectAndReturn(openBrace1);    //"{"
  getToken_ExpectAndReturn(NAME2);         //"NAME2"
  getToken_ExpectAndReturn(int20);         //"20"
  getToken_ExpectAndReturn(dollarSign);

  jsonObj=createJsonObject();
  Try{
    jsonTok=jsonParse(jsonObj);
    TEST_FAIL_MESSAGE("Expecting ERR_EXPECT_OPERATOR but none thrown.");
  }Catch(err){
    TEST_ASSERT_EQUAL_STRING("ERROR[7]:Expected ':' but get '20'.",err->errorMsg);
    TEST_ASSERT_EQUAL(ERR_EXPECT_OPERATOR,err->errorCode);
    free(err);
  }

  free(jsonObj);
  free(jsonTok);

  TOKEN_FREE;
}

/**
 * at state VALUE,
 * Test if no token has been passed in after Colon token
 *
 *  {
 *    "NAME1":"JS",
 *    "AGE"  :{"NAME2":
 *
 */
void test_Recursion_JSON_List_with_no_Token_Passed_in_after_Colon_Token_should_Throw_Error()
{
  JsonObject *jsonObj=NULL;
  Token *jsonTok;
  ErrorObject *err;

  TOKEN_DECLARE;

  getToken_ExpectAndReturn(openBrace0);    //"{"
  getToken_ExpectAndReturn(NAME1);         //"NAME1"
  getToken_ExpectAndReturn(colon0);        //":"
  getToken_ExpectAndReturn(JS);            //"JS"
  getToken_ExpectAndReturn(coma0);          //","
  getToken_ExpectAndReturn(AGE);           //"AGE"
  getToken_ExpectAndReturn(colon1);        //":"
  getToken_ExpectAndReturn(openBrace1);    //"{"
  getToken_ExpectAndReturn(NAME2);         //"NAME2"
  getToken_ExpectAndReturn(colon2);        //":"
  getToken_ExpectAndReturn(dollarSign);

  jsonObj=createJsonObject();
  Try{
    jsonTok=jsonParse(jsonObj);
    TEST_FAIL_MESSAGE("Expecting ERR_ACCESS_DENIED but none thrown.");
  }Catch(err){
    TEST_ASSERT_EQUAL_STRING("ERROR[9]:ACCESS DENIED!!!The Json List is not completed.",err->errorMsg);
    TEST_ASSERT_EQUAL(ERR_ACCESS_DENIED,err->errorCode);
    free(err);
  }

  free(jsonObj);
  free(jsonTok);

  TOKEN_FREE;
}

/**
 * at state VALUE,
 * Test if closeBrace token has been passed in after Colon token
 *
 *  {
 *    "NAME1":"JS",
 *    "AGE"  :{"NAME2":}
 *
 */
void test_Recursion_JSON_List_with_close_Brace_Token_Passed_in_after_Colon_Token_should_Throw_Error()
{
  JsonObject *jsonObj=NULL;
  Token *jsonTok;
  ErrorObject *err;

  TOKEN_DECLARE;

  getToken_ExpectAndReturn(openBrace0);    //"{"
  getToken_ExpectAndReturn(NAME1);         //"NAME1"
  getToken_ExpectAndReturn(colon0);        //":"
  getToken_ExpectAndReturn(JS);            //"JS"
  getToken_ExpectAndReturn(coma0);          //","
  getToken_ExpectAndReturn(AGE);           //"AGE"
  getToken_ExpectAndReturn(colon1);        //":"
  getToken_ExpectAndReturn(openBrace1);    //"{"
  getToken_ExpectAndReturn(NAME2);         //"NAME2"
  getToken_ExpectAndReturn(colon2);        //":"
  getToken_ExpectAndReturn(closeBrace0);   //"}"
  getToken_ExpectAndReturn(dollarSign);

  jsonObj=createJsonObject();
  Try{
    jsonTok=jsonParse(jsonObj);
    TEST_FAIL_MESSAGE("Expecting ERR_ILLEGAL_VALUE but none thrown.");
  }Catch(err){
    TEST_ASSERT_EQUAL_STRING("ERROR[10]:Illegal 'Value'.Expected an Integer/String/Float for 'Value'.",err->errorMsg);
    TEST_ASSERT_EQUAL(ERR_ILLEGAL_VALUE,err->errorCode);
    free(err);
  }

  free(jsonObj);
  free(jsonTok);

  TOKEN_FREE;
}

/**
 * at state STRING,
 * Test if no token has been passed in after STEVEN token
 *
 *  {
 *    "NAME1":"JS",
 *    "AGE"  :{"NAME2":"STEVEN"
 *
 */
void test_Recursion_JSON_List_with_no_Token_Passed_in_after_String_Token_should_Throw_Error()
{
  JsonObject *jsonObj=NULL;
  Token *jsonTok;
  ErrorObject *err;

  TOKEN_DECLARE;

  getToken_ExpectAndReturn(openBrace0);    //"{"
  getToken_ExpectAndReturn(NAME1);         //"NAME1"
  getToken_ExpectAndReturn(colon0);        //":"
  getToken_ExpectAndReturn(JS);            //"JS"
  getToken_ExpectAndReturn(coma0);          //","
  getToken_ExpectAndReturn(AGE);           //"AGE"
  getToken_ExpectAndReturn(colon1);        //":"
  getToken_ExpectAndReturn(openBrace1);    //"{"
  getToken_ExpectAndReturn(NAME2);         //"NAME2"
  getToken_ExpectAndReturn(colon2);        //":"
  getToken_ExpectAndReturn(STEVEN);        //"STEVEN"
  getToken_ExpectAndReturn(dollarSign);

  jsonObj=createJsonObject();
  Try{
    jsonTok=jsonParse(jsonObj);
    TEST_FAIL_MESSAGE("Expecting ERR_ACCESS_DENIED but none thrown.");
  }Catch(err){
    TEST_ASSERT_EQUAL_STRING("ERROR[9]:ACCESS DENIED!!!The Json List is not completed.",err->errorMsg);
    TEST_ASSERT_EQUAL(ERR_ACCESS_DENIED,err->errorCode);
    free(err);
  }

  free(jsonObj);
  free(jsonTok);

  TOKEN_FREE;
}

/**
 * at state STRING,
 * Test if caret token has been passed in after STEVEN token
 *
 *  {
 *    "NAME1":"JS",
 *    "AGE"  :{"NAME2":"STEVEN"^
 *
 */
void test_Recursion_JSON_List_with_Caret_Token_Passed_in_after_String_Token_should_Throw_Error()
{
  JsonObject *jsonObj=NULL;
  Token *jsonTok;
  ErrorObject *err;

  TOKEN_DECLARE;

  getToken_ExpectAndReturn(openBrace0);    //"{"
  getToken_ExpectAndReturn(NAME1);         //"NAME1"
  getToken_ExpectAndReturn(colon0);        //":"
  getToken_ExpectAndReturn(JS);            //"JS"
  getToken_ExpectAndReturn(coma0);          //","
  getToken_ExpectAndReturn(AGE);           //"AGE"
  getToken_ExpectAndReturn(colon1);        //":"
  getToken_ExpectAndReturn(openBrace1);    //"{"
  getToken_ExpectAndReturn(NAME2);         //"NAME2"
  getToken_ExpectAndReturn(colon2);        //":"
  getToken_ExpectAndReturn(STEVEN);        //"STEVEN"
  getToken_ExpectAndReturn(caret);         //"^"
  getToken_ExpectAndReturn(dollarSign);

  jsonObj=createJsonObject();
  Try{
    jsonTok=jsonParse(jsonObj);
    TEST_FAIL_MESSAGE("Expecting ERR_EXPECT_OPERATOR but none thrown.");
  }Catch(err){
    TEST_ASSERT_EQUAL_STRING("ERROR[7]:Expected Operator '}' or ',' but get '^'.",err->errorMsg);
    TEST_ASSERT_EQUAL(ERR_EXPECT_OPERATOR,err->errorCode);
    free(err);
  }

  free(jsonObj);
  free(jsonTok);

  TOKEN_FREE;
}

/**
 * at state STRING,
 * Test if YEN token has been passed in after STEVEN token
 *
 *  {
 *    "NAME1":"JS",
 *    "AGE"  :{"NAME2":"STEVEN""YEN"
 *
 */
void test_Recursion_JSON_List_with_String_Token_Passed_in_after_String_Token_should_Throw_Error()
{
  JsonObject *jsonObj=NULL;
  Token *jsonTok;
  ErrorObject *err;

  TOKEN_DECLARE;

  getToken_ExpectAndReturn(openBrace0);    //"{"
  getToken_ExpectAndReturn(NAME1);         //"NAME1"
  getToken_ExpectAndReturn(colon0);        //":"
  getToken_ExpectAndReturn(JS);            //"JS"
  getToken_ExpectAndReturn(coma0);          //","
  getToken_ExpectAndReturn(AGE);           //"AGE"
  getToken_ExpectAndReturn(colon1);        //":"
  getToken_ExpectAndReturn(openBrace1);    //"{"
  getToken_ExpectAndReturn(NAME2);         //"NAME2"
  getToken_ExpectAndReturn(colon2);        //":"
  getToken_ExpectAndReturn(STEVEN);        //"STEVEN"
  getToken_ExpectAndReturn(YEN);           //"YEN"
  getToken_ExpectAndReturn(dollarSign);

  jsonObj=createJsonObject();
  Try{
    jsonTok=jsonParse(jsonObj);
    TEST_FAIL_MESSAGE("Expecting ERR_EXPECT_OPERATOR but none thrown.");
  }Catch(err){
    TEST_ASSERT_EQUAL_STRING("ERROR[7]:Expected Operator '}' or ',' but get 'YEN'.",err->errorMsg);
    TEST_ASSERT_EQUAL(ERR_EXPECT_OPERATOR,err->errorCode);
    free(err);
  }

  free(jsonObj);
  free(jsonTok);

  TOKEN_FREE;
}

/**
 * at state STRING,
 * Test if int20 token has been passed in after STEVEN token
 *
 *  {
 *    "NAME1":"JS",
 *    "AGE"  :{"NAME2":"STEVEN"20
 *
 */
void test_Recursion_JSON_List_with_Integer_Token_Passed_in_after_String_Token_should_Throw_Error()
{
  JsonObject *jsonObj=NULL;
  Token *jsonTok;
  ErrorObject *err;

  TOKEN_DECLARE;

  getToken_ExpectAndReturn(openBrace0);    //"{"
  getToken_ExpectAndReturn(NAME1);         //"NAME1"
  getToken_ExpectAndReturn(colon0);        //":"
  getToken_ExpectAndReturn(JS);            //"JS"
  getToken_ExpectAndReturn(coma0);          //","
  getToken_ExpectAndReturn(AGE);           //"AGE"
  getToken_ExpectAndReturn(colon1);        //":"
  getToken_ExpectAndReturn(openBrace1);    //"{"
  getToken_ExpectAndReturn(NAME2);         //"NAME2"
  getToken_ExpectAndReturn(colon2);        //":"
  getToken_ExpectAndReturn(STEVEN);        //"STEVEN"
  getToken_ExpectAndReturn(int20);         //"20"
  getToken_ExpectAndReturn(dollarSign);

  jsonObj=createJsonObject();
  Try{
    jsonTok=jsonParse(jsonObj);
    TEST_FAIL_MESSAGE("Expecting ERR_EXPECT_OPERATOR but none thrown.");
  }Catch(err){
    TEST_ASSERT_EQUAL_STRING("ERROR[7]:Expected Operator '}' or ',' but get '20'.",err->errorMsg);
    TEST_ASSERT_EQUAL(ERR_EXPECT_OPERATOR,err->errorCode);
    free(err);
  }

  free(jsonObj);
  free(jsonTok);

  TOKEN_FREE;
}

/**
 * at state NUMBER,
 * Test if caret token has been passed in after int20 token
 *
 *  {
 *    "NAME1":"JS",
 *    "AGE"  :{"NAME2":20
 *
 */
void test_Recursion_JSON_List_with_no_Token_Passed_in_after_Integer_Token_should_Throw_Error()
{
  JsonObject *jsonObj=NULL;
  Token *jsonTok;
  ErrorObject *err;

  TOKEN_DECLARE;

  getToken_ExpectAndReturn(openBrace0);    //"{"
  getToken_ExpectAndReturn(NAME1);         //"NAME1"
  getToken_ExpectAndReturn(colon0);        //":"
  getToken_ExpectAndReturn(JS);            //"JS"
  getToken_ExpectAndReturn(coma0);          //","
  getToken_ExpectAndReturn(AGE);           //"AGE"
  getToken_ExpectAndReturn(colon1);        //":"
  getToken_ExpectAndReturn(openBrace1);    //"{"
  getToken_ExpectAndReturn(NAME2);         //"NAME2"
  getToken_ExpectAndReturn(colon2);        //":"
  getToken_ExpectAndReturn(int20);         //"20"
  getToken_ExpectAndReturn(dollarSign);

  jsonObj=createJsonObject();
  Try{
    jsonTok=jsonParse(jsonObj);
    TEST_FAIL_MESSAGE("Expecting ERR_ACCESS_DENIED but none thrown.");
  }Catch(err){
    TEST_ASSERT_EQUAL_STRING("ERROR[9]:ACCESS DENIED!!!The Json List is not completed.",err->errorMsg);
    TEST_ASSERT_EQUAL(ERR_ACCESS_DENIED,err->errorCode);
    free(err);
  }

  free(jsonObj);
  free(jsonTok);

  TOKEN_FREE;
}

/**
 * at state NUMBER,
 * Test if caret token has been passed in after int20 token
 *
 *  {
 *    "NAME1":"JS",
 *    "AGE"  :{"NAME2":20^
 *
 */
void test_Recursion_JSON_List_with_Caret_Token_Passed_in_after_Integer_Token_should_Throw_Error()
{
  JsonObject *jsonObj=NULL;
  Token *jsonTok;
  ErrorObject *err;

  TOKEN_DECLARE;

  getToken_ExpectAndReturn(openBrace0);    //"{"
  getToken_ExpectAndReturn(NAME1);         //"NAME1"
  getToken_ExpectAndReturn(colon0);        //":"
  getToken_ExpectAndReturn(JS);            //"JS"
  getToken_ExpectAndReturn(coma0);          //","
  getToken_ExpectAndReturn(AGE);           //"AGE"
  getToken_ExpectAndReturn(colon1);        //":"
  getToken_ExpectAndReturn(openBrace1);    //"{"
  getToken_ExpectAndReturn(NAME2);         //"NAME2"
  getToken_ExpectAndReturn(colon2);        //":"
  getToken_ExpectAndReturn(int20);         //"20"
  getToken_ExpectAndReturn(caret);         //"^"
  getToken_ExpectAndReturn(dollarSign);

  jsonObj=createJsonObject();
  Try{
    jsonTok=jsonParse(jsonObj);
    TEST_FAIL_MESSAGE("Expecting ERR_EXPECT_OPERATOR but none thrown.");
  }Catch(err){
    TEST_ASSERT_EQUAL_STRING("ERROR[7]:Expected Operator '}' or ',' but get '^'.",err->errorMsg);
    TEST_ASSERT_EQUAL(ERR_EXPECT_OPERATOR,err->errorCode);
    free(err);
  }

  free(jsonObj);
  free(jsonTok);

  TOKEN_FREE;
}

/**
 * at state NUMBER,
 * Test if YEN token has been passed in after int20 token
 *
 *  {
 *    "NAME1":"JS",
 *    "AGE"  :{"NAME2":20"YEN"
 *
 */
void test_Recursion_JSON_List_with_String_Token_Passed_in_after_Integer_Token_should_Throw_Error()
{
  JsonObject *jsonObj=NULL;
  Token *jsonTok;
  ErrorObject *err;

  TOKEN_DECLARE;

  getToken_ExpectAndReturn(openBrace0);    //"{"
  getToken_ExpectAndReturn(NAME1);         //"NAME1"
  getToken_ExpectAndReturn(colon0);        //":"
  getToken_ExpectAndReturn(JS);            //"JS"
  getToken_ExpectAndReturn(coma0);         //","
  getToken_ExpectAndReturn(AGE);           //"AGE"
  getToken_ExpectAndReturn(colon1);        //":"
  getToken_ExpectAndReturn(openBrace1);    //"{"
  getToken_ExpectAndReturn(NAME2);         //"NAME2"
  getToken_ExpectAndReturn(colon2);        //":"
  getToken_ExpectAndReturn(int20);         //"20"
  getToken_ExpectAndReturn(YEN);           //"YEN"
  getToken_ExpectAndReturn(dollarSign);

  jsonObj=createJsonObject();
  Try{
    jsonTok=jsonParse(jsonObj);
    TEST_FAIL_MESSAGE("Expecting ERR_EXPECT_OPERATOR but none thrown.");
  }Catch(err){
    TEST_ASSERT_EQUAL_STRING("ERROR[7]:Expected Operator '}' or ',' but get 'YEN'.",err->errorMsg);
    TEST_ASSERT_EQUAL(ERR_EXPECT_OPERATOR,err->errorCode);
    free(err);
  }

  free(jsonObj);
  free(jsonTok);

  TOKEN_FREE;
}

/**
 * at state NUMBER,
 * Test if int30 token has been passed in after int20 token
 *
 *  {
 *    "NAME1":"JS",
 *    "AGE"  :{"NAME2":20 30
 *
 */
void test_Recursion_JSON_List_with_Integer_Token_Passed_in_after_Integer_Token_should_Throw_Error()
{
  JsonObject *jsonObj=NULL;
  Token *jsonTok;
  ErrorObject *err;

  TOKEN_DECLARE;

  getToken_ExpectAndReturn(openBrace0);    //"{"
  getToken_ExpectAndReturn(NAME1);         //"NAME1"
  getToken_ExpectAndReturn(colon0);        //":"
  getToken_ExpectAndReturn(JS);            //"JS"
  getToken_ExpectAndReturn(coma0);         //","
  getToken_ExpectAndReturn(AGE);           //"AGE"
  getToken_ExpectAndReturn(colon1);        //":"
  getToken_ExpectAndReturn(openBrace1);    //"{"
  getToken_ExpectAndReturn(NAME2);         //"NAME2"
  getToken_ExpectAndReturn(colon2);        //":"
  getToken_ExpectAndReturn(int20);         //"20"
  getToken_ExpectAndReturn(int30);         //"30"
  getToken_ExpectAndReturn(dollarSign);

  jsonObj=createJsonObject();
  Try{
    jsonTok=jsonParse(jsonObj);
    TEST_FAIL_MESSAGE("Expecting ERR_EXPECT_OPERATOR but none thrown.");
  }Catch(err){
    TEST_ASSERT_EQUAL_STRING("ERROR[7]:Expected Operator '}' or ',' but get '30'.",err->errorMsg);
    TEST_ASSERT_EQUAL(ERR_EXPECT_OPERATOR,err->errorCode);
    free(err);
  }

  free(jsonObj);
  free(jsonTok);

  TOKEN_FREE;
}

/**
 * at state OBJECT
 * Test if no token has been passed in after coma token
 *
 *  {
 *    "NAME1":"JS",
 *    "AGE"  :{"NAME2":20,
 *
 */
void test_Recursion_JSON_List_with_no_Token_Passed_in_after_coma_Token_should_Throw_Error()
{
  JsonObject *jsonObj=NULL;
  Token *jsonTok;
  ErrorObject *err;

  TOKEN_DECLARE;

  getToken_ExpectAndReturn(openBrace0);    //"{"
  getToken_ExpectAndReturn(NAME1);         //"NAME1"
  getToken_ExpectAndReturn(colon0);        //":"
  getToken_ExpectAndReturn(JS);            //"JS"
  getToken_ExpectAndReturn(coma0);         //","
  getToken_ExpectAndReturn(AGE);           //"AGE"
  getToken_ExpectAndReturn(colon1);        //":"
  getToken_ExpectAndReturn(openBrace1);    //"{"
  getToken_ExpectAndReturn(NAME2);         //"NAME2"
  getToken_ExpectAndReturn(colon2);        //":"
  getToken_ExpectAndReturn(int20);         //"20"
  getToken_ExpectAndReturn(coma1);         //","
  getToken_ExpectAndReturn(dollarSign);

  jsonObj=createJsonObject();
  Try{
    jsonTok=jsonParse(jsonObj);
    TEST_FAIL_MESSAGE("Expecting ERR_ACCESS_DENIED but none thrown.");
  }Catch(err){
    TEST_ASSERT_EQUAL_STRING("ERROR[9]:ACCESS DENIED!!!The Json List is not completed.",err->errorMsg);
    TEST_ASSERT_EQUAL(ERR_ACCESS_DENIED,err->errorCode);
    free(err);
  }

  free(jsonObj);
  free(jsonTok);

  TOKEN_FREE;
}

/**
 * at state WAIT_FOR_OPERATOR
  * Test if no token has been passed in after closeBrace token
 *
 *  {
 *    "NAME1":"JS",
 *    "AGE"  :{"NAME2":20,
 *             "NAME3":"YEN"}
 *
 */
void test_Recursion_JSON_List_with_no_Token_Passed_in_after_close_Brace_Token_should_Throw_Error()
{
  JsonObject *jsonObj=NULL;
  Token *jsonTok;
  ErrorObject *err;

  TOKEN_DECLARE;

  getToken_ExpectAndReturn(openBrace0);    //"{"
  getToken_ExpectAndReturn(NAME1);         //"NAME1"
  getToken_ExpectAndReturn(colon0);        //":"
  getToken_ExpectAndReturn(JS);            //"JS"
  getToken_ExpectAndReturn(coma0);          //","
  getToken_ExpectAndReturn(AGE);           //"AGE"
  getToken_ExpectAndReturn(colon1);        //":"
  getToken_ExpectAndReturn(openBrace1);    //"{"
  getToken_ExpectAndReturn(NAME2);         //"NAME2"
  getToken_ExpectAndReturn(colon2);        //":"
  getToken_ExpectAndReturn(STEVEN);        //"STEVEN"
  getToken_ExpectAndReturn(coma1);          //","
  getToken_ExpectAndReturn(NAME3);         //"NAME3"
  getToken_ExpectAndReturn(colon3);        //":"
  getToken_ExpectAndReturn(YEN);           //"YEN"
  getToken_ExpectAndReturn(closeBrace0);   //"}"
  getToken_ExpectAndReturn(dollarSign);

  jsonObj=createJsonObject();
  Try{
    jsonTok=jsonParse(jsonObj);
    TEST_FAIL_MESSAGE("Expecting ERR_ACCESS_DENIED but none thrown.");
  }Catch(err){
    TEST_ASSERT_EQUAL_STRING("ERROR[9]:ACCESS DENIED!!!The Json List is not completed.",err->errorMsg);
    TEST_ASSERT_EQUAL(ERR_ACCESS_DENIED,err->errorCode);
    free(err);
  }

  free(jsonObj);
  free(jsonTok);

  TOKEN_FREE;
}

/**
 * Test for complete Recursion JsonList
 *
 *  {
 *    "NAME1":"JS",
 *    "AGE"  :{ "NAME2":"STEVEN",
 *              "NAME3":"YEN"}
 *  }
 */
void test_Recursion_JSON_List_for_complete_form()
{
  JsonObject *jsonObj=NULL;
  Token *jsonTok;
  Iterator *iter1,*iter2;
  ErrorObject *err;

  TOKEN_DECLARE;

  getToken_ExpectAndReturn(openBrace0);    //"{"
  getToken_ExpectAndReturn(NAME1);         //"NAME1"
  getToken_ExpectAndReturn(colon0);        //":"
  getToken_ExpectAndReturn(JS);            //"JS"
  getToken_ExpectAndReturn(coma0);          //","
  getToken_ExpectAndReturn(AGE);           //"AGE"
  getToken_ExpectAndReturn(colon1);        //":"
  getToken_ExpectAndReturn(openBrace1);    //"{"
  getToken_ExpectAndReturn(NAME2);         //"NAME2"
  getToken_ExpectAndReturn(colon2);        //":"
  getToken_ExpectAndReturn(STEVEN);        //"STEVEN"
  getToken_ExpectAndReturn(coma1);          //","
  getToken_ExpectAndReturn(NAME3);         //"NAME3"
  getToken_ExpectAndReturn(colon3);        //":"
  getToken_ExpectAndReturn(YEN);           //"YEN"
  getToken_ExpectAndReturn(closeBrace0);   //"}"
  getToken_ExpectAndReturn(closeBrace1);   //"}"
  getToken_ExpectAndReturn(dollarSign);

  jsonObj=createJsonObject();
  Try{
    jsonTok=jsonParse(jsonObj);
  }Catch(err){
    TEST_FAIL_JSON("unexpected error occurred =>'%s'",err->errorMsg);
    free(err);
  }

  TEST_ASSERT_EQUAL(END,jsonObj->state);

  iter1=createIterator(((JsonToken *)jsonTok)->list);
  TEST_ASSERT_EQUAL_STRING("{",((OperatorToken *)(iter1->current->value))->symbol);
  iter1=iteratorGetNext(iter1);
  TEST_ASSERT_KEY_VALUE(NAME1,JS, iter1->current);
  iter1=iteratorGetNext(iter1);
  TEST_ASSERT_KEY(AGE,iter1->current);
  iter2=createIterator(((JsonToken *)(((OperatorToken *)(iter1->current->value))->token[1]))->list);
  TEST_ASSERT_EQUAL_STRING("{",((OperatorToken *)(iter2->current->value))->symbol);
  iter2=iteratorGetNext(iter2);
  TEST_ASSERT_KEY_VALUE(NAME2,STEVEN, iter2->current);
  iter2=iteratorGetNext(iter2);
  TEST_ASSERT_KEY_VALUE(NAME3,YEN, iter2->current);
  iter2=iteratorGetNext(iter2);
  TEST_ASSERT_EQUAL_STRING("}",((OperatorToken *)(iter2->current->value))->symbol);
  iter1=iteratorGetNext(iter1);
  TEST_ASSERT_EQUAL_STRING("}",((OperatorToken *)(iter1->current->value))->symbol);

  free(jsonObj);
  free(jsonTok);
  free(iter2);
  free(iter1);

  TOKEN_FREE;
}

/**
 * Test if extra Token passed into Recursion JsonList
 *
 *  {
 *    "NAME1":"JS",
 *    "AGE"  :{ "NAME2":"STEVEN",
 *              "NAME3":"YEN"}
 *  }^
 */
void test_JSON_List_with_Extra_Token_Passed_into_Recursion_JSON_List()
{
  JsonObject *jsonObj=NULL;
  Token *jsonTok;
  Iterator *iter1,*iter2;
  ErrorObject *err;

  TOKEN_DECLARE;

  getToken_ExpectAndReturn(openBrace0);    //"{"
  getToken_ExpectAndReturn(NAME1);         //"NAME1"
  getToken_ExpectAndReturn(colon0);        //":"
  getToken_ExpectAndReturn(JS);            //"JS"
  getToken_ExpectAndReturn(coma0);          //","
  getToken_ExpectAndReturn(AGE);           //"AGE"
  getToken_ExpectAndReturn(colon1);        //":"
  getToken_ExpectAndReturn(openBrace1);    //"{"
  getToken_ExpectAndReturn(NAME2);         //"NAME2"
  getToken_ExpectAndReturn(colon2);        //":"
  getToken_ExpectAndReturn(STEVEN);        //"STEVEN"
  getToken_ExpectAndReturn(coma1);          //","
  getToken_ExpectAndReturn(NAME3);         //"NAME3"
  getToken_ExpectAndReturn(colon3);        //":"
  getToken_ExpectAndReturn(YEN);           //"YEN"
  getToken_ExpectAndReturn(closeBrace0);   //"}"
  getToken_ExpectAndReturn(closeBrace1);   //"}"
  getToken_ExpectAndReturn(caret);         //"^"
  getToken_ExpectAndReturn(dollarSign);

  jsonObj=createJsonObject();
  Try{
    jsonTok=jsonParse(jsonObj);
    TEST_FAIL_MESSAGE("Expecting ERR_ACCESS_DENIED but none thrown.");
  }Catch(err){
    TEST_ASSERT_EQUAL_STRING("ERROR[9]:ACCESS DENIED!!!The Json List already completed.",err->errorMsg);
    TEST_ASSERT_EQUAL(ERR_ACCESS_DENIED,err->errorCode);
    free(err);
  }

  free(jsonObj);
  free(jsonTok);
  free(iter2);
  free(iter1);

  TOKEN_FREE;
}


/**
 * Test Complex JsonList
 *
 *  {
 *    "NAME1":"JS",
 *    "AGE"  :{ "NAME2":"STEVEN",
 *              "NAME3":{ "NAME4":"ABU" },
 *              "NAME4":"YEN"
 *            },
 *    "ADD"  : 30
 *  }
 */
void test_Complex_Json_List()
{
  JsonObject *jsonObj=NULL;
  Token *jsonTok;
  Iterator *iter1,*iter2,*iter3;
  ErrorObject *err;

  TOKEN_DECLARE;

  getToken_ExpectAndReturn(openBrace0);    //"{"
  getToken_ExpectAndReturn(NAME1);         //"NAME1"
  getToken_ExpectAndReturn(colon0);        //":"
  getToken_ExpectAndReturn(JS);            //"JS"
  getToken_ExpectAndReturn(coma0);         //","
  getToken_ExpectAndReturn(AGE);           //"AGE"
  getToken_ExpectAndReturn(colon1);        //":"
  getToken_ExpectAndReturn(openBrace1);    //"{"
  getToken_ExpectAndReturn(NAME2);         //"NAME2"
  getToken_ExpectAndReturn(colon2);        //":"
  getToken_ExpectAndReturn(STEVEN);        //"STEVEN"
  getToken_ExpectAndReturn(coma1);         //","
  getToken_ExpectAndReturn(NAME3);         //"NAME3"
  getToken_ExpectAndReturn(colon3);        //":"
  getToken_ExpectAndReturn(openBrace2);    //"{"
  getToken_ExpectAndReturn(NAME4);         //"NAME4"
  getToken_ExpectAndReturn(colon4);        //":"
  getToken_ExpectAndReturn(ABU);           //"ABU"
  getToken_ExpectAndReturn(closeBrace0);   //"}"
  getToken_ExpectAndReturn(coma2);         //","
  getToken_ExpectAndReturn(NAME4);         //"NAME4"
  getToken_ExpectAndReturn(colon5);        //":"
  getToken_ExpectAndReturn(YEN);           //"YEN"
  getToken_ExpectAndReturn(closeBrace1);   //"}"
  getToken_ExpectAndReturn(coma3);         //","
  getToken_ExpectAndReturn(ADD);           //"ADD"
  getToken_ExpectAndReturn(colon6);        //":"
  getToken_ExpectAndReturn(int30);         //"30"
  getToken_ExpectAndReturn(closeBrace2);   //"}"
  getToken_ExpectAndReturn(dollarSign);

  jsonObj=createJsonObject();
  Try{
    jsonTok=jsonParse(jsonObj);
  }Catch(err){
    TEST_FAIL_JSON("unexpected error occurred =>'%s'",err->errorMsg);
    free(err);
  }
  
  TEST_ASSERT_EQUAL(END,jsonObj->state);

  iter1=createIterator(((JsonToken *)jsonTok)->list);
  TEST_ASSERT_EQUAL_STRING("{",((OperatorToken *)(iter1->current->value))->symbol);
  iter1=iteratorGetNext(iter1);
  TEST_ASSERT_KEY_VALUE(NAME1,JS, iter1->current);
  iter1=iteratorGetNext(iter1);
  TEST_ASSERT_KEY(AGE,iter1->current);
  iter2=createIterator(((JsonToken *)(((OperatorToken *)(iter1->current->value))->token[1]))->list);
  TEST_ASSERT_EQUAL_STRING("{",((OperatorToken *)(iter2->current->value))->symbol);
  iter2=iteratorGetNext(iter2);
  TEST_ASSERT_KEY_VALUE(NAME2,STEVEN, iter2->current);
  iter2=iteratorGetNext(iter2);
  TEST_ASSERT_KEY(NAME3,iter2->current);
  iter3=createIterator(((JsonToken *)(((OperatorToken *)(iter2->current->value))->token[1]))->list);
  TEST_ASSERT_EQUAL_STRING("{",((OperatorToken *)(iter3->current->value))->symbol);
  iter3=iteratorGetNext(iter3);
  TEST_ASSERT_KEY_VALUE(NAME4,ABU, iter3->current);
  iter3=iteratorGetNext(iter3);
  TEST_ASSERT_EQUAL_STRING("}",((OperatorToken *)(iter3->current->value))->symbol);
  iter2=iteratorGetNext(iter2);
  TEST_ASSERT_KEY_VALUE(NAME4,YEN, iter2->current);
  iter2=iteratorGetNext(iter2);
  TEST_ASSERT_EQUAL_STRING("}",((OperatorToken *)(iter2->current->value))->symbol);
  iter1=iteratorGetNext(iter1);
  TEST_ASSERT_KEY_VALUE(ADD,int30, iter1->current);
  iter1=iteratorGetNext(iter1);
  TEST_ASSERT_EQUAL_STRING("}",((OperatorToken *)(iter1->current->value))->symbol);

  free(jsonObj);
  free(jsonTok);
  free(iter1);
  free(iter2);
  free(iter3);

  TOKEN_FREE;
}


