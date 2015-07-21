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
#include <ctype.h>

int recur=0;

Token *link2Tokens(Token *leftValue, char *operatorSymbol, Token *rightValue){
  if( leftValue==NULL || operatorSymbol==NULL || rightValue==NULL){
    return NULL;
  }
  else{
    OperatorToken *opTok;

    opTok=(OperatorToken *)createOperatorToken(operatorSymbol);

    opTok->token[0]=leftValue;
    opTok->token[1]=rightValue;

    return (Token *)opTok;
  }
}

JsonObject *createJsonObject(){
}

Token *getElementValue(ListElement *findKey){
  if(findKey==NULL){
    return NULL;
  }
  else{
    return ((OperatorToken *)(findKey->value))->token[1];
  }
}

LinkedList *jsonParse(){

  Token *token;
  ListElement *newNode;
  Token *leftToken,*rightToken;

  LinkedList *list=malloc(sizeof(LinkedList));

  list=createLinkedList();

  if(recur==0){
    token=getToken();
  }
  else{
    list->state=OBJECT;
    newNode=createListElement(createOperatorToken("{"));
    addLast(newNode,list);
    token=getToken();
  }

  do{
    switch(list->state){
      case WAIT_FOR_TOKEN :
        if(token-> type==TOKEN_OPERATOR_TYPE && strcmp(((OperatorToken *)(token))->symbol,"{")==0){
          list->state=OBJECT;
          newNode=createListElement(createOperatorToken("{"));
          addLast(newNode,list);
        }
        else{
          ThrowError("ERROR:Expected Open Brace",ERR_EXPECT_OPERATOR);
          list->state=ERROR;
        }break;

      case OBJECT :
        if(token->type==TOKEN_IDENTIFIER_TYPE){
          list->state=WAIT_FOR_COLON;
          leftToken=(Token *)createIdentifierToken(((IdentifierToken *)(token))->name);
        }
        else{
          ThrowError("ERROR:Expected Identifier",ERR_EXPECT_IDEN);
          list->state=ERROR;
        }break;

      case WAIT_FOR_COLON :
        if(token->type==TOKEN_OPERATOR_TYPE && strcmp(((OperatorToken *)(token))->symbol,":")==0){
          list->state=value;
        }
        else{
          ThrowError("ERROR:Expected colon",ERR_EXPECT_COLON);
          list->state=ERROR;
        }break;

      case value :
        if(token->type==TOKEN_OPERATOR_TYPE){
          if(strcmp(((OperatorToken *)(token))->symbol,"{")==0){
            LinkedList *recurList=malloc(sizeof(LinkedList));
            list->state=WAIT_FOR_OPERATOR;
            recur=1;

            recurList=jsonParse();

            if(recurList->state==ERROR || recurList->state!=END){
              ThrowError("ERROR:Illegal Value",ERR_ILLEGAL_VALUE);
              list->state=ERROR;
              return list;
            }
            newNode=createListElement(link2Tokens(leftToken, ":", (Token *)(recurList)));
            addLast(newNode,list);
          }
          else if(strcmp(((OperatorToken *)(token))->symbol,"[")==0){
            list->state=ARRAY;
          }
          else{
            ThrowError("ERROR:Illegal Value",ERR_ILLEGAL_VALUE);
            list->state=ERROR;
          }
        }
        else if(token->type==TOKEN_STRING_TYPE){
          list->state=STRING;
          rightToken=(Token *)createStringToken(((StringToken *)(token))->name);
          newNode=createListElement(link2Tokens(leftToken, ":", rightToken));
          addLast(newNode,list);
        }
        else if(token->type==TOKEN_INTEGER_TYPE || token->type==TOKEN_FLOAT_TYPE){
          list->state=NUMBER;
          rightToken=(Token *)createIntegerToken(((IntegerToken *)(token))->value);
          newNode=createListElement(link2Tokens(leftToken, ":", rightToken));
          addLast(newNode,list);
        }
        else{
          ThrowError("ERROR:Illegal Value",ERR_ILLEGAL_VALUE);
          list->state=ERROR;
        }break;

      case STRING :
        if(token->type==TOKEN_OPERATOR_TYPE){
          if(strcmp(((OperatorToken *)(token))->symbol,"}")==0){
            list->state=END;
            newNode=createListElement(createOperatorToken("}"));
            addLast(newNode,list);
          }
          else if(strcmp(((OperatorToken *)(token))->symbol,",")==0){
            list->state=OBJECT;
          }
          else{
            ThrowError("ERROR:Expected operator '}' or ','",ERR_EXPECT_OPERATOR);
            list->state=ERROR;
          }
        }
        else{
          ThrowError("ERROR:Expected operator '}' or ','",ERR_EXPECT_OPERATOR);
          list->state=ERROR;
        }break;

      case NUMBER :
        if(token->type==TOKEN_OPERATOR_TYPE ){
          if(strcmp(((OperatorToken *)(token))->symbol,"}")==0){
            list->state=END;
            newNode=createListElement(createOperatorToken("}"));
            addLast(newNode,list);
          }
          else if(strcmp(((OperatorToken *)(token))->symbol,",")==0){
            list->state=OBJECT;
          }
          else{
            ThrowError("ERROR:Expected operator '}' or ','",ERR_EXPECT_OPERATOR);
            list->state=ERROR;
          }
        }
        else{
          ThrowError("ERROR:Expected operator '}' or ','",ERR_EXPECT_OPERATOR);
          list->state=ERROR;
        }break;

      case WAIT_FOR_OPERATOR :
        if(token->type==TOKEN_OPERATOR_TYPE ){
          if(strcmp(((OperatorToken *)(token))->symbol,"}")==0){
            list->state=END;
            newNode=createListElement(createOperatorToken("}"));
            addLast(newNode,list);
          }
          else if(strcmp(((OperatorToken *)(token))->symbol,",")==0){
            list->state=OBJECT;
          }
          else{
            ThrowError("ERROR:Expected operator '}' or ','",ERR_EXPECT_OPERATOR);
            list->state=ERROR;
          }
        }
        else{
          ThrowError("ERROR:Expected operator '}' or ','",ERR_EXPECT_OPERATOR);
          list->state=ERROR;
        }break;

      case ERROR :
        ThrowError("ERROR:Unknown Error",ERR_ILLEGAL_VALUE);
        return list;

      default:
        ThrowError("ERROR:Unknown Error",ERR_ILLEGAL_VALUE);
        list->state=ERROR;
    }

    token=getToken();

    if(recur==1 && token->type==TOKEN_OPERATOR_TYPE){
      if(strcmp(((OperatorToken *)(token))->symbol,"}")==0){
        if(list->state==STRING || list->state==NUMBER){
          list->state=END;
          newNode=createListElement(createOperatorToken("}"));
          addLast(newNode,list);
          recur=0;
          break;
        }
        else{
          ThrowError("ERROR:Illegal Value",ERR_ILLEGAL_VALUE);
          list->state=ERROR;
        }
      }
    }

  }while(token!=NULL);

  return list;
}


