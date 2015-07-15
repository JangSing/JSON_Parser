#include "CustomAssertion.h"
#include "Token.h"
#include "JSON.h"
#include "LinkedList.h"
#include "IteratorFunction.h"

#include <stdio.h>

void customTestAssertTree(void *key, void *value, Iterator *actual, int lineNo){
  operatorToken *opTok=((operatorToken *)(actual->current->value));

  TEST_ASSERT_EQUAL_STRING(":",opTok->symbol);

  if(opTok->token[0]->type==TOKEN_IDENTIFIER_TYPE){
    TEST_ASSERT_EQUAL_STRING((char *)(key),((IdentifierToken *)(opTok->token[0]))->name);
  }
  else{
    CUSTOM_TEST_FAIL("The key must be a IDENTIFIER type");
  }

  if(opTok->token[1]->type==TOKEN_STRING_TYPE){
    TEST_ASSERT_EQUAL_STRING((char *)(value),((StringToken *)(opTok->token[1]))->name);
  }
  else if (opTok->token[1]->type==TOKEN_INTEGER_TYPE){
    TEST_ASSERT_EQUAL(*((int *)(value)),((IntegerToken *)(opTok->token[1]))->value);
  }
  else{
    CUSTOM_TEST_FAIL("Unexpected value type");
  }

}