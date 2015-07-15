#include "CustomAssertion.h"
#include "Token.h"
#include "JSON.h"
#include "LinkedList.h"
#include "IteratorFunction.h"

#include <stdio.h>

void customTestAssertKeyValue(void *key, void *value, ListElement *actual, int lineNo){

  if (key==NULL || value==NULL || actual==NULL){
    CUSTOM_TEST_FAIL("ERROR:There are no key or value or actual to be tested");
  }
  else{
    OperatorToken *opTok=((OperatorToken *)(actual->value));

    char *idenKey=((IdentifierToken *)(key))->name;
    char *strValue=((StringToken *)(value))->name;
    int  intValue=((IntegerToken *)(value))->value;

    char *leftToken=((IdentifierToken *)(opTok->token[0]))->name;
    char *charRightToken=((StringToken *)(opTok->token[1]))->name;
    int  intRightToken=((IntegerToken *)(opTok->token[1]))->value;


    UNITY_TEST_ASSERT_EQUAL_STRING(":", opTok->symbol, lineNo, NULL);


    //test for KEY token
    if(opTok->token[0]->type==TOKEN_IDENTIFIER_TYPE){
      UNITY_TEST_ASSERT_EQUAL_STRING(idenKey,leftToken,lineNo, NULL);
    }
    else{
      CUSTOM_TEST_FAIL("ERROR:The Key must be an Identifier");
    }

    //test for VALUE token
    if(opTok->token[1]->type==TOKEN_STRING_TYPE){
      UNITY_TEST_ASSERT_EQUAL_STRING(strValue,charRightToken,lineNo, NULL);
    }
    else if(opTok->token[1]->type==TOKEN_INTEGER_TYPE){
      UNITY_TEST_ASSERT_EQUAL_INT(intValue,intRightToken, lineNo, NULL);
    }
    else{
      CUSTOM_TEST_FAIL("ERROR:Unexpected value type");
    }
  }

}