#ifndef CustomAssertion_H
#define CustomAssertion_H

#include "unity.h"
#include "Token.h"
#include "JSON.h"
#include "LinkedList.h"
#include "IteratorFunction.h"

#define TEST_ASSERT_KEY_VALUE(key, value, actual)      \
                    customTestAssertKeyValue(key, value, actual, __LINE__)

#define TEST_ASSERT_KEY(key, actual)      \
                    customTestAssertKey(key, actual, __LINE__)

#define TEST_ASSERT_VALUE(value, actual)      \
                    customTestAssertValue(value, actual, __LINE__)

#define CUSTOM_TEST_FAIL(msg,...)              {                                                                              \
                                               char buffer[256];                                                              \
                                               sprintf(buffer,msg, ## __VA_ARGS__);                                           \
                                               UNITY_TEST_FAIL(lineNo, buffer);                                               \
                                               }

#define TEST_FAIL_JSON(msg,...)                {                                                                              \
                                               char buffer[256];                                                              \
                                               sprintf(buffer,msg, ## __VA_ARGS__);                                           \
                                               UNITY_TEST_FAIL(__LINE__, buffer);                                             \
                                               }


void customTestAssertKeyValue(void *key, void *value, ListElement *actual, int lineNo);

void customTestAssertKey(void *key, ListElement *actual, int lineNo);

void customTestAssertValue(void *value, ListElement *actual, int lineNo);


#endif // CustomAssertion_H
#include "ErrorObject.h"
#include "CException.h"
#include "compareFunction.h"
#include "createTokenType.h"
#include "FindElementFunction.h"
#include "IteratorFunction.h"
#include "JSON.h"
#include "LinkedList.h"
#include "Token.h"
#include "CustomAssertion.h"

#include <stdio.h>

void customTestAssertKeyValue(void *key, void *value, ListElement *actual, int lineNo){

  Iterator *iter;

  if (key==NULL || value==NULL || actual==NULL){
    CUSTOM_TEST_FAIL("ERROR:The key or value or actual cannot be NULL.");
  }
  else{
    OperatorToken *opTokActual=((OperatorToken *)(actual->value));

    char *idenKey=((IdentifierToken *)(key))->name;
    char *strValue=((StringToken *)(value))->name;
    int  intValue=((IntegerToken *)(value))->value;
    double  floatValue=((FloatToken *)(value))->value;

    char *idenLeftToken=((IdentifierToken *)(opTokActual->token[0]))->name;
    char *charRightToken=((StringToken *)(opTokActual->token[1]))->name;
    int  intRightToken=((IntegerToken *)(opTokActual->token[1]))->value;
    double  floatRightToken=((FloatToken *)(opTokActual->token[1]))->value;

    iter=createIterator((LinkedList *)(opTokActual->token[1]));


    UNITY_TEST_ASSERT_EQUAL_STRING(":", opTokActual->symbol, lineNo, NULL);


    //test for KEY token
    if(opTokActual->token[0]->type==TOKEN_IDENTIFIER_TYPE){
      if(((Token *)(key))->type==TOKEN_IDENTIFIER_TYPE){
        UNITY_TEST_ASSERT_EQUAL_STRING(idenKey,idenLeftToken,lineNo, NULL);
      }
      else{
        CUSTOM_TEST_FAIL("ERROR:Actual value for KEY was %s",idenLeftToken);
      }
    }
    else{
      CUSTOM_TEST_FAIL("ERROR:Unexpected KEY Token type.Expected an Identifier Token.");
    }

    //test for VALUE token
    if(opTokActual->token[1]->type==TOKEN_STRING_TYPE){
      if(((Token *)(value))->type==TOKEN_STRING_TYPE){
        UNITY_TEST_ASSERT_EQUAL_STRING(strValue,charRightToken,lineNo, NULL);
      }
      else{
        CUSTOM_TEST_FAIL("ERROR:Actual value for VALUE was %s",charRightToken);
      }
    }
    else if(opTokActual->token[1]->type==TOKEN_INTEGER_TYPE){
      if(((Token *)(value))->type==TOKEN_INTEGER_TYPE){
        UNITY_TEST_ASSERT_EQUAL_INT(intValue,intRightToken, lineNo, NULL);
      }
      else{
        CUSTOM_TEST_FAIL("ERROR:Actual value for VALUE was %d",intRightToken);
      }
    }
    else if(opTokActual->token[1]->type==TOKEN_FLOAT_TYPE){
      if(((Token *)(value))->type==TOKEN_FLOAT_TYPE){
        UNITY_TEST_ASSERT_EQUAL_FLOAT(floatValue,floatRightToken, lineNo, NULL);
      }
      else{
        CUSTOM_TEST_FAIL("ERROR:Actual value for VALUE was %d",floatRightToken);
      }
    }
    else{
      CUSTOM_TEST_FAIL("ERROR:Unexpected VALUE Token type.Expected String,Integer or a Float Token.");
    }
  }

}

void customTestAssertKey(void *key, ListElement *actual, int lineNo){

  Iterator *iter;

  if (key==NULL || actual==NULL){
    CUSTOM_TEST_FAIL("ERROR:The key or actual cannot be NULL.");
  }
  else{
    OperatorToken *opTokActual=((OperatorToken *)(actual->value));

    char *idenKey=((IdentifierToken *)(key))->name;
    char *idenLeftToken=((IdentifierToken *)(opTokActual->token[0]))->name;

    UNITY_TEST_ASSERT_EQUAL_STRING(":", opTokActual->symbol, lineNo, NULL);

    //test for KEY token
    if(opTokActual->token[0]->type==TOKEN_IDENTIFIER_TYPE){
      if(((Token *)(key))->type==TOKEN_IDENTIFIER_TYPE){
        UNITY_TEST_ASSERT_EQUAL_STRING(idenKey,idenLeftToken,lineNo, NULL);
      }
      else{
        CUSTOM_TEST_FAIL("ERROR:Actual value for KEY was %s",idenLeftToken);
      }
    }
    else{
      CUSTOM_TEST_FAIL("ERROR:Unexpected KEY Token type.Expected an Identifier Token.");
    }
  }

}

void customTestAssertValue(void *value, ListElement *actual, int lineNo){

  Iterator *iter;

  if (value==NULL || actual==NULL){
    CUSTOM_TEST_FAIL("ERROR:The value or actual cannot be NULL.");
  }
  else{
    OperatorToken *opTokActual=((OperatorToken *)(actual->value));

    char *strValue=((StringToken *)(value))->name;
    int  intValue=((IntegerToken *)(value))->value;
    double  floatValue=((FloatToken *)(value))->value;

    char *charRightToken=((StringToken *)(opTokActual->token[1]))->name;
    int  intRightToken=((IntegerToken *)(opTokActual->token[1]))->value;
    double  floatRightToken=((FloatToken *)(opTokActual->token[1]))->value;

    iter=createIterator((LinkedList *)(opTokActual->token[1]));

    UNITY_TEST_ASSERT_EQUAL_STRING(":", opTokActual->symbol, lineNo, NULL);

    //test for VALUE token
    if(opTokActual->token[1]->type==TOKEN_STRING_TYPE){
      if(((Token *)(value))->type==TOKEN_STRING_TYPE){
        UNITY_TEST_ASSERT_EQUAL_STRING(strValue,charRightToken,lineNo, NULL);
      }
      else{
        CUSTOM_TEST_FAIL("ERROR:Actual value for VALUE was %s",charRightToken);
      }
    }
    else if(opTokActual->token[1]->type==TOKEN_INTEGER_TYPE){
      if(((Token *)(value))->type==TOKEN_INTEGER_TYPE){
        UNITY_TEST_ASSERT_EQUAL_INT(intValue,intRightToken, lineNo, NULL);
      }
      else{
        CUSTOM_TEST_FAIL("ERROR:Actual value for VALUE was %d",intRightToken);
      }
    }
    else if(opTokActual->token[1]->type==TOKEN_FLOAT_TYPE){
      if(((Token *)(value))->type==TOKEN_FLOAT_TYPE){
        UNITY_TEST_ASSERT_EQUAL_FLOAT(floatValue,floatRightToken, lineNo, NULL);
      }
      else{
        CUSTOM_TEST_FAIL("ERROR:Actual value for VALUE was %d",floatRightToken);
      }
    }
    else{
      CUSTOM_TEST_FAIL("ERROR:Unexpected VALUE Token type.Expected String,Integer or a Float Token.");
    }
  }

}
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

