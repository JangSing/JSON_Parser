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
  LinkedList *list;
  Iterator *iter;

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

  TEST_ASSERT_NOT_NULL(list);
  list=jsonParse();

  TEST_ASSERT_EQUAL(END,list->state);

  iter=createIterator(list);
  TEST_ASSERT_EQUAL_STRING("{",((OperatorToken *)(iter->current->value))->symbol);
  iter=iteratorGetNext(iter);

  TEST_ASSERT_KEY_VALUE(NAME1,JS, iter->current);

  iter=iteratorGetNext(iter);

  TEST_ASSERT_KEY_VALUE(AGE,int20, iter->current);

  iter=iteratorGetNext(iter);
  TEST_ASSERT_EQUAL_STRING("}",((OperatorToken *)(iter->current->value))->symbol);

  free(list);
  free(iter);
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
  LinkedList *list;
  Iterator *iter1,*iter2;

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

  TEST_ASSERT_NOT_NULL(list);
  list=jsonParse();

  TEST_ASSERT_EQUAL(END,list->state);

  iter1=createIterator(list);
  TEST_ASSERT_EQUAL_STRING("{",((OperatorToken *)(iter1->current->value))->symbol);
  iter1=iteratorGetNext(iter1);
  TEST_ASSERT_KEY_VALUE(NAME1,JS, iter1->current);
  iter1=iteratorGetNext(iter1);
  TEST_ASSERT_KEY(AGE,iter1->current);
  iter2=createIterator(((LinkedList *)(((OperatorToken *)(iter1->current->value))->token[1])));
  TEST_ASSERT_EQUAL_STRING("{",((OperatorToken *)(iter2->current->value))->symbol);
  iter2=iteratorGetNext(iter2);
  TEST_ASSERT_KEY_VALUE(NAME2,STEVEN, iter2->current);
  iter2=iteratorGetNext(iter2);
  TEST_ASSERT_KEY_VALUE(NAME3,Yen, iter2->current);
  iter2=iteratorGetNext(iter2);
  TEST_ASSERT_EQUAL_STRING("}",((OperatorToken *)(iter2->current->value))->symbol);
  iter1=iteratorGetNext(iter1);
  TEST_ASSERT_EQUAL_STRING("}",((OperatorToken *)(iter1->current->value))->symbol);

  free(list);
  free(iter2);
  free(iter1);
}

/**
 *  {
 *    "NAME1":"JS",
 *    "NAME2":"STEVEN"
 *  }
 */
void test_Finding_Element_in_Simple_JSON_List()
{
  LinkedList *list;
  ListElement *findKey;
  Token *findVal;

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

  TEST_ASSERT_NOT_NULL(list);
  list=jsonParse();

  TEST_ASSERT_EQUAL(END,list->state);

  findKey=(ListElement *)(keyFind(list, "AGE", strCompare));
  findVal=(Token *)(getElementValue(findKey));

  TEST_ASSERT_EQUAL(((IntegerToken *)(int20))->value,((IntegerToken *)(findVal))->value);

  free(list);
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
  LinkedList *list;
  ListElement *findKey;
  Token *findVal;

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

  TEST_ASSERT_NOT_NULL(list);
  list=jsonParse();

  TEST_ASSERT_EQUAL(END,list->state);

  findKey=(ListElement *)(keyFind(list, "AGE", strCompare));
  findKey=(ListElement *)(keyFind((LinkedList *)(((OperatorToken *)(findKey->value))->token[1]), "NAME3", strCompare));
  findVal=(Token *)(getElementValue(findKey));

  TEST_ASSERT_EQUAL_PTR(((StringToken *)(Yen))->name,((StringToken *)(findVal))->name);

  free(list);
  free(findKey);
  free(findVal);
}

void test_Recursion_JSON_List_with_TryCatch()
{
  LinkedList *list;
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
  getToken_ExpectAndReturn(int20);            //"JS"
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

  TEST_ASSERT_NOT_NULL(list);

  Try{
    list=jsonParse();
  }Catch(err){
    switch(err->errorCode){
    case ERR_EXPECT_COLON     :UNITY_TEST_FAIL(__LINE__, err->errorMsg);break;
    case ERR_EXPECT_OPERATOR  :UNITY_TEST_FAIL(__LINE__, err->errorMsg);break;
    case ERR_EXPECT_IDEN      :UNITY_TEST_FAIL(__LINE__, err->errorMsg);break;
    case ERR_ILLEGAL_VALUE    :UNITY_TEST_FAIL(__LINE__, err->errorMsg);break;
    case ERR_ACCESS_DENIED    :UNITY_TEST_FAIL(__LINE__, err->errorMsg);break;
    }
  }

  TEST_ASSERT_EQUAL(END,list->state);

  free(list);
  free(err);
}


