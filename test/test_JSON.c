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
 *  {
 *    "NAME1":"JS",
 *    "NAME2":"STEVEN"
 *  }
 */
void test_Simple_JSON_List()
{
  JsonObject *jsonObj;
  Token *jsonTok;
  Iterator *iter;
  ErrorObject *err;

  Token *openBrace=createOperatorToken("{");
  Token *closeBrace=createOperatorToken("}");
  Token *coma=createOperatorToken(",");
  Token *colon0=createOperatorToken(":");
  Token *colon1=createOperatorToken(":");
  Token *NAME1=createIdentifierToken("NAME1");
  Token *AGE=createIdentifierToken("AGE");
  Token *JS=createStringToken("JS");
  Token *int20=createIntegerToken(20);

  getToken_ExpectAndReturn(openBrace);     //"{"
  getToken_ExpectAndReturn(NAME1);         //"NAME1"
  getToken_ExpectAndReturn(colon0);        //":"
  getToken_ExpectAndReturn(JS);            //"JS"
  getToken_ExpectAndReturn(coma);          //","
  getToken_ExpectAndReturn(AGE);           //"AGE"
  getToken_ExpectAndReturn(colon1);        //":"
  getToken_ExpectAndReturn(int20);         //20
  getToken_ExpectAndReturn(closeBrace);    //"}"
  getToken_ExpectAndReturn(NULL);

  jsonObj=createJsonObject();
  Try{
    jsonTok=jsonParse(jsonObj);
  }Catch(err){
    switch(err->errorCode){
    case ERR_EXPECT_COLON     :TEST_FAIL_MESSAGE(err->errorMsg);break;
    case ERR_EXPECT_OPERATOR  :TEST_FAIL_MESSAGE(err->errorMsg);break;
    case ERR_EXPECT_IDEN      :TEST_FAIL_MESSAGE(err->errorMsg);break;
    case ERR_ILLEGAL_VALUE    :TEST_FAIL_MESSAGE(err->errorMsg);break;
    case ERR_ACCESS_DENIED    :TEST_FAIL_MESSAGE(err->errorMsg);break;
    }
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

  Token *openBrace0=createOperatorToken("{");
  Token *openBrace1=createOperatorToken("{");
  Token *closeBrace0=createOperatorToken("}");
  Token *closeBrace1=createOperatorToken("}");
  Token *coma=createOperatorToken(",");
  Token *colon0=createOperatorToken(":");
  Token *colon1=createOperatorToken(":");
  Token *colon2=createOperatorToken(":");
  Token *colon3=createOperatorToken(":");
  Token *NAME1=createIdentifierToken("NAME1");
  Token *AGE=createIdentifierToken("AGE");
  Token *NAME2=createIdentifierToken("NAME2");
  Token *NAME3=createIdentifierToken("NAME3");
  Token *JS=createStringToken("JS");
  Token *STEVEN=createStringToken("STEVEN");
  Token *Yen=createStringToken("Yen");
  Token *int20=createIntegerToken(20);

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
  getToken_ExpectAndReturn(Yen);           //"Yen"
  getToken_ExpectAndReturn(closeBrace0);   //"}"
  getToken_ExpectAndReturn(closeBrace1);   //"}"
  getToken_ExpectAndReturn(NULL);

  jsonObj=createJsonObject();
  Try{
    jsonTok=jsonParse(jsonObj);
  }Catch(err){
    switch(err->errorCode){
    case ERR_EXPECT_COLON     :TEST_FAIL_MESSAGE(err->errorMsg);break;
    case ERR_EXPECT_OPERATOR  :TEST_FAIL_MESSAGE(err->errorMsg);break;
    case ERR_EXPECT_IDEN      :TEST_FAIL_MESSAGE(err->errorMsg);break;
    case ERR_ILLEGAL_VALUE    :TEST_FAIL_MESSAGE(err->errorMsg);break;
    case ERR_ACCESS_DENIED    :TEST_FAIL_MESSAGE(err->errorMsg);break;
    }
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
  TEST_ASSERT_KEY_VALUE(NAME3,Yen, iter2->current);
  iter2=iteratorGetNext(iter2);
  TEST_ASSERT_EQUAL_STRING("}",((OperatorToken *)(iter2->current->value))->symbol);
  iter1=iteratorGetNext(iter1);
  TEST_ASSERT_EQUAL_STRING("}",((OperatorToken *)(iter1->current->value))->symbol);

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

  Token *openBrace=createOperatorToken("{");
  Token *closeBrace=createOperatorToken("}");
  Token *coma=createOperatorToken(",");
  Token *colon0=createOperatorToken(":");
  Token *colon1=createOperatorToken(":");
  Token *NAME1=createIdentifierToken("NAME1");
  Token *AGE=createIdentifierToken("AGE");
  Token *JS=createStringToken("JS");
  Token *int20=createIntegerToken(20);

  getToken_ExpectAndReturn(openBrace);     //"{"
  getToken_ExpectAndReturn(NAME1);         //"NAME1"
  getToken_ExpectAndReturn(colon0);        //":"
  getToken_ExpectAndReturn(JS);            //"JS"
  getToken_ExpectAndReturn(coma);          //","
  getToken_ExpectAndReturn(AGE);           //"AGE"
  getToken_ExpectAndReturn(colon1);        //":"
  getToken_ExpectAndReturn(int20);         //20
  getToken_ExpectAndReturn(closeBrace);    //"}"
  getToken_ExpectAndReturn(NULL);

  jsonObj=createJsonObject();

  Try{
    jsonTok=jsonParse(jsonObj);
  }Catch(err){
    switch(err->errorCode){
    case ERR_EXPECT_COLON     :TEST_FAIL_MESSAGE(err->errorMsg);break;
    case ERR_EXPECT_OPERATOR  :TEST_FAIL_MESSAGE(err->errorMsg);break;
    case ERR_EXPECT_IDEN      :TEST_FAIL_MESSAGE(err->errorMsg);break;
    case ERR_ILLEGAL_VALUE    :TEST_FAIL_MESSAGE(err->errorMsg);break;
    case ERR_ACCESS_DENIED    :TEST_FAIL_MESSAGE(err->errorMsg);break;
    }
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

  Token *openBrace0=createOperatorToken("{");
  Token *openBrace1=createOperatorToken("{");
  Token *closeBrace0=createOperatorToken("}");
  Token *closeBrace1=createOperatorToken("}");
  Token *coma=createOperatorToken(",");
  Token *colon0=createOperatorToken(":");
  Token *colon1=createOperatorToken(":");
  Token *colon2=createOperatorToken(":");
  Token *colon3=createOperatorToken(":");
  Token *NAME1=createIdentifierToken("NAME1");
  Token *AGE=createIdentifierToken("AGE");
  Token *NAME2=createIdentifierToken("NAME2");
  Token *NAME3=createIdentifierToken("NAME3");
  Token *JS=createStringToken("JS");
  Token *STEVEN=createStringToken("STEVEN");
  Token *Yen=createStringToken("Yen");
  Token *int20=createIntegerToken(20);

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
  getToken_ExpectAndReturn(Yen);           //"Yen"
  getToken_ExpectAndReturn(closeBrace0);   //"}"
  getToken_ExpectAndReturn(closeBrace1);   //"}"
  getToken_ExpectAndReturn(NULL);

  jsonObj=createJsonObject();

  Try{
    jsonTok=jsonParse(jsonObj);
  }Catch(err){
    switch(err->errorCode){
    case ERR_EXPECT_COLON     :TEST_FAIL_MESSAGE(err->errorMsg);break;
    case ERR_EXPECT_OPERATOR  :TEST_FAIL_MESSAGE(err->errorMsg);break;
    case ERR_EXPECT_IDEN      :TEST_FAIL_MESSAGE(err->errorMsg);break;
    case ERR_ILLEGAL_VALUE    :TEST_FAIL_MESSAGE(err->errorMsg);break;
    case ERR_ACCESS_DENIED    :TEST_FAIL_MESSAGE(err->errorMsg);break;
    }
  }

  TEST_ASSERT_EQUAL(END,jsonObj->state);

  findKey=(ListElement *)(keyFind(((JsonToken *)jsonTok)->list, "AGE", strCompare));
  findKey=(ListElement *)(keyFind(((JsonToken *)(((OperatorToken *)(findKey->value))->token[1]))->list, "NAME3", strCompare));
  findVal=(Token *)(getElementValue(findKey));

  TEST_ASSERT_EQUAL_STRING(((StringToken *)(Yen))->name,((StringToken *)(findVal))->name);

  free(jsonObj);
  free(jsonTok);
  free(err);
  free(findKey);
  free(findVal);

}

void test_Recursion_JSON_List_with_TryCatch()
{
  JsonObject *jsonObj;
  ErrorObject *err;
  Token *jsonTok;

  Token *openBrace0=createOperatorToken("{");
  Token *openBrace1=createOperatorToken("{");
  Token *closeBrace0=createOperatorToken("}");
  Token *closeBrace1=createOperatorToken("}");
  Token *coma=createOperatorToken(",");
  Token *colon0=createOperatorToken(":");
  Token *colon1=createOperatorToken(":");
  Token *colon2=createOperatorToken(":");
  Token *colon3=createOperatorToken(":");
  Token *NAME1=createIdentifierToken("NAME1");
  Token *AGE=createIdentifierToken("AGE");
  Token *NAME2=createIdentifierToken("NAME2");
  Token *NAME3=createIdentifierToken("NAME3");
  Token *JS=createStringToken("JS");
  Token *STEVEN=createStringToken("STEVEN");
  Token *Yen=createStringToken("Yen");
  Token *int20=createIntegerToken(20);

  getToken_ExpectAndReturn(openBrace0);    //"{"
  getToken_ExpectAndReturn(NAME1);         //"NAME1"
  getToken_ExpectAndReturn(colon0);        //":"
  getToken_ExpectAndReturn(int20);         //"JS"
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
  getToken_ExpectAndReturn(Yen);           //"Yen"
  getToken_ExpectAndReturn(closeBrace0);   //"}"
  getToken_ExpectAndReturn(closeBrace1);   //"}"
  getToken_ExpectAndReturn(NULL);

  jsonObj=createJsonObject();

  Try{
    jsonTok=jsonParse(jsonObj);
  }Catch(err){
    switch(err->errorCode){
    case ERR_EXPECT_COLON     :TEST_FAIL_MESSAGE(err->errorMsg);break;
    case ERR_EXPECT_OPERATOR  :TEST_FAIL_MESSAGE(err->errorMsg);break;
    case ERR_EXPECT_IDEN      :TEST_FAIL_MESSAGE(err->errorMsg);break;
    case ERR_ILLEGAL_VALUE    :TEST_FAIL_MESSAGE(err->errorMsg);break;
    case ERR_ACCESS_DENIED    :TEST_FAIL_MESSAGE(err->errorMsg);break;
    }
  }

  TEST_ASSERT_EQUAL(END,jsonObj->state);

  free(jsonObj);
  free(jsonTok);
  free(err);
}

void test_jsonParse()
{
  JsonObject *jsonObj;
  ErrorObject *err;
  Token *jsonTok;

  Token *openBrace0=createOperatorToken("{");
  Token *openBrace1=createOperatorToken("{");
  Token *closeBrace0=createOperatorToken("}");
  Token *closeBrace1=createOperatorToken("}");
  Token *coma=createOperatorToken(",");
  Token *colon0=createOperatorToken(":");
  Token *colon1=createOperatorToken(":");
  Token *colon2=createOperatorToken(":");
  Token *colon3=createOperatorToken(":");
  Token *NAME1=createIdentifierToken("NAME1");
  Token *AGE=createIdentifierToken("AGE");
  Token *NAME2=createIdentifierToken("NAME2");
  Token *NAME3=createIdentifierToken("NAME3");
  Token *JS=createStringToken("JS");
  Token *STEVEN=createStringToken("STEVEN");
  Token *Yen=createStringToken("Yen");
  Token *int20=createIntegerToken(20);

  getToken_ExpectAndReturn(openBrace0);    //"{"
  getToken_ExpectAndReturn(NAME1);         //"NAME1"
  getToken_ExpectAndReturn(colon0);        //":"
  getToken_ExpectAndReturn(int20);         //"JS"
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
  getToken_ExpectAndReturn(Yen);           //"Yen"
  getToken_ExpectAndReturn(closeBrace0);   //"}"
  getToken_ExpectAndReturn(closeBrace1);   //"}"
  getToken_ExpectAndReturn(NULL);


  jsonObj=createJsonObject();

  Try{
    jsonTok=jsonParse(jsonObj);
  }Catch(err){
    switch(err->errorCode){
    case ERR_EXPECT_COLON     :TEST_FAIL_MESSAGE(err->errorMsg);break;
    case ERR_EXPECT_OPERATOR  :TEST_FAIL_MESSAGE(err->errorMsg);break;
    case ERR_EXPECT_IDEN      :TEST_FAIL_MESSAGE(err->errorMsg);break;
    case ERR_ILLEGAL_VALUE    :TEST_FAIL_MESSAGE(err->errorMsg);break;
    case ERR_ACCESS_DENIED    :TEST_FAIL_MESSAGE(err->errorMsg);break;
    }
  }
  TEST_ASSERT_EQUAL(END,jsonObj->state);
}