#include <stdarg.h>
#include <malloc.h>
#include <stdio.h>
#include <assert.h>
#include <ctype.h>

void setUp()
{
}

void tearDown()
{
}

/****************************************************************************************************
 * This test is to test whether the TEST_ASSERT_KEY_VALUE are able to function.                     *
 * For Example,                                                                                     *
 *                                                                                                  *
 *                         ____                                                                     *
 *                        | : |                                                                     *
 *                        ----                                                                      *
 *                      /     \                                                                     *
 *                  'NAME1'   'JS'                                                                  *
 *                                                                                                  *
 * The TEST_ASSERT_KEY_VALUE will pass in the whole tree shown above to test.                       *
 * Test whether the expected 'Key' and 'Value' are the same with the 'Key' and 'Value' in the tree. *
 *                                                                                                  *
 ****************************************************************************************************/
void test_Custom_Test_Assert_Key_Value()
{
  LinkedList *list;
  Iterator *iter;
  JsonObject *jsonObj;
  Token *jsonTok;

  TOKEN_DECLARE;

  getToken_ExpectAndReturn(openBrace0);     //"{"
  getToken_ExpectAndReturn(NAME1);          //"NAME1"
  getToken_ExpectAndReturn(colon0);         //":"
  getToken_ExpectAndReturn(JS);             //"JS"
  getToken_ExpectAndReturn(closeBrace0);    //"}"
  getToken_ExpectAndReturn(dollarSign);

  jsonObj=createJsonObject();
  jsonTok=jsonParse(jsonObj);

  TEST_ASSERT_EQUAL(END,jsonObj->state);

  iter=createIterator(((JsonToken *)jsonTok)->list);
  TEST_ASSERT_EQUAL_STRING("{",((OperatorToken *)(iter->current->value))->symbol);
  iter=iteratorGetNext(iter);
  TEST_ASSERT_NOT_NULL(NAME1);
  TEST_ASSERT_NOT_NULL(JS);
  TEST_ASSERT_NOT_NULL(iter->current);
  TEST_ASSERT_KEY_VALUE(NAME1,JS, iter->current);
  iter=iteratorGetNext(iter);
  TEST_ASSERT_EQUAL_STRING("}",((OperatorToken *)(iter->current->value))->symbol);

  TOKEN_FREE;
}


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
 * This test file is to test for the Finding function for both JsonList.                                    *
 * Whenever if NULL is passing into keyFind, the function will return NULL.                                 *
 *                                                                                                          *
 *  For the function keyFind,                                                                               *
 *   -if the Key wanted to find is in the JsonList the function will return the tree of the Key.            *
 *   -else the function will ThrowError.                                                                    *
 *                                                                                                          *
 *  For the function getElementValue,                                                                       *
 *   -The function will return the 'Value' of the tree that passed into the function.                       *
 *   -if the 'Value' of the tree is Operator type, the function will return NULL.                           *
 *   -also, if NULL tree passing into the function, the function will return NULL.                          *
 *                                                                                                          *
 ************************************************************************************************************/

void test_keyFind_Function_given_list_is_NULL_should_return_NULL()
{
  ListElement *findEle;
  char *strTest="forTesting";

  findEle=keyFind(NULL,strTest,strCompare);

  TEST_ASSERT_NULL(findEle);
}

void test_keyFind_Function_given_Key_is_NULL_should_return_NULL()
{
  ListElement *findEle;
  LinkedList *list;

  list=createLinkedList();
  findEle=keyFind(list,NULL,strCompare);

  TEST_ASSERT_NULL(findEle);
}

void test_keyFind_Function_given_Compare_Function_is_NULL_should_return_NULL()
{
  ListElement *findEle;
  LinkedList *list;
  char *strTest="forTesting";

  list=createLinkedList();
  findEle=keyFind(list,strTest,NULL);

  TEST_ASSERT_NULL(findEle);
}

/************************************************************************************************************
 * The JsonList for the findElement Function to test are as shown below,                                    *
 *                                                                                                          *
 *  {                                                                                                       *
 *    "NAME1":"JS",                                                                                         *
 *    "NAME2":20,                                                                                           *
 *    "NAME3":"STEVEN",                                                                                     *
 *  }                                                                                                       *
 *                                                                                                          *
 * -Test to find the 'Key'="AGE".                                                                           *
 *                                                                                                          *
 ************************************************************************************************************/
void test_Finding_Element_if_Key_not_Found_in_the_Simple_JSON_List_Should_Throw_Error()
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
  getToken_ExpectAndReturn(coma1);         //","
  getToken_ExpectAndReturn(NAME3);         //"NAME3"
  getToken_ExpectAndReturn(colon2);        //":"
  getToken_ExpectAndReturn(STEVEN);        //"STEVEN"
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

/************************************************************************************************************
 * The JsonList for the findElement Function to test are as shown below,                                    *
 *                                                                                                          *
 *  {                                                                                                       *
 *    "NAME1":"JS",                                                                                         *
 *    "AGE"  :20,                                                                                           *
 *    "NAME3":"STEVEN",                                                                                     *
 *  }                                                                                                       *
 *                                                                                                          *
 * -Test to find the 'Key'="AGE".                                                                           *
 * -Test to get the 'Value' for the 'Key' found.                                                            *
 *                                                                                                          *
 ************************************************************************************************************/
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
  getToken_ExpectAndReturn(coma0);         //","
  getToken_ExpectAndReturn(AGE);           //"AGE"
  getToken_ExpectAndReturn(colon1);        //":"
  getToken_ExpectAndReturn(int20);         //20
  getToken_ExpectAndReturn(coma1);         //","
  getToken_ExpectAndReturn(NAME3);         //"NAME3"
  getToken_ExpectAndReturn(colon2);        //":"
  getToken_ExpectAndReturn(STEVEN);        //"STEVEN"
  getToken_ExpectAndReturn(closeBrace0);   //"}"
  getToken_ExpectAndReturn(dollarSign);

  jsonObj=createJsonObject();

  Try{
    jsonTok=jsonParse(jsonObj);
    TEST_ASSERT_EQUAL(END,jsonObj->state);
    findKey=keyFind(((JsonToken *)jsonTok)->list, "AGE", strCompare);
    findVal=(Token *)(getElementValue(findKey));
    TEST_ASSERT_NOT_NULL(findVal);
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

/************************************************************************************************************
 * The JsonList for the findElement Function to test are as shown below,                                    *
 *                                                                                                          *
 *  {                                                                                                       *
 *    "NAME1":"JS",                                                                                         *
 *    "AGE"  :{ "NAME2":"STEVEN",                                                                           *
 *              "NAME4":"YEN"}                                                                              *
 *  }                                                                                                       *
 *                                                                                                          *
 * -Test to find the 'Key'="AGE" in recur=0.                                                                *
 * -Test to find the 'Key'="NAME3" in recur=1.                                                              *
 *                                                                                                          *                                                                                                         *
 ************************************************************************************************************/
void test_Finding_Element_if_Key_not_Found_in_the_Recursion_JSON_List_Should_Throw_Error()
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

/************************************************************************************************************
 * The JsonList for the findElement Function to test are as shown below,                                    *
 *                                                                                                          *
 *  {                                                                                                       *
 *    "NAME1":"JS",                                                                                         *
 *    "AGE"  :{ "NAME2":"STEVEN",                                                                           *
 *              "NAME3":"YEN"}                                                                              *
 *  }                                                                                                       *
 *                                                                                                          *
 * -Test to find the 'Key'="AGE" in recur=0.                                                                *
 * -Test to find the 'Key'="NAME3" in recur=1.                                                              *
 * -Test to get the 'Value' for the 'Key' found in recur=1.                                                 *
 *                                                                                                          *                                                                                                         *
 ************************************************************************************************************/
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
    TEST_ASSERT_NOT_NULL(findVal);
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

void test_iteratorGetNext_given_current_iterator_should_return_next_iterator()
{
  int value[]={1,3,4};

  LinkedList *ptr;
  Iterator *iter;

  ptr=createLinkedList();

  addLast(createListElement(&value[0]),ptr);
  addLast(createListElement(&value[1]),ptr);
  addLast(createListElement(&value[2]),ptr);

  TEST_ASSERT_NOT_NULL(ptr);
  iter=createIterator(ptr);

  TEST_ASSERT_NOT_NULL(iter);
  TEST_ASSERT_NOT_NULL(iter->current->next);
  TEST_ASSERT_EQUAL(1,*((int *)(iter->current->value)));
  iter=iteratorGetNext(iter);

  TEST_ASSERT_NOT_NULL(iter);
  TEST_ASSERT_NOT_NULL(iter->current->next);
  TEST_ASSERT_EQUAL(3,*((int *)(iter->current->value)));
  iter=iteratorGetNext(iter);

  TEST_ASSERT_NOT_NULL(iter);
  TEST_ASSERT_NULL(iter->current->next);
  TEST_ASSERT_EQUAL(4,*((int *)(iter->current->value)));
}
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

/****************************************************************************************************************************************************
 *                                                                                                                                                  *
 * An Example of a Simple JsonList is as shown below.                                                                                               *
 *                                                                                                                                                  *
 *  {                                                                                                                                               *
 *    "NAME1":"JS",                                                                                                                                 *
 *    "NAME2":"STEVEN"                                                                                                                              *
 *  }                                                                                                                                               *
 *                                                                                                                                                  *
 * An Example of a JsonList with Recursion is as shown below.                                                                                       *
 *                                                                                                                                                  *
 *  {                                                                                                                                               *
 *    "NAME1":"JS",                                                                                                                                 *
 *    "AGE"  :{ "NAME2":"STEVEN",                                                                                                                   *
 *              "NAME3":"YEN"}                                                                                                                      *
 *  }                                                                                                                                               *
 *                                                                                                                                                  *
 * When creating the JSON list, a single object is as shown below.                                                                                  *
 * E.g.                                                                                                                                             *
 *                         ____                                                                                                                     *
 *                        | : |                                                                                                                     *
 *                        ----                                                                                                                      *
 *                      /     \                                                                                                                     *
 *                  'NAME1'   'JS'                                                                                                                  *
 *                                                                                                                                                  *
 * Each of the OBJECT token will be linked by using the Linked List to form the JSON list.                                                          *
 * For every single OBJECT that has created above is a ListElement of the Linked List.                                                              *
 * When the input Token passing in is "{", then a Linked List has been created. So the object can be linked together by using the function AddLast. *
 * the Linking of the JSON list is as shown below,                                                                                                  *
 * E.g.                                                                                                                                             *
 *                         ____                                                                                                                     *
 *               {------->| : |------>}------>NULL                                                                                                  *
 *                        ----                                                                                                                      *
 *                      /     \                                                                                                                     *
 *                  'NAME1'   'JS'                                                                                                                  *
 *                                                                                                                                                  *
 * The Linking of the Simple JsonList mentioned above is as shown below.                                                                            *
 *                         ____                 ____                                                                                                *
 *               {------->| : |--------------->| : |--------->}------>NULL                                                                          *
 *                        ----                 ----                                                                                                 *
 *                      /     \              /     \                                                                                                *
 *                  'NAME1'   'JS'       'NAME2'  'STEVEN'                                                                                          *
 *                                                                                                                                                  *
 * The Linking of the Recursion JsonList mentioned above is as shown below.                                                                         *
 *                         ____                 ____                                                                                                *
 *               {------->| : |--------------->| : |--------->}------->NULL                                                                         *
 *                        ----                 ----                                                                                                 *
 *                      /     \              /     \           ____                 ____                                                            *
 *                  'NAME1'   'JS'       'AGE'      {-------->| : |--------------->| : |--------->}----->NULL                                       *
 *                                                            ----                 ----                                                             *
 *                                                          /     \               /     \                                                           *
 *                                                    'NAME2'    'STEVEN'    'NAME3'    'YEN'                                                       *
 *                                                                                                                                                  *
 ****************************************************************************************************************************************************
 */



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
 * Test function link2Tokens if leftToken/operatorSymbol/rightToken are NULL should return NULL;
 *
 */
void test_function_link2Tokens_with_NULL_input_should_return_NULL()
{
  Token *token1,*token2,*token3,*token4;

  token1=link2Tokens(NULL,":", token2);
  TEST_ASSERT_NULL(token1);
  token2=link2Tokens(token1,":",NULL);
  TEST_ASSERT_NULL(token2);
  token3=link2Tokens(token1,NULL,token2);
  TEST_ASSERT_NULL(token3);
  token4=link2Tokens(NULL,NULL,NULL);
  TEST_ASSERT_NULL(token4);

  free(token1);
  free(token2);
  free(token3);
  free(token4);
}

/**
 * Test if Empty Object been passed into the list
 *
 */
void test_JSON_List_with_Empty_Object_Passed_in_should_Throw_Error()
{
  printf("JSON list test No.0");
  JsonObject *jsonObj=NULL;
  Token *jsonTok;
  ErrorObject *err;

  TOKEN_DECLARE;

  Try{
    jsonTok=jsonParse(jsonObj);
    TEST_FAIL_MESSAGE("Expecting ERR_EXPECT_OPERATOR to be thrown, but none thrown.");
  }Catch(err){
    TEST_ASSERT_EQUAL_STRING("ERROR[12]:Empty object passing into the JsonParse.",err->errorMsg);
    TEST_ASSERT_EQUAL(ERR_EMPTY_OBJECT,err->errorCode);
    free(err);
  }

  free(jsonObj);
  free(jsonTok);

  TOKEN_FREE;
  printf("\n\n");
}

/**
 * at state WAIT_FOR_TOKEN,
 * Test if Empty String been passed into the list
 *
 */
void test_JSON_List_with_Empty_String_Passed_in_should_Throw_Error()
{
  printf("JSON list test No.1");
  JsonObject *jsonObj=NULL;
  Token *jsonTok;
  ErrorObject *err;

  TOKEN_DECLARE;

  getToken_ExpectAndReturn(dollarSign);

  jsonObj=createJsonObject();
  Try{
    jsonTok=jsonParse(jsonObj);
    TEST_FAIL_MESSAGE("Expecting ERR_EXPECT_OPERATOR to be thrown, but none thrown.");
  }Catch(err){
    TEST_ASSERT_EQUAL_STRING("ERROR[13]:Empty String passing into the JsonParse.",err->errorMsg);
    TEST_ASSERT_EQUAL(ERR_EMPTY_STRING,err->errorCode);
    free(err);
  }

  free(jsonObj);
  free(jsonTok);

  TOKEN_FREE;
  printf("\n\n");
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
  printf("JSON list test No.2");
  JsonObject *jsonObj=NULL;
  Token *jsonTok;
  ErrorObject *err;

  TOKEN_DECLARE;

  getToken_ExpectAndReturn(closeBrace0);   //"}"
  getToken_ExpectAndReturn(dollarSign);

  jsonObj=createJsonObject();
  Try{
    jsonTok=jsonParse(jsonObj);
    TEST_FAIL_MESSAGE("Expecting ERR_EXPECT_OPERATOR to be thrown, but none thrown.");
  }Catch(err){
    TEST_ASSERT_EQUAL_STRING("ERROR[7]:Expected '{' at the beginning of JsonList but get '}'.",err->errorMsg);
    TEST_ASSERT_EQUAL(ERR_EXPECT_OPERATOR,err->errorCode);
    free(err);
  }

  free(jsonObj);
  free(jsonTok);

  TOKEN_FREE;
  printf("\n\n");
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
  printf("JSON list test No.3");
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
    TEST_FAIL_MESSAGE("Expecting ERR_EXPECT_OPERATOR to be thrown, but none thrown.");
  }Catch(err){
    TEST_ASSERT_EQUAL_STRING("ERROR[7]:Expected '{' at the beginning of JsonList but get '}'.",err->errorMsg);
    TEST_ASSERT_EQUAL(ERR_EXPECT_OPERATOR,err->errorCode);
    free(err);
  }
  free(jsonObj);
  free(jsonTok);

  TOKEN_FREE;
  printf("\n\n");
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
  printf("JSON list test No.4");
  JsonObject *jsonObj=NULL;
  Token *jsonTok;
  ErrorObject *err;

  TOKEN_DECLARE;

  getToken_ExpectAndReturn(openBrace0);   //"{"
  getToken_ExpectAndReturn(dollarSign);

  jsonObj=createJsonObject();
  Try{
    jsonTok=jsonParse(jsonObj);
    TEST_FAIL_MESSAGE("Expecting ERR_ACCESS_DENIED to be thrown, but none thrown.");
  }Catch(err){
    TEST_ASSERT_EQUAL_STRING("ERROR[9]:ACCESS DENIED!!!The Json List is not completed.",err->errorMsg);
    TEST_ASSERT_EQUAL(ERR_ACCESS_DENIED,err->errorCode);
    free(err);
  }
  free(jsonObj);
  free(jsonTok);

  TOKEN_FREE;
  printf("\n\n");
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
  printf("JSON list test No.5");
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
    TEST_FAIL_MESSAGE("Expecting ERR_EXPECT_IDEN to be thrown, but none thrown.");
  }Catch(err){
    TEST_ASSERT_EQUAL_STRING("ERROR[8]:Expected an Identifier for 'Key' but get 'JS'.",err->errorMsg);
    TEST_ASSERT_EQUAL(ERR_EXPECT_IDEN,err->errorCode);
    free(err);
  }
  free(jsonObj);
  free(jsonTok);

  TOKEN_FREE;
  printf("\n\n");
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
  printf("JSON list test No.6");
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
    TEST_FAIL_MESSAGE("Expecting ERR_ACCESS_DENIED to be thrown, but none thrown.");
  }Catch(err){
    TEST_ASSERT_EQUAL_STRING("ERROR[9]:ACCESS DENIED!!!The Json List is not completed.",err->errorMsg);
    TEST_ASSERT_EQUAL(ERR_ACCESS_DENIED,err->errorCode);
    free(err);
  }
  free(jsonObj);
  free(jsonTok);

  TOKEN_FREE;
  printf("\n\n");
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
  printf("JSON list test No.7");
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
    TEST_FAIL_MESSAGE("Expecting ERR_EXPECT_OPERATOR to be thrown, but none thrown.");
  }Catch(err){
    TEST_ASSERT_EQUAL_STRING("ERROR[7]:Expected ':' after 'Key' but get '}'.\n\n'NAME1'}\n       ^\n",err->errorMsg);
    TEST_ASSERT_EQUAL(ERR_EXPECT_OPERATOR,err->errorCode);
    free(err);
  }
  free(jsonObj);
  free(jsonTok);

  TOKEN_FREE;
  printf("\n\n");
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
  printf("JSON list test No.8");
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
    TEST_FAIL_MESSAGE("Expecting ERR_EXPECT_OPERATOR to be thrown, but none thrown.");
  }Catch(err){
    TEST_ASSERT_EQUAL_STRING("ERROR[7]:Expected ':' after 'Key' but get 'JS'.\n\n'NAME1''JS'\n       ^\n",err->errorMsg);
    TEST_ASSERT_EQUAL(ERR_EXPECT_OPERATOR,err->errorCode);
    free(err);
  }
  free(jsonObj);
  free(jsonTok);

  TOKEN_FREE;
  printf("\n\n");
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
  printf("JSON list test No.9");
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
    TEST_FAIL_MESSAGE("Expecting ERR_EXPECT_OPERATOR to be thrown, but none thrown.");
  }Catch(err){
    TEST_ASSERT_EQUAL_STRING("ERROR[7]:Expected ':' after 'Key' but get '20'.\n\n'NAME1'20\n       ^\n",err->errorMsg);
    TEST_ASSERT_EQUAL(ERR_EXPECT_OPERATOR,err->errorCode);
    free(err);
  }
  free(jsonObj);
  free(jsonTok);

  TOKEN_FREE;
  printf("\n\n");
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
  printf("JSON list test No.10");
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
    TEST_FAIL_MESSAGE("Expecting ERR_ACCESS_DENIED to be thrown, but none thrown.");
  }Catch(err){
    TEST_ASSERT_EQUAL_STRING("ERROR[9]:ACCESS DENIED!!!The Json List is not completed.",err->errorMsg);
    TEST_ASSERT_EQUAL(ERR_ACCESS_DENIED,err->errorCode);
    free(err);
  }
  free(jsonObj);
  free(jsonTok);

  TOKEN_FREE;
  printf("\n\n");
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
  printf("JSON list test No.11");
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
    TEST_FAIL_MESSAGE("Expecting ERR_ILLEGAL_VALUE to be thrown, but none thrown.");
  }Catch(err){
    TEST_ASSERT_EQUAL_STRING("ERROR[10]:Expected an Integer/String/Float/{ for 'Value' but get }.\n\n'NAME1':}\n        ^\n",err->errorMsg);
    TEST_ASSERT_EQUAL(ERR_ILLEGAL_VALUE,err->errorCode);
    free(err);
  }
  free(jsonObj);
  free(jsonTok);

  TOKEN_FREE;
  printf("\n\n");
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
  printf("JSON list test No.12");
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
    TEST_FAIL_MESSAGE("Expecting ERR_ACCESS_DENIED to be thrown, but none thrown.");
  }Catch(err){
    TEST_ASSERT_EQUAL_STRING("ERROR[9]:ACCESS DENIED!!!The Json List is not completed.",err->errorMsg);
    TEST_ASSERT_EQUAL(ERR_ACCESS_DENIED,err->errorCode);
    free(err);
  }
  free(jsonObj);
  free(jsonTok);

  TOKEN_FREE;
  printf("\n\n");
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
  printf("JSON list test No.13");
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
    TEST_FAIL_MESSAGE("Expecting ERR_EXPECT_OPERATOR to be thrown, but none thrown.");
  }Catch(err){
    TEST_ASSERT_EQUAL_STRING("ERROR[7]:Expected Operator '}' or ',' after 'Value' but get '^'.\n\n'NAME1':'JS'^\n            ^\n",err->errorMsg);
    TEST_ASSERT_EQUAL(ERR_EXPECT_OPERATOR,err->errorCode);
    free(err);
  }
  free(jsonObj);
  free(jsonTok);

  TOKEN_FREE;
  printf("\n\n");
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
  printf("JSON list test No.14");
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
    TEST_FAIL_MESSAGE("Expecting ERR_EXPECT_OPERATOR to be thrown, but none thrown.");
  }Catch(err){
    TEST_ASSERT_EQUAL_STRING("ERROR[7]:Expected Operator '}' or ',' after 'Value' but get 'NAME2'.\n\n'NAME1':'JS''NAME2'\n            ^\n",err->errorMsg);
    TEST_ASSERT_EQUAL(ERR_EXPECT_OPERATOR,err->errorCode);
    free(err);
  }
  free(jsonObj);
  free(jsonTok);

  TOKEN_FREE;
  printf("\n\n");
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
  printf("JSON list test No.15");
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
    TEST_FAIL_MESSAGE("Expecting ERR_EXPECT_OPERATOR to be thrown, but none thrown.");
  }Catch(err){
    TEST_ASSERT_EQUAL_STRING("ERROR[7]:Expected Operator '}' or ',' after 'Value' but get '20'.\n\n'NAME1':'JS'20\n            ^\n",err->errorMsg);
    TEST_ASSERT_EQUAL(ERR_EXPECT_OPERATOR,err->errorCode);
    free(err);
  }
  free(jsonObj);
  free(jsonTok);

  TOKEN_FREE;
  printf("\n\n");
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
  printf("JSON list test No.16");
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
    TEST_FAIL_MESSAGE("Expecting ERR_ACCESS_DENIED to be thrown, but none thrown.");
  }Catch(err){
    TEST_ASSERT_EQUAL_STRING("ERROR[9]:ACCESS DENIED!!!The Json List is not completed.",err->errorMsg);
    TEST_ASSERT_EQUAL(ERR_ACCESS_DENIED,err->errorCode);
    free(err);
  }
  free(jsonObj);
  free(jsonTok);

  TOKEN_FREE;
  printf("\n\n");
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
  printf("JSON list test No.17");
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
    TEST_FAIL_MESSAGE("Expecting ERR_EXPECT_OPERATOR to be thrown, but none thrown.");
  }Catch(err){
    TEST_ASSERT_EQUAL_STRING("ERROR[7]:Expected Operator '}' or ',' after 'Value' but get '^'.\n\n'NAME1':20^\n          ^\n",err->errorMsg);
    TEST_ASSERT_EQUAL(ERR_EXPECT_OPERATOR,err->errorCode);
    free(err);
  }
  free(jsonObj);
  free(jsonTok);

  TOKEN_FREE;
  printf("\n\n");
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
  printf("JSON list test No.18");
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
    TEST_FAIL_MESSAGE("Expecting ERR_EXPECT_OPERATOR to be thrown, but none thrown.");
  }Catch(err){
    TEST_ASSERT_EQUAL_STRING("ERROR[7]:Expected Operator '}' or ',' after 'Value' but get 'JS'.\n\n'NAME1':20'JS'\n          ^\n",err->errorMsg);
    TEST_ASSERT_EQUAL(ERR_EXPECT_OPERATOR,err->errorCode);
    free(err);
  }
  free(jsonObj);
  free(jsonTok);

  TOKEN_FREE;
  printf("\n\n");
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
  printf("JSON list test No.19");
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
    TEST_FAIL_MESSAGE("Expecting ERR_EXPECT_OPERATOR to be thrown, but none thrown.");
  }Catch(err){
    TEST_ASSERT_EQUAL_STRING("ERROR[7]:Expected Operator '}' or ',' after 'Value' but get '30'.\n\n'NAME1':20 30\n           ^\n",err->errorMsg);
    TEST_ASSERT_EQUAL(ERR_EXPECT_OPERATOR,err->errorCode);
    free(err);
  }
  free(jsonObj);
  free(jsonTok);

  TOKEN_FREE;
  printf("\n\n");
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
  printf("JSON list test No.20");
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
    TEST_FAIL_MESSAGE("Expecting ERR_ACCESS_DENIED to be thrown, but none thrown.");
  }Catch(err){
    TEST_ASSERT_EQUAL_STRING("ERROR[9]:ACCESS DENIED!!!The Json List is not completed.",err->errorMsg);
    TEST_ASSERT_EQUAL(ERR_ACCESS_DENIED,err->errorCode);
    free(err);
  }
  free(jsonObj);
  free(jsonTok);

  TOKEN_FREE;
  printf("\n\n");
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
  printf("JSON list test No.21");
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
  printf("\n\n");
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
  printf("JSON list test No.22");
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
    TEST_FAIL_MESSAGE("Expecting ERR_ACCESS_DENIED to be thrown, but none thrown.");
  }Catch(err){
    TEST_ASSERT_EQUAL_STRING("ERROR[9]:ACCESS DENIED!!!The Json List already completed.",err->errorMsg);
    TEST_ASSERT_EQUAL(ERR_ACCESS_DENIED,err->errorCode);
    free(err);
  }

  free(jsonObj);
  free(jsonTok);
  free(iter);

  TOKEN_FREE;
  printf("\n\n");
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
  printf("JSON list test No.23");
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
    TEST_FAIL_MESSAGE("Expecting ERR_ACCESS_DENIED to be thrown, but none thrown.");
  }Catch(err){
    TEST_ASSERT_EQUAL_STRING("ERROR[9]:ACCESS DENIED!!!The Json List is not completed.",err->errorMsg);
    TEST_ASSERT_EQUAL(ERR_ACCESS_DENIED,err->errorCode);
    free(err);
  }

  free(jsonObj);
  free(jsonTok);

  TOKEN_FREE;
  printf("\n\n");
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
  printf("JSON list test No.24");
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
    TEST_FAIL_MESSAGE("Expecting ERR_EXPECT_IDEN to be thrown, but none thrown.");
  }Catch(err){
    TEST_ASSERT_EQUAL_STRING("ERROR[8]:Expected an Identifier for 'Key' but get 'STEVEN'.",err->errorMsg);
    TEST_ASSERT_EQUAL(ERR_EXPECT_IDEN,err->errorCode);
    free(err);
  }

  free(jsonObj);
  free(jsonTok);

  TOKEN_FREE;
  printf("\n\n");
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
  printf("JSON list test No.25");
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
    TEST_FAIL_MESSAGE("Expecting ERR_ACCESS_DENIED to be thrown, but none thrown.");
  }Catch(err){
    TEST_ASSERT_EQUAL_STRING("ERROR[9]:ACCESS DENIED!!!The Json List is not completed.",err->errorMsg);
    TEST_ASSERT_EQUAL(ERR_ACCESS_DENIED,err->errorCode);
    free(err);
  }

  free(jsonObj);
  free(jsonTok);

  TOKEN_FREE;
  printf("\n\n");
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
  printf("JSON list test No.26");
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
    TEST_FAIL_MESSAGE("Expecting ERR_EXPECT_OPERATOR to be thrown, but none thrown.");
  }Catch(err){
    TEST_ASSERT_EQUAL_STRING("ERROR[7]:Expected ':' after 'Key' but get '^'.\n\n'NAME2'^\n       ^\n",err->errorMsg);
    TEST_ASSERT_EQUAL(ERR_EXPECT_OPERATOR,err->errorCode);
    free(err);
  }

  free(jsonObj);
  free(jsonTok);

  TOKEN_FREE;
  printf("\n\n");
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
  printf("JSON list test No.27");
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
    TEST_FAIL_MESSAGE("Expecting ERR_EXPECT_OPERATOR to be thrown, but none thrown.");
  }Catch(err){
    TEST_ASSERT_EQUAL_STRING("ERROR[7]:Expected ':' after 'Key' but get 'STEVEN'.\n\n'NAME2''STEVEN'\n       ^\n",err->errorMsg);
    TEST_ASSERT_EQUAL(ERR_EXPECT_OPERATOR,err->errorCode);
    free(err);
  }

  free(jsonObj);
  free(jsonTok);

  TOKEN_FREE;
  printf("\n\n");
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
  printf("JSON list test No.28");
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
    TEST_FAIL_MESSAGE("Expecting ERR_EXPECT_OPERATOR to be thrown, but none thrown.");
  }Catch(err){
    TEST_ASSERT_EQUAL_STRING("ERROR[7]:Expected ':' after 'Key' but get '20'.\n\n'NAME2'20\n       ^\n",err->errorMsg);
    TEST_ASSERT_EQUAL(ERR_EXPECT_OPERATOR,err->errorCode);
    free(err);
  }

  free(jsonObj);
  free(jsonTok);

  TOKEN_FREE;
  printf("\n\n");
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
  printf("JSON list test No.29");
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
    TEST_FAIL_MESSAGE("Expecting ERR_ACCESS_DENIED to be thrown, but none thrown.");
  }Catch(err){
    TEST_ASSERT_EQUAL_STRING("ERROR[9]:ACCESS DENIED!!!The Json List is not completed.",err->errorMsg);
    TEST_ASSERT_EQUAL(ERR_ACCESS_DENIED,err->errorCode);
    free(err);
  }

  free(jsonObj);
  free(jsonTok);

  TOKEN_FREE;
  printf("\n\n");
}

/**
 * at state VALUE,
 * Test if closeBrace token has been passed in after Colon token
 *
 *  {
 *    "NAME1":"JS",
 *    "AGE"  :{"NAME2":^
 *
 */
void test_Recursion_JSON_List_with_caret_Token_Passed_in_after_Colon_Token_should_Throw_Error()
{
  printf("JSON list test No.30");
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
  getToken_ExpectAndReturn(caret);         //"^"
  getToken_ExpectAndReturn(dollarSign);

  jsonObj=createJsonObject();
  Try{
    jsonTok=jsonParse(jsonObj);
    TEST_FAIL_MESSAGE("Expecting ERR_ILLEGAL_VALUE to be thrown, but none thrown.");
  }Catch(err){
    TEST_ASSERT_EQUAL_STRING("ERROR[10]:Expected an Integer/String/Float/{ for 'Value' but get ^.\n\n'NAME2':^\n        ^\n",err->errorMsg);
    TEST_ASSERT_EQUAL(ERR_ILLEGAL_VALUE,err->errorCode);
    free(err);
  }

  free(jsonObj);
  free(jsonTok);

  TOKEN_FREE;
  printf("\n\n");
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
  printf("JSON list test No.31");
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
    TEST_FAIL_MESSAGE("Expecting ERR_ACCESS_DENIED to be thrown, but none thrown.");
  }Catch(err){
    TEST_ASSERT_EQUAL_STRING("ERROR[9]:ACCESS DENIED!!!The Json List is not completed.",err->errorMsg);
    TEST_ASSERT_EQUAL(ERR_ACCESS_DENIED,err->errorCode);
    free(err);
  }

  free(jsonObj);
  free(jsonTok);

  TOKEN_FREE;
  printf("\n\n");
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
  printf("JSON list test No.32");
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
    TEST_FAIL_MESSAGE("Expecting ERR_EXPECT_OPERATOR to be thrown, but none thrown.");
  }Catch(err){
    TEST_ASSERT_EQUAL_STRING("ERROR[7]:Expected Operator '}' or ',' after 'Value' but get '^'.\n\n'NAME2':'STEVEN'^\n                ^\n",err->errorMsg);
    TEST_ASSERT_EQUAL(ERR_EXPECT_OPERATOR,err->errorCode);
    free(err);
  }

  free(jsonObj);
  free(jsonTok);

  TOKEN_FREE;
  printf("\n\n");
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
  printf("JSON list test No.33");
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
    TEST_FAIL_MESSAGE("Expecting ERR_EXPECT_OPERATOR to be thrown, but none thrown.");
  }Catch(err){
    TEST_ASSERT_EQUAL_STRING("ERROR[7]:Expected Operator '}' or ',' after 'Value' but get 'YEN'.\n\n'NAME2':'STEVEN''YEN'\n                ^\n",err->errorMsg);
    TEST_ASSERT_EQUAL(ERR_EXPECT_OPERATOR,err->errorCode);
    free(err);
  }

  free(jsonObj);
  free(jsonTok);

  TOKEN_FREE;
  printf("\n\n");
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
  printf("JSON list test No.34");
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
    TEST_FAIL_MESSAGE("Expecting ERR_EXPECT_OPERATOR to be thrown, but none thrown.");
  }Catch(err){
    TEST_ASSERT_EQUAL_STRING("ERROR[7]:Expected Operator '}' or ',' after 'Value' but get '20'.\n\n'NAME2':'STEVEN'20\n                ^\n",err->errorMsg);
    TEST_ASSERT_EQUAL(ERR_EXPECT_OPERATOR,err->errorCode);
    free(err);
  }

  free(jsonObj);
  free(jsonTok);

  TOKEN_FREE;
  printf("\n\n");
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
  printf("JSON list test No.35");
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
    TEST_FAIL_MESSAGE("Expecting ERR_ACCESS_DENIED to be thrown, but none thrown.");
  }Catch(err){
    TEST_ASSERT_EQUAL_STRING("ERROR[9]:ACCESS DENIED!!!The Json List is not completed.",err->errorMsg);
    TEST_ASSERT_EQUAL(ERR_ACCESS_DENIED,err->errorCode);
    free(err);
  }

  free(jsonObj);
  free(jsonTok);

  TOKEN_FREE;
  printf("\n\n");
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
  printf("JSON list test No.36");
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
    TEST_FAIL_MESSAGE("Expecting ERR_EXPECT_OPERATOR to be thrown, but none thrown.");
  }Catch(err){
    TEST_ASSERT_EQUAL_STRING("ERROR[7]:Expected Operator '}' or ',' after 'Value' but get '^'.\n\n'NAME2':20^\n          ^\n",err->errorMsg);
    TEST_ASSERT_EQUAL(ERR_EXPECT_OPERATOR,err->errorCode);
    free(err);
  }

  free(jsonObj);
  free(jsonTok);

  TOKEN_FREE;
  printf("\n\n");
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
  printf("JSON list test No.37");
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
    TEST_FAIL_MESSAGE("Expecting ERR_EXPECT_OPERATOR to be thrown, but none thrown.");
  }Catch(err){
    TEST_ASSERT_EQUAL_STRING("ERROR[7]:Expected Operator '}' or ',' after 'Value' but get 'YEN'.\n\n'NAME2':20'YEN'\n          ^\n",err->errorMsg);
    TEST_ASSERT_EQUAL(ERR_EXPECT_OPERATOR,err->errorCode);
    free(err);
  }

  free(jsonObj);
  free(jsonTok);

  TOKEN_FREE;
  printf("\n\n");
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
  printf("JSON list test No.38");
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
    TEST_FAIL_MESSAGE("Expecting ERR_EXPECT_OPERATOR to be thrown, but none thrown.");
  }Catch(err){
    TEST_ASSERT_EQUAL_STRING("ERROR[7]:Expected Operator '}' or ',' after 'Value' but get '30'.\n\n'NAME2':20 30\n           ^\n",err->errorMsg);
    TEST_ASSERT_EQUAL(ERR_EXPECT_OPERATOR,err->errorCode);
    free(err);
  }

  free(jsonObj);
  free(jsonTok);

  TOKEN_FREE;
  printf("\n\n");
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
  printf("JSON list test No.39");
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
    TEST_FAIL_MESSAGE("Expecting ERR_ACCESS_DENIED to be thrown, but none thrown.");
  }Catch(err){
    TEST_ASSERT_EQUAL_STRING("ERROR[9]:ACCESS DENIED!!!The Json List is not completed.",err->errorMsg);
    TEST_ASSERT_EQUAL(ERR_ACCESS_DENIED,err->errorCode);
    free(err);
  }

  free(jsonObj);
  free(jsonTok);

  TOKEN_FREE;
  printf("\n\n");
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
  printf("JSON list test No.40");
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
    TEST_FAIL_MESSAGE("Expecting ERR_ACCESS_DENIED to be thrown, but none thrown.");
  }Catch(err){
    TEST_ASSERT_EQUAL_STRING("ERROR[9]:ACCESS DENIED!!!The Json List is not completed.",err->errorMsg);
    TEST_ASSERT_EQUAL(ERR_ACCESS_DENIED,err->errorCode);
    free(err);
  }

  free(jsonObj);
  free(jsonTok);

  TOKEN_FREE;
  printf("\n\n");
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
  printf("JSON list test No.41");
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
  printf("\n\n");
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
  printf("JSON list test No.42");
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
    TEST_FAIL_MESSAGE("Expecting ERR_ACCESS_DENIED to be thrown, but none thrown.");
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
  printf("\n\n");
}


