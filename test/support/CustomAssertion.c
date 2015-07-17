#include "CustomAssertion.h"
#include "Token.h"
#include "JSON.h"
#include "LinkedList.h"
#include "IteratorFunction.h"
#include "FindElementFunction.h"

#include <stdio.h>

void customTestAssertKeyValue(void *key, void *value, ListElement *actual, int lineNo){

  Iterator *iter;

  if (key==NULL || value==NULL || actual==NULL){
    CUSTOM_TEST_FAIL("ERROR:The key or value or actual cannot be NULL.");
  }
  else{
    OperatorToken *opTok=((OperatorToken *)(actual->value));

    char *idenKey=((IdentifierToken *)(key))->name;
    char *strValue=((StringToken *)(value))->name;
    int  intValue=((IntegerToken *)(value))->value;
    double  floatValue=((FloatToken *)(value))->value;

    char *leftToken=((IdentifierToken *)(opTok->token[0]))->name;
    char *charRightToken=((StringToken *)(opTok->token[1]))->name;
    int  intRightToken=((IntegerToken *)(opTok->token[1]))->value;
    double  floatRightToken=((FloatToken *)(opTok->token[1]))->value;

    iter=createIterator((LinkedList *)(opTok->token[1]));


    UNITY_TEST_ASSERT_EQUAL_STRING(":", opTok->symbol, lineNo, NULL);


    //test for KEY token
    if(opTok->token[0]->type==TOKEN_IDENTIFIER_TYPE){
      if(((Token *)(key))->type==TOKEN_IDENTIFIER_TYPE){
        UNITY_TEST_ASSERT_EQUAL_STRING(idenKey,leftToken,lineNo, NULL);
      }
      else{
        CUSTOM_TEST_FAIL("ERROR:Actual value for KEY was %s",leftToken);
      }
    }
    else{
      CUSTOM_TEST_FAIL("ERROR:Unexpected Token type.");
    }

    //test for VALUE token
    if(opTok->token[1]->type==TOKEN_STRING_TYPE){
      if(((Token *)(value))->type==TOKEN_STRING_TYPE){
        UNITY_TEST_ASSERT_EQUAL_STRING(strValue,charRightToken,lineNo, NULL);
      }
      else{
        CUSTOM_TEST_FAIL("ERROR:Actual value for VALUE was %s",charRightToken);
      }
    }
    else if(opTok->token[1]->type==TOKEN_INTEGER_TYPE){
      if(((Token *)(value))->type==TOKEN_INTEGER_TYPE){
        UNITY_TEST_ASSERT_EQUAL_INT(intValue,intRightToken, lineNo, NULL);
      }
      else{
        CUSTOM_TEST_FAIL("ERROR:Actual value for VALUE was %d",intRightToken);
      }
    }
    else if(opTok->token[1]->type==TOKEN_FLOAT_TYPE){
      if(((Token *)(value))->type==TOKEN_FLOAT_TYPE){
        UNITY_TEST_ASSERT_EQUAL_FLOAT(floatValue,floatRightToken, lineNo, NULL);
      }
      else{
        CUSTOM_TEST_FAIL("ERROR:Actual value for VALUE was %d",floatRightToken);
      }
    }
    else{
      CUSTOM_TEST_FAIL("ERROR:Unexpected Token type.");
    }
  }

}


void customTestAssertKey(void *key, ListElement *actual, int lineNo){

  Iterator *iter;

  if (key==NULL || actual==NULL){
    CUSTOM_TEST_FAIL("ERROR:The key or actual cannot be NULL.");
  }
  else{
    OperatorToken *opTok=((OperatorToken *)(actual->value));

    char *idenKey=((IdentifierToken *)(key))->name;
    char *leftToken=((IdentifierToken *)(opTok->token[0]))->name;

    UNITY_TEST_ASSERT_EQUAL_STRING(":", opTok->symbol, lineNo, NULL);

    //test for KEY token
    if(opTok->token[0]->type==TOKEN_IDENTIFIER_TYPE){
      if(((Token *)(key))->type==TOKEN_IDENTIFIER_TYPE){
        UNITY_TEST_ASSERT_EQUAL_STRING(idenKey,leftToken,lineNo, NULL);
      }
      else{
        CUSTOM_TEST_FAIL("ERROR:Actual value for KEY was %s",leftToken);
      }
    }
    else{
      CUSTOM_TEST_FAIL("ERROR:Unexpected Token type.");
    }
  }

}

void customTestAssertValue(void *value, ListElement *actual, int lineNo){

  Iterator *iter;

  if (value==NULL || actual==NULL){
    CUSTOM_TEST_FAIL("ERROR:The value or actual cannot be NULL.");
  }
  else{
    OperatorToken *opTok=((OperatorToken *)(actual->value));

    char *strValue=((StringToken *)(value))->name;
    int  intValue=((IntegerToken *)(value))->value;
    double  floatValue=((FloatToken *)(value))->value;

    char *charRightToken=((StringToken *)(opTok->token[1]))->name;
    int  intRightToken=((IntegerToken *)(opTok->token[1]))->value;
    double  floatRightToken=((FloatToken *)(opTok->token[1]))->value;

    iter=createIterator((LinkedList *)(opTok->token[1]));

    UNITY_TEST_ASSERT_EQUAL_STRING(":", opTok->symbol, lineNo, NULL);

    //test for VALUE token
    if(opTok->token[1]->type==TOKEN_STRING_TYPE){
      if(((Token *)(value))->type==TOKEN_STRING_TYPE){
        UNITY_TEST_ASSERT_EQUAL_STRING(strValue,charRightToken,lineNo, NULL);
      }
      else{
        CUSTOM_TEST_FAIL("ERROR:Actual value for VALUE was %s",charRightToken);
      }
    }
    else if(opTok->token[1]->type==TOKEN_INTEGER_TYPE){
      if(((Token *)(value))->type==TOKEN_INTEGER_TYPE){
        UNITY_TEST_ASSERT_EQUAL_INT(intValue,intRightToken, lineNo, NULL);
      }
      else{
        CUSTOM_TEST_FAIL("ERROR:Actual value for VALUE was %d",intRightToken);
      }
    }
    else if(opTok->token[1]->type==TOKEN_FLOAT_TYPE){
      if(((Token *)(value))->type==TOKEN_FLOAT_TYPE){
        UNITY_TEST_ASSERT_EQUAL_FLOAT(floatValue,floatRightToken, lineNo, NULL);
      }
      else{
        CUSTOM_TEST_FAIL("ERROR:Actual value for VALUE was %d",floatRightToken);
      }
    }
    else{
      CUSTOM_TEST_FAIL("ERROR:Unexpected Token type.");
    }
  }

}
