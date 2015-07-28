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
  Token *INT=malloc(sizeof(Token));
  Token *FLOAT=malloc(sizeof(Token));
  Token *IDEN=malloc(sizeof(Token));
  Token *STR=malloc(sizeof(Token));
  Token *OPE=malloc(sizeof(Token));

  ((IntegerToken *)(INT))-> value=100;
  ((FloatToken *)(FLOAT))-> value=12.34;
  ((IdentifierToken *)(IDEN))-> name="JangSing";
  ((StringToken *)(STR))-> name="Wong";
  ((OperatorToken *)(OPE))-> symbol="{";

	getToken_ExpectAndReturn(INT);
	getToken_ExpectAndReturn(FLOAT);
	getToken_ExpectAndReturn(IDEN);
	getToken_ExpectAndReturn(STR);
	getToken_ExpectAndReturn(OPE);

  TEST_ASSERT_EQUAL(100,((IntegerToken *)(getToken()))-> value);
  TEST_ASSERT_EQUAL_FLOAT(12.34,((FloatToken *)(getToken()))-> value);
  TEST_ASSERT_EQUAL_STRING("JangSing",((IdentifierToken *)(getToken()))-> name);
  TEST_ASSERT_EQUAL_STRING("Wong",((StringToken *)(getToken()))-> name);
  TEST_ASSERT_EQUAL_STRING("{",((OperatorToken *)(getToken()))-> symbol);

  free(INT);
  free(FLOAT);
  free(IDEN);
  free(STR);
  free(OPE);

}

/**
 * A complete Simple List has been tested
 *
 *  {
 *    "NAME1":"JS",
 *    "NAME2":"STEVEN"
 *  }
 */
void test_Simple_JSON_List_for_well_form()
{
  JsonObject *jsonObj;
  Token *jsonTok;
  Iterator *iter;
  ErrorObject *err;

  TOKEN_DECLARE;

  getToken_ExpectAndReturn(openBrace0);    //"{"
  getToken_ExpectAndReturn(NAME1);         //"NAME1"
  getToken_ExpectAndReturn(colon0);        //":"
  getToken_ExpectAndReturn(JS);            //"JS"
  getToken_ExpectAndReturn(coma);          //","
  getToken_ExpectAndReturn(AGE);           //"AGE"
  getToken_ExpectAndReturn(colon1);        //":"
  getToken_ExpectAndReturn(int20);         //20
  getToken_ExpectAndReturn(closeBrace0);   //"}"
  getToken_ExpectAndReturn(NULL);

  jsonObj=createJsonObject();
  Try{
    jsonTok=jsonParse(jsonObj);
  }Catch(err){
    TEST_FAIL_MESSAGE(err->errorMsg);
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
  free(err);
}


/**
 * Test only '}' token has been passed into the list
 *
 *  }
 *
 */
void test_Simple_JSON_List_with_not_well_form_should_Throw_Error1()
{
  JsonObject *jsonObj;
  Token *jsonTok;
  ErrorObject *err;

  TOKEN_DECLARE;

  getToken_ExpectAndReturn(closeBrace0);   //"}"
  getToken_ExpectAndReturn(NULL);

  jsonObj=createJsonObject();
  Try{
    jsonTok=jsonParse(jsonObj);
  }Catch(err){
    TEST_ASSERT_EQUAL_STRING("ERROR:Expected '{' but get '}'.",err->errorMsg);
    TEST_ASSERT_EQUAL(ERR_EXPECT_OPERATOR,err->errorCode);
  }
  free(jsonObj);
  free(jsonTok);
  free(err);
}

/**
 * Test unexpected 'KEY' token has been passed into the list
 *
 *  { "JS"
 *
 */
void test_Simple_JSON_List_with_not_well_form_should_Throw_Error2()
{
  JsonObject *jsonObj;
  Token *jsonTok;
  ErrorObject *err;

  TOKEN_DECLARE;

  getToken_ExpectAndReturn(openBrace0);   //"{"
  getToken_ExpectAndReturn(JS);           //"JS"
  getToken_ExpectAndReturn(NULL);

  jsonObj=createJsonObject();
  Try{
    jsonTok=jsonParse(jsonObj);
  }Catch(err){
    TEST_ASSERT_EQUAL_STRING("ERROR:Expected an Identifier for 'Key'.",err->errorMsg);
    TEST_ASSERT_EQUAL(ERR_EXPECT_IDEN,err->errorCode);
  }
  free(jsonObj);
  free(jsonTok);
  free(err);
}

/**
 * Test unexpected token has been passed into the list after 'KEY' token
 *
 *  { "NAME1"}
 *
 */
void test_Simple_JSON_List_with_not_well_form_should_Throw_Error3()
{
  JsonObject *jsonObj;
  Token *jsonTok;
  ErrorObject *err;

  TOKEN_DECLARE;

  getToken_ExpectAndReturn(openBrace0);   //"{"
  getToken_ExpectAndReturn(NAME1);        //"NAME1"
  getToken_ExpectAndReturn(closeBrace0);  //"}"
  getToken_ExpectAndReturn(NULL);

  jsonObj=createJsonObject();
  Try{
    jsonTok=jsonParse(jsonObj);
  }Catch(err){
    TEST_ASSERT_EQUAL_STRING("ERROR:Expected ':' but get '}'.",err->errorMsg);
    TEST_ASSERT_EQUAL(ERR_EXPECT_OPERATOR,err->errorCode);
  }
  free(jsonObj);
  free(jsonTok);
  free(err);
}

/**
 * Test unexpected 'VALUE' token has been passed into the list
 *
 *  { "NAME1":}
 *
 */
void test_Simple_JSON_List_with_not_well_form_should_Throw_Error4()
{
  JsonObject *jsonObj;
  Token *jsonTok;
  ErrorObject *err;

  TOKEN_DECLARE;

  getToken_ExpectAndReturn(openBrace0);   //"{"
  getToken_ExpectAndReturn(NAME1);        //"NAME1"
  getToken_ExpectAndReturn(colon0);        //:
  getToken_ExpectAndReturn(closeBrace0);  //"}"
  getToken_ExpectAndReturn(NULL);

  jsonObj=createJsonObject();
  Try{
    jsonTok=jsonParse(jsonObj);
  }Catch(err){
    TEST_ASSERT_EQUAL_STRING("ERROR:Illegal Value.",err->errorMsg);
    TEST_ASSERT_EQUAL(ERR_ILLEGAL_VALUE,err->errorCode);
  }
  free(jsonObj);
  free(jsonTok);
  free(err);
}

/**
 * Test unexpected token has been passed into the list after 'VALUE' token
 *
 *  { "NAME1":"JS"^
 *
 */
void test_Simple_JSON_List_with_not_well_form_should_Throw_Error5()
{
  JsonObject *jsonObj;
  Token *jsonTok;
  ErrorObject *err;

  TOKEN_DECLARE;

  getToken_ExpectAndReturn(openBrace0);   //{
  getToken_ExpectAndReturn(NAME1);        //"NAME1"
  getToken_ExpectAndReturn(colon0);       //:
  getToken_ExpectAndReturn(JS);           //"JS"
  getToken_ExpectAndReturn(caret);        //^
  getToken_ExpectAndReturn(NULL);

  jsonObj=createJsonObject();
  Try{
    jsonTok=jsonParse(jsonObj);
  }Catch(err){
    TEST_ASSERT_EQUAL_STRING("ERROR:Expected Operator '}' or ',' but get '^'.",err->errorMsg);
    TEST_ASSERT_EQUAL(ERR_EXPECT_OPERATOR,err->errorCode);
  }
  free(jsonObj);
  free(jsonTok);
  free(err);
}

/**
 * Test unexpected 'KEY' token has been passed into the list
 *
 *  {
 *    "NAME1":"JS",
 *  }
 *
 */
void test_Simple_JSON_List_with_not_well_form_should_Throw_Error6()
{
  JsonObject *jsonObj;
  Token *jsonTok;
  ErrorObject *err;

  TOKEN_DECLARE;

  getToken_ExpectAndReturn(openBrace0);   //{
  getToken_ExpectAndReturn(NAME1);        //"NAME1"
  getToken_ExpectAndReturn(colon0);       //:
  getToken_ExpectAndReturn(JS);           //"JS"
  getToken_ExpectAndReturn(coma);         //,
  getToken_ExpectAndReturn(closeBrace0);  //}
  getToken_ExpectAndReturn(NULL);

  jsonObj=createJsonObject();
  Try{
    jsonTok=jsonParse(jsonObj);
  }Catch(err){
    TEST_ASSERT_EQUAL_STRING("ERROR:Expected an Identifier for 'Key'.",err->errorMsg);
    TEST_ASSERT_EQUAL(ERR_EXPECT_IDEN,err->errorCode);
  }
  free(jsonObj);
  free(jsonTok);
  free(err);
}

/**
 * Test unexpected token has been passed into the list after 'KEY' token
 *
 *  {
 *    "NAME1":"JS",
 *    "AGE"
 *  }
 *
 */
void test_Simple_JSON_List_with_not_well_form_should_Throw_Error7()
{
  JsonObject *jsonObj;
  Token *jsonTok;
  ErrorObject *err;

  TOKEN_DECLARE;

  getToken_ExpectAndReturn(openBrace0);   //{
  getToken_ExpectAndReturn(NAME1);        //"NAME1"
  getToken_ExpectAndReturn(colon0);       //:
  getToken_ExpectAndReturn(JS);           //"JS"
  getToken_ExpectAndReturn(coma);         //,
  getToken_ExpectAndReturn(AGE);          //"AGE"
  getToken_ExpectAndReturn(closeBrace0);  //}
  getToken_ExpectAndReturn(NULL);

  jsonObj=createJsonObject();
  Try{
    jsonTok=jsonParse(jsonObj);
  }Catch(err){
    TEST_ASSERT_EQUAL_STRING("ERROR:Expected ':' but get '}'.",err->errorMsg);
    TEST_ASSERT_EQUAL(ERR_EXPECT_OPERATOR,err->errorCode);
  }
  free(jsonObj);
  free(jsonTok);
  free(err);
}

/**
 * Test unexpected 'VALUE' token has been passed into the list
 *
 *  {
 *    "NAME1":"JS",
 *    "AGE"  :
 *  }
 *
 */
void test_Simple_JSON_List_with_not_well_form_should_Throw_Error8()
{
  JsonObject *jsonObj;
  Token *jsonTok;
  ErrorObject *err;

  TOKEN_DECLARE;

  getToken_ExpectAndReturn(openBrace0);   //{
  getToken_ExpectAndReturn(NAME1);        //"NAME1"
  getToken_ExpectAndReturn(colon0);       //:
  getToken_ExpectAndReturn(JS);           //"JS"
  getToken_ExpectAndReturn(coma);         //,
  getToken_ExpectAndReturn(AGE);          //"AGE"
  getToken_ExpectAndReturn(colon1);        //:
  getToken_ExpectAndReturn(closeBrace0);  //}
  getToken_ExpectAndReturn(NULL);

  jsonObj=createJsonObject();
  Try{
    jsonTok=jsonParse(jsonObj);
  }Catch(err){
    TEST_ASSERT_EQUAL_STRING("ERROR:Illegal Value.",err->errorMsg);
    TEST_ASSERT_EQUAL(ERR_ILLEGAL_VALUE,err->errorCode);
  }
  free(jsonObj);
  free(jsonTok);
  free(err);
}

/**
 * Test unexpected token has been passed into the list after 'VALUE' token
 *
 *  {
 *    "NAME1":"JS",
 *    "AGE"  :20^
 *
 */
void test_Simple_JSON_List_with_not_well_form_should_Throw_Error9()
{
  JsonObject *jsonObj;
  Token *jsonTok;
  ErrorObject *err;

  TOKEN_DECLARE;

  getToken_ExpectAndReturn(openBrace0);   //{
  getToken_ExpectAndReturn(NAME1);        //"NAME1"
  getToken_ExpectAndReturn(colon0);       //:
  getToken_ExpectAndReturn(JS);           //"JS"
  getToken_ExpectAndReturn(coma);         //,
  getToken_ExpectAndReturn(AGE);          //"AGE"
  getToken_ExpectAndReturn(colon1);       //:
  getToken_ExpectAndReturn(int20);        //20
  getToken_ExpectAndReturn(caret);        //^
  getToken_ExpectAndReturn(NULL);

  jsonObj=createJsonObject();
  Try{
    jsonTok=jsonParse(jsonObj);
  }Catch(err){
    TEST_ASSERT_EQUAL_STRING("ERROR:Expected Operator '}' or ',' but get '^'.",err->errorMsg);
    TEST_ASSERT_EQUAL(ERR_EXPECT_OPERATOR,err->errorCode);
  }
  free(jsonObj);
  free(jsonTok);
  free(err);
}

/**
 *{
 *  "NAME1":"JS",
 *  "AGE"  :{ "NAME2":"STEVEN",
 *            "NAME3":"YEN"}
 *}
 */
void test_JSON_List_with_Recursion_JSON_List()
{
  JsonObject *jsonObj;
  Token *jsonTok;
  Iterator *iter1,*iter2;
  ErrorObject *err;

  TOKEN_DECLARE;

  getToken_ExpectAndReturn(openBrace0);    //"{"
  getToken_ExpectAndReturn(NAME1);         //"NAME1"
  getToken_ExpectAndReturn(colon0);        //":"
  getToken_ExpectAndReturn(JS);            //"JS"
  getToken_ExpectAndReturn(coma);          //","
  getToken_ExpectAndReturn(AGE);           //"AGE"
  getToken_ExpectAndReturn(colon1);        //":"
  getToken_ExpectAndReturn(openBrace1);    //"{"
  getToken_ExpectAndReturn(NAME2);         //"NAME2"
  getToken_ExpectAndReturn(colon2);        //":"
  getToken_ExpectAndReturn(STEVEN);        //"STEVEN"
  getToken_ExpectAndReturn(coma);          //","
  getToken_ExpectAndReturn(NAME3);         //"NAME3"
  getToken_ExpectAndReturn(colon3);        //":"
  getToken_ExpectAndReturn(YEN);           //"YEN"
  getToken_ExpectAndReturn(closeBrace0);   //"}"
  getToken_ExpectAndReturn(closeBrace1);   //"}"
  getToken_ExpectAndReturn(NULL);

  jsonObj=createJsonObject();
  Try{
    jsonTok=jsonParse(jsonObj);
  }Catch(err){
    TEST_FAIL_MESSAGE(err->errorMsg);
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
  free(err);
}

/**
 *  {
 *    "NAME1":"JS",
 *    "NAME2":"STEVEN"
 *  }
 */
void test_Finding_Element_in_Simple_JSON_List()
{
  JsonObject *jsonObj;
  Token *jsonTok;
  ListElement *findKey;
  Token *findVal;
  ErrorObject *err;

  TOKEN_DECLARE;

  getToken_ExpectAndReturn(openBrace0);     //"{"
  getToken_ExpectAndReturn(NAME1);         //"NAME1"
  getToken_ExpectAndReturn(colon0);        //":"
  getToken_ExpectAndReturn(JS);            //"JS"
  getToken_ExpectAndReturn(coma);          //","
  getToken_ExpectAndReturn(AGE);           //"AGE"
  getToken_ExpectAndReturn(colon1);        //":"
  getToken_ExpectAndReturn(int20);         //20
  getToken_ExpectAndReturn(closeBrace0);    //"}"
  getToken_ExpectAndReturn(NULL);

  jsonObj=createJsonObject();

  Try{
    jsonTok=jsonParse(jsonObj);
  }Catch(err){
    TEST_FAIL_MESSAGE(err->errorMsg);
  }

  TEST_ASSERT_EQUAL(END,jsonObj->state);
  findKey=(ListElement *)(keyFind(((JsonToken *)jsonTok)->list, "AGE", strCompare));
  findVal=(Token *)(getElementValue(findKey));

  TEST_ASSERT_EQUAL(((IntegerToken *)(int20))->value,((IntegerToken *)(findVal))->value);

  free(jsonObj);
  free(jsonTok);
  free(err);
  free(findKey);
  free(findVal);
}

/**
 *{
 *  "NAME1":"JS",
 *  "AGE"  :{ "NAME2":"STEVEN",
 *            "NAME3":"YEN"}
 *}
 */
void test_Finding_Element_in_Recursion_JSON_List()
{
  JsonObject *jsonObj;
  Token *jsonTok;
  ListElement *findKey;
  Token *findVal;
  ErrorObject *err;

  TOKEN_DECLARE;

  getToken_ExpectAndReturn(openBrace0);    //"{"
  getToken_ExpectAndReturn(NAME1);         //"NAME1"
  getToken_ExpectAndReturn(colon0);        //":"
  getToken_ExpectAndReturn(JS);            //"JS"
  getToken_ExpectAndReturn(coma);          //","
  getToken_ExpectAndReturn(AGE);           //"AGE"
  getToken_ExpectAndReturn(colon1);        //":"
  getToken_ExpectAndReturn(openBrace1);    //"{"
  getToken_ExpectAndReturn(NAME2);         //"NAME2"
  getToken_ExpectAndReturn(colon2);        //":"
  getToken_ExpectAndReturn(STEVEN);        //"STEVEN"
  getToken_ExpectAndReturn(coma);          //","
  getToken_ExpectAndReturn(NAME3);         //"NAME3"
  getToken_ExpectAndReturn(colon3);        //":"
  getToken_ExpectAndReturn(YEN);           //"YEN"
  getToken_ExpectAndReturn(closeBrace0);   //"}"
  getToken_ExpectAndReturn(closeBrace1);   //"}"
  getToken_ExpectAndReturn(NULL);

  jsonObj=createJsonObject();

  Try{
    jsonTok=jsonParse(jsonObj);
  }Catch(err){
    TEST_FAIL_MESSAGE(err->errorMsg);
  }

  TEST_ASSERT_EQUAL(END,jsonObj->state);

  findKey=(ListElement *)(keyFind(((JsonToken *)jsonTok)->list, "AGE", strCompare));
  findKey=(ListElement *)(keyFind(((JsonToken *)(((OperatorToken *)(findKey->value))->token[1]))->list, "NAME3", strCompare));
  findVal=(Token *)(getElementValue(findKey));

  TEST_ASSERT_EQUAL_STRING(((StringToken *)(YEN))->name,((StringToken *)(findVal))->name);

  free(jsonObj);
  free(jsonTok);
  free(err);
  free(findKey);
  free(findVal);

}