/**
 * Test for Complex JsonList
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
  printf("JSON list test No.43");
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
  printf("\n\n");
}


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

void setUp(void)
{
}

void tearDown(void)
{
}

/************************************************************************
 * Testing function createLinkedList.                                   *
 * -Initially the head and the tail are pointing to NULL.               *
 * -the starting length of the list has set to zero.                    *
 *                                                                      *
 *    list---+-->head-----+                                             *   
 *           |            |                                             *
 *           +-->tail-----+                                             *
 *                        |                                             *
 *                        v                                             *
 *                       NULL                                           *
 *                                                                      *
 ************************************************************************/
void test_function_createLinkedList()
{
  LinkedList *list;
  list = createLinkedList();

  TEST_ASSERT_NOT_NULL(list);
  TEST_ASSERT_NULL(list->head);
  TEST_ASSERT_NULL(list->tail);
  TEST_ASSERT_EQUAL(0,list->length);
}

/************************************************************************
 * Testing function createListElement given NULL value.                 *
 * -If the passing in address is NULL, the function will return NULL.   *
 *            ____________                                              *
 *           |  newNode  |                                              *
 *           -------------                                              *
 *   value   |    NULL   |                                              *
 *           -------------                                              *
 *           |   next    |---->NULL                                     *
 *           -------------                                              *
 *                                                                      *
 ************************************************************************/
void test_function_createListElement_given_NULL_value_should_return_NULL()
{
  ListElement *newNode;

  newNode = createListElement(NULL);

  TEST_ASSERT_NULL(newNode);
}

/************************************************************************
 * Testing function createListElement for any type of value.            *
 * -This function is able to pass in any type of value.                 *
 * -Initially the next pointer of the function is pointing to NULL.     *   
 *                         ____________                                 *
 *                        |  newNode  |                                 *
 *                        -------------                                 *
 *                        |   value   |                                 *
 *                        -------------                                 *
 *                        |   next    |---->NULL                        *
 *                        -------------                                 *
 *                                                                      *
 *                                                                      *
 *  For Integer Value,                                                  *
 *                         ____________                                 *
 *                        |  newNode  |                                 *
 *                        -------------                                 *
 *               value    |    1      |                                 *
 *                        -------------                                 *
 *                        |   next    |---->NULL                        *
 *                        -------------                                 * 
 *                                                                      *
 *                                                                      *
 *  For String Value,                                                   *
 *                         ____________                                 *
 *                        |  newNode  |                                 *
 *                        -------------                                 *
 *               value    |"JangSing" |                                 *
 *                        -------------                                 *
 *                        |   next    |---->NULL                        *
 *                        -------------                                 * 
 *                                                                      * 
 *                                                                      * 
 *  For Token Value,                                                    *
 *                         ____________                                 *
 *                        |  newNode  |                                 *
 *                        -------------                                 *
 *               value    |  Token    |                                 *
 *                        -------------                                 *
 *                        |   next    |---->NULL                        *
 *                        -------------                                 * 
 *                                                                      * 
 ************************************************************************/
void test_function_createListElement_for_Integer_value()
{
  ListElement *newNode;
  int value=1;

  newNode = createListElement(&value);

  TEST_ASSERT_NOT_NULL(newNode);
  TEST_ASSERT_NOT_NULL(newNode->value);
  TEST_ASSERT_EQUAL(1,*(int *)newNode->value);
  TEST_ASSERT_NULL(newNode->next);
}

void test_function_createListElement_for_String_value()
{
  ListElement *newNode;
  char *value="JangSing";

  newNode = createListElement(value);

  TEST_ASSERT_NOT_NULL(newNode);
  TEST_ASSERT_NOT_NULL(newNode->value);
  TEST_ASSERT_EQUAL_STRING("JangSing",(char *)newNode->value);
  TEST_ASSERT_NULL(newNode->next);
}

void test_function_createListElement_for_Token_value()
{
  ListElement *newNode;
  IntegerToken *intTok;

  intTok=(IntegerToken *)createIntegerToken(123);
  newNode = createListElement(intTok);

  TEST_ASSERT_NOT_NULL(newNode);
  TEST_ASSERT_NOT_NULL(newNode->value);

  TEST_ASSERT_EQUAL(123,intTok->value);

  TEST_ASSERT_EQUAL(123,((IntegerToken *)(newNode->value))->value);
  TEST_ASSERT_EQUAL(TOKEN_INTEGER_TYPE,((IntegerToken *)(newNode->value))->type);
}

/*********************************************************************************
 * Testing function addLast when one element added to the LinkedList.            *
 * -The addLast function will pass in the ListElement and the List.              *
 * -The function will add the Element to the tail of the List.                   *
 * -If either Element or List is pointing to NULL,the function will do nothing.  *
 *                                                                               *
 *                                   ___________                                 *
 *          list---+-->head-------->|  value=5 |                                 *
 *                 |                |__________|---->NULL                        *
 *                 |                    ^                                        *
 *                 |                    |                                        *
 *                 +-->tail-------------+                                        *
 *                                                                               *
 *********************************************************************************/           
void test_Adding_one_element_to_LinkedList_using_function_AddLast()
{
  int value=5;

  LinkedList *list;

  list  = createLinkedList();

  addLast(createListElement(&value),list);

  TEST_ASSERT_NOT_NULL(list);
  TEST_ASSERT_NOT_NULL(list->head);
  TEST_ASSERT_NOT_NULL(list->tail);

  TEST_ASSERT_EQUAL(5,*((int *)(list->head->value)));
  TEST_ASSERT_NULL(list->head->next);
  TEST_ASSERT_EQUAL(5,*((int *)(list->tail->value)));
  TEST_ASSERT_NULL(list->tail->next);
  TEST_ASSERT_EQUAL(1,list->length);
}

void test_addLast_Function_given_NULL_Element_Should_do_nothing()
{
  int i;
  int value1=1;
  int value2=2;

  LinkedList *list;
  
  list=createLinkedList();

  addLast(createListElement(&value1),list);
  addLast(NULL,list);
  addLast(createListElement(&value2),list);

  TEST_ASSERT_NOT_NULL(list);
  TEST_ASSERT_EQUAL(1,*((int *)(list->head->value)));
  TEST_ASSERT_EQUAL_PTR(list->tail,list->head->next);
  TEST_ASSERT_EQUAL(2,*((int *)(list->tail->value)));
  TEST_ASSERT_NULL(list->tail->next);
  TEST_ASSERT_EQUAL(2,list->length);
}

void test_addLast_Function_given_NULL_List_Should_do_nothing()
{
  int value[]={1,2};

  LinkedList *list;
  list=createLinkedList();

  addLast(createListElement(&value[0]),NULL);
  addLast(createListElement(&value[1]),list);

  TEST_ASSERT_NOT_NULL(list);
  TEST_ASSERT_NOT_NULL(list->head);
  TEST_ASSERT_NOT_NULL(list->tail);

  TEST_ASSERT_EQUAL(2,*((int *)(list->head->value)));
  TEST_ASSERT_NULL(list->head->next);
  TEST_ASSERT_EQUAL(2,*((int *)(list->tail->value)));
  TEST_ASSERT_NULL(list->tail->next);
  TEST_ASSERT_EQUAL(1,list->length);
}

/**********************************************************************************
 * Testing function addLast when two element added to the LinkedList.             *
 *                                                                                *
 *                      1st Ele         2nd Ele                                   *
 *                      _________      _________                                  *
 *   list---+-->head-->| value=1|     | value=2|                                  *
 *          |          |________|---->|________|---->NULL                         *
 *          |                             ^                                       *
 *          |                             |                                       *
 *          +-->tail----------------------+                                       *
 *                                                                                *
 **********************************************************************************/ 
void test_Adding_two_element_to_LinkedList_using_function_addLast()
{
  int i;
  int value[]={1,2};

  LinkedList *list;
  list=createLinkedList();

  for(i=0;i<2;i++){
    addLast(createListElement(&value[i]),list);
  }

  TEST_ASSERT_EQUAL(1,*((int *)(list->head->value)));
  TEST_ASSERT_NOT_NULL(list->head);
  TEST_ASSERT_NOT_NULL(list->tail);
  TEST_ASSERT_EQUAL_PTR(list->tail,list->head->next);
  TEST_ASSERT_EQUAL(2,*((int *)(list->tail->value)));
  TEST_ASSERT_NULL(list->tail->next);
  TEST_ASSERT_EQUAL(2,list->length);
}

/**********************************************************************************
 * Testing function AddLast when three element added to the LinkedList.           *
 *                                                                                *
 *                     1st Ele        2nd Ele        3rd Ele                      *
 *                    _________      _________      _________                     *
 * list---+-->head-->| value=1|     | value=2|     | value=3|                     *
 *        |          |________|---->|________|---->|________|---->NULL            *
 *        |                                            ^                          *
 *        |                                            |                          *
 *        +-->tail-------------------------------------+                          *
 *                                                                                *
 **********************************************************************************/
void test_Adding_three_element_to_LinkedList_using_function_addLast()
{
  int i;
  int value[]={1,2,3};

  LinkedList *list;
  Iterator *iter;
  list=createLinkedList();

  for(i=0;i<3;i++){
    addLast(createListElement(&value[i]),list);
  }

  TEST_ASSERT_NOT_NULL(list);
  iter=createIterator(list);
  TEST_ASSERT_EQUAL(*((int *)(list->head->value)),*((int *)(iter->current->value)));
  TEST_ASSERT_EQUAL(1,*((int *)(iter->current->value)));
  iter=iteratorGetNext(iter);
  TEST_ASSERT_EQUAL(2,*((int *)(iter->current->value)));
  iter=iteratorGetNext(iter);
  TEST_ASSERT_EQUAL(*((int *)(list->tail->value)),*((int *)(iter->current->value)));
  TEST_ASSERT_EQUAL(3,*((int *)(iter->current->value)));
  iter=iteratorGetNext(iter);
  TEST_ASSERT_NULL(iter->current);
  TEST_ASSERT_EQUAL(3,list->length);
}


void test_Adding_five_element_to_LinkedList_using_function_addLast()
{
  int i;
  int value[]={95,100,14,111,123};

  LinkedList *list;
  Iterator *iter;
  list = createLinkedList();

  for(i=0;i<5;i++){
    addLast(createListElement(&value[i]),list);
  }

  TEST_ASSERT_NOT_NULL(list);
  iter=createIterator(list);
  TEST_ASSERT_EQUAL(95  ,*((int *)(iter->current->value)));
  iter=iteratorGetNext(iter);
  TEST_ASSERT_EQUAL(100 ,*((int *)(iter->current->value)));
  iter=iteratorGetNext(iter);
  TEST_ASSERT_EQUAL(14  ,*((int *)(iter->current->value)));
  iter=iteratorGetNext(iter);
  TEST_ASSERT_EQUAL(111 ,*((int *)(iter->current->value)));
  iter=iteratorGetNext(iter);
  TEST_ASSERT_EQUAL(123 ,*((int *)(iter->current->value)));
  iter=iteratorGetNext(iter);
  TEST_ASSERT_NULL(iter->current);
  TEST_ASSERT_EQUAL(5,list->length);
}






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

void setUp()
{
}

void tearDown()
{
}


/*********************************************************************
 *  test for Compare Function. (intCompare & strCompare)             *
 *  -if values are equal, function will return 0.                    *
 *  -if either values are NULL, function will return -1.             *
 *  -else the function will return 1.                                *
 *                                                                   *
 *********************************************************************/
void test_function_intCompare()
{
  int value[10]={1212,2121,1556,1556};
  char *str[10]={"JS","HAHAHA","hello","Hello","hello"};

  TEST_ASSERT_EQUAL(1,intCompare(&value[0], &value[1]));
  TEST_ASSERT_EQUAL(0,intCompare(&value[2], &value[3]));

  TEST_ASSERT_EQUAL(1,intCompare(&str[0], &str[1]));
  TEST_ASSERT_EQUAL(1,intCompare(&str[2], &str[3]));
  TEST_ASSERT_EQUAL(0,intCompare(&str[2], &str[4]));
  
  TEST_ASSERT_EQUAL(-1,intCompare(NULL, &value[3]));
  TEST_ASSERT_EQUAL(-1,intCompare(&value[3], NULL));
}

void test_function_strCompare()
{
  int value[10]={1212,2121,1556,1556};
  char *str[10]={"JS","HAHAHA","hello","Hello","hello"};

  TEST_ASSERT_EQUAL(1,strCompare(&value[0], &value[1]));
  TEST_ASSERT_EQUAL(0,strCompare(&value[2], &value[3]));

  TEST_ASSERT_EQUAL(1,strCompare(&str[0], &str[1]));
  TEST_ASSERT_EQUAL(1,strCompare(&str[2], &str[3]));
  TEST_ASSERT_EQUAL(0,strCompare(&str[2], &str[4]));

  TEST_ASSERT_EQUAL(-1,strCompare(NULL, &str[3]));
  TEST_ASSERT_EQUAL(-1,strCompare(&str[3], NULL));
}
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
