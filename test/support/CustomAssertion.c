#include "CustomAssertion.h"
#include "Token.h"
#include "JSON.h"
#include "LinkedList.h"
#include <stdio.h>


void customTestAssertTree(void *Key, void *Value, Iterator *actual, int lineNo){
  OperatorToken *OpTok=((OperatorToken *)(actual->current->value));
  
  TEST_ASSERT_EQUAL_STRING(":",OpTok->symbol);
  
  if(OpTok->token[0]->type==TOKEN_IDENTIFIER_TYPE){
    TEST_ASSERT_EQUAL_STRING((char *)(Key),((IdentifierToken *)(OpTok->token[0]))->name);
  }
  else{
    CUSTOM_TEST_FAIL("The Key must be a IDENTIFIER type");
  }
  
  if(OpTok->token[1]->type==TOKEN_STRING_TYPE){
    TEST_ASSERT_EQUAL_STRING((char *)(Value),((StringToken *)(OpTok->token[1]))->name);
  }
  else if (OpTok->token[1]->type==TOKEN_INTEGER_TYPE){
    TEST_ASSERT_EQUAL(*((int *)(Value)),((IntegerToken *)(OpTok->token[1]))->value);
  }
  else{
    CUSTOM_TEST_FAIL("Unexpected value type");
  }

}