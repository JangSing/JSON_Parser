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

#include <malloc.h>
#include <stdio.h>
#include <assert.h>

ListElement *keyFind(LinkedList *list, void *key, int(*compare)(void *,void *)){
  char *errMsg;

  if(list==NULL || compare==NULL){
    return NULL;
  }
  else{
    ListElement *elemPtr;
    elemPtr=list->head;

    if(key==NULL || (compare(elemPtr ->value , key)==-1)){
      return NULL;
    }

    else{
      elemPtr=elemPtr->next;
      //if they are not the same then continue looping
      while (compare(((IdentifierToken *)(((OperatorToken *)(elemPtr ->value))->token[0]))->name , key)==1){
        elemPtr =elemPtr->next;
        if (((Token *)(elemPtr->value))->type==TOKEN_OPERATOR_TYPE && strcmp(((OperatorToken *)(elemPtr->value))->symbol,"}")==0){
          errMsg="ERROR[%d]:Key not Found.Finding 'Key'=>'%s'.";
          printf(errMsg,ERR_KEY_NOT_FOUND,(char *)(key));
          throwError(ERR_KEY_NOT_FOUND,errMsg,ERR_KEY_NOT_FOUND,(char *)(key));
        }
      }
      printf("Finding 'Value' for 'Key'='%s'\n",(char *)(key));
      return elemPtr;
    }
  }
}

Token *getElementValue(ListElement *findKey){
  Token *leftToken=((OperatorToken *)(findKey->value))->token[0];
  Token *rightToken=((OperatorToken *)(findKey->value))->token[1];

  if(findKey==NULL){
    return NULL;
  }
  else{
    if(rightToken->type==TOKEN_STRING_TYPE){
      printf("The 'Value' for '%s' is '%s'\n",((IdentifierToken *)leftToken)->name,((StringToken *)rightToken)->name);
    }
    else if(rightToken->type==TOKEN_INTEGER_TYPE){
      printf("The 'Value' for '%s' is '%d'\n",((IdentifierToken *)leftToken)->name,((IntegerToken *)rightToken)->value);
    }
    return rightToken;
  }
}

