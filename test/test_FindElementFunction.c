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

#include <malloc.h>
#include <stdio.h>
#include <assert.h>

void setUp()
{
}

void tearDown()
{
}

/************************************************************************************************************
 * This test file is to test for the Finding function for both LinkedList and JsonList.                     *
 * Whenever if NULL is passing into listFind or keyFind, the function will return NULL.                     *
 *                                                                                                          *
 *  For the function listFind,                                                                              *
 *   -if the element wanted to find is in the LinkedList the function will return the found Element.        *
 *   -else the function will return NULL.                                                                   *
 *                                                                                                          *
 *  For the function keyFind,                                                                               *
 *   -if the Key wanted to find is in the JsonList the function will return the tree of the Key.            *
 *   -else the function will ThrowError.                                                                    *
 *                                                                                                          *
 ************************************************************************************************************/

void test_listFind_Function_given_list_is_NULL_should_return_NULL()
{
  ListElement *findEle;
  char *strTest="forTesting";

  findEle=listFind(NULL,strTest,strCompare);

  TEST_ASSERT_NULL(findEle);
}

void test_keyFind_Function_given_list_is_NULL_should_return_NULL()
{
  ListElement *findEle;
  char *strTest="forTesting";

  findEle=keyFind(NULL,strTest,strCompare);

  TEST_ASSERT_NULL(findEle);
}

void test_listFind_Function_given_Value_is_NULL_should_return_NULL()
{
  ListElement *findEle;
  LinkedList *list;

  list=createLinkedList();

  findEle=listFind(list,NULL,strCompare);

  TEST_ASSERT_NULL(findEle);
}

void test_keyFind_Function_given_Value_is_NULL_should_return_NULL()
{
  ListElement *findEle;
  LinkedList *list;

  list=createLinkedList();

  findEle=keyFind(list,NULL,strCompare);

  TEST_ASSERT_NULL(findEle);
}

void test_Find_Integer_Element_if_Element_not_in_the_List_Should_return_NULL()
{
	int myValue4 =8;
  int value[]={1,3,4,6,7};

  LinkedList *ptr;
  ListElement *elemFind;

  ptr=createLinkedList();

  addLast(createListElement(&value[0]),ptr);
  addLast(createListElement(&value[1]),ptr);
  addLast(createListElement(&value[2]),ptr);
  addLast(createListElement(&value[3]),ptr);
  addLast(createListElement(&value[4]),ptr);

  elemFind=NULL;
  elemFind=listFind(ptr,&myValue4,intCompare);

  TEST_ASSERT_NOT_NULL(ptr);
  TEST_ASSERT_NULL(elemFind);
}

void test_findElement_integer()
{
	int myValue4 =4;
  int value[]={1,3,4,6,7};

  LinkedList *ptr;
  ListElement *elemFind;

  ptr=createLinkedList();

  addLast(createListElement(&value[0]),ptr);
  addLast(createListElement(&value[1]),ptr);
  addLast(createListElement(&value[2]),ptr);
  addLast(createListElement(&value[3]),ptr);
  addLast(createListElement(&value[4]),ptr);

  elemFind=NULL;
  elemFind=listFind(ptr,&myValue4,intCompare);

  TEST_ASSERT_NOT_NULL(ptr);
  TEST_ASSERT_NOT_NULL(elemFind);
  TEST_ASSERT_NOT_NULL(elemFind->value);
  TEST_ASSERT_EQUAL(4,*(int *)(elemFind->value));
}

void test_Find_String_Element_if_Element_not_in_the_List_Should_return_NULL()
{
	char *myStr4="five";
  char *str[]={"one","three","four","six","seven"};

  LinkedList *ptr;
  ListElement *elemFind;

  ptr=createLinkedList();

  addLast(createListElement(str[0]),ptr);
  addLast(createListElement(str[1]),ptr);
  addLast(createListElement(str[2]),ptr);
  addLast(createListElement(str[3]),ptr);
  addLast(createListElement(str[4]),ptr);

  elemFind=NULL;
  elemFind=listFind(ptr,myStr4,strCompare);

  TEST_ASSERT_NOT_NULL(ptr);
  TEST_ASSERT_NULL(elemFind);
}

void test_findElement_string()
{
	char *myStr4="four";
  char *str[]={"one","three","four","six","seven"};

  LinkedList *ptr;
  ListElement *elemFind;

  ptr=createLinkedList();

  addLast(createListElement(str[0]),ptr);
  addLast(createListElement(str[1]),ptr);
  addLast(createListElement(str[2]),ptr);
  addLast(createListElement(str[3]),ptr);
  addLast(createListElement(str[4]),ptr);

  elemFind=NULL;
  elemFind=listFind(ptr,myStr4,strCompare);

  TEST_ASSERT_NOT_NULL(ptr);
  TEST_ASSERT_NOT_NULL(elemFind);
  TEST_ASSERT_NOT_NULL(elemFind->value);
  TEST_ASSERT_EQUAL("four",(char *)(elemFind->value));
}

/**
 *  {
 *    "NAME1":"JS",
 *    "NAME2":"STEVEN"
 *  }
 */
void test_Finding_Element_if_Key_not_Found_in_the_Simple_JSON_List()
{
  printf("JSON list Finding Element test No.1\n");
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
  getToken_ExpectAndReturn(coma0);         //","
  getToken_ExpectAndReturn(NAME2);         //"NAME2"
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
  Try{
    findKey=keyFind(((JsonToken *)jsonTok)->list, "AGE", strCompare);
    TEST_FAIL_MESSAGE("Expecting ERR_KEY_NOT_FOUND to be thrown, but none thrown.");
  }Catch(err){
    TEST_ASSERT_EQUAL_STRING("ERROR[14]:Key not Found.Finding 'Key'=>'AGE'.",err->errorMsg);
    TEST_ASSERT_EQUAL(ERR_KEY_NOT_FOUND,err->errorCode);
    free(err);
  }

  free(jsonObj);
  free(jsonTok);
  free(findKey);
  free(findVal);

  TOKEN_FREE;
  printf("\n\n");
}


/**
 *  {
 *    "NAME1":"JS",
 *    "NAME2":"STEVEN"
 *  }
 */
void test_Finding_Element_in_Simple_JSON_List()
{
  printf("JSON list Finding Element test No.2\n");
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
  getToken_ExpectAndReturn(coma0);          //","
  getToken_ExpectAndReturn(AGE);           //"AGE"
  getToken_ExpectAndReturn(colon1);        //":"
  getToken_ExpectAndReturn(int20);         //20
  getToken_ExpectAndReturn(closeBrace0);   //"}"
  getToken_ExpectAndReturn(dollarSign);

  jsonObj=createJsonObject();

  Try{
    jsonTok=jsonParse(jsonObj);
    TEST_ASSERT_EQUAL(END,jsonObj->state);
    findKey=keyFind(((JsonToken *)jsonTok)->list, "AGE", strCompare);
    findVal=(Token *)(getElementValue(findKey));
  }Catch(err){
    TEST_FAIL_JSON("unexpected error occurred =>'%s'",err->errorMsg);
    free(err);
  }
  
  TEST_ASSERT_EQUAL(((IntegerToken *)(int20))->value,((IntegerToken *)(findVal))->value);

  free(jsonObj);
  free(jsonTok);
  free(err);
  free(findKey);
  free(findVal);

  TOKEN_FREE;
  printf("\n\n");
}

/**
 *{
 *  "NAME1":"JS",
 *  "AGE"  :{ "NAME2":"STEVEN",
 *            "NAME3":"YEN"}
 *}
 */
void test_Finding_Element_if_Key_not_Found_in_the_Recursion_JSON_List()
{
  printf("JSON list Finding Element test No.3\n");
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
  getToken_ExpectAndReturn(coma0);          //","
  getToken_ExpectAndReturn(AGE);           //"AGE"
  getToken_ExpectAndReturn(colon1);        //":"
  getToken_ExpectAndReturn(openBrace1);    //"{"
  getToken_ExpectAndReturn(NAME2);         //"NAME2"
  getToken_ExpectAndReturn(colon2);        //":"
  getToken_ExpectAndReturn(STEVEN);        //"STEVEN"
  getToken_ExpectAndReturn(coma1);          //","
  getToken_ExpectAndReturn(NAME4);         //"NAME4"
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

  Try{
    findKey=(ListElement *)(keyFind(((JsonToken *)jsonTok)->list, "AGE", strCompare));
    findKey=(ListElement *)(keyFind(((JsonToken *)(((OperatorToken *)(findKey->value))->token[1]))->list, "NAME3", strCompare));
    TEST_FAIL_MESSAGE("Expecting ERR_KEY_NOT_FOUND but none thrown.");
  }Catch(err){
    TEST_ASSERT_EQUAL_STRING("ERROR[14]:Key not Found.Finding 'Key'=>'NAME3'.",err->errorMsg);
    TEST_ASSERT_EQUAL(ERR_KEY_NOT_FOUND,err->errorCode);
    free(err);
  }


  free(jsonObj);
  free(jsonTok);
  free(err);
  free(findKey);
  free(findVal);

  TOKEN_FREE;
  printf("\n\n");
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
  printf("JSON list Finding Element test No.4\n");
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
    TEST_ASSERT_EQUAL(END,jsonObj->state);
    findKey=(ListElement *)(keyFind(((JsonToken *)jsonTok)->list, "AGE", strCompare));
    findKey=(ListElement *)(keyFind(((JsonToken *)(((OperatorToken *)(findKey->value))->token[1]))->list, "NAME3", strCompare));
    findVal=(Token *)(getElementValue(findKey));
  }Catch(err){
    TEST_FAIL_JSON("unexpected error occurred =>'%s'",err->errorMsg);
    free(err);
  }
  
  TEST_ASSERT_EQUAL_STRING(((StringToken *)(YEN))->name,((StringToken *)(findVal))->name);

  free(jsonObj);
  free(jsonTok);
  free(err);
  free(findKey);
  free(findVal);

  TOKEN_FREE;
  printf("\n\n");
}










