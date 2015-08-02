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

#include <stdarg.h>
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

Token *getElementValue(ListElement *findKey){
  if(findKey==NULL){
    return NULL;
  }
  else{
    return ((OperatorToken *)(findKey->value))->token[1];
  }
}

JsonObject *createJsonObject(){
  JsonObject *jsonObj=malloc(sizeof(JsonObject));
  jsonObj->state=WAIT_FOR_TOKEN;
  return jsonObj;
}

Token *jsonParse(JsonObject *jsonObj){
  JsonToken *jsonTok=malloc(sizeof(JsonToken));
  LinkedList *list;

  JsonObject *recurJsonObj;
  Token *token,*dumpToken;
  ListElement *newNode;
  Token *leftToken,*rightToken;
  char *errMsg;

  list=createLinkedList();

  if(recur==0){
    token=getToken();
  }
  else{
    jsonObj->state=OBJECT;
    newNode=createListElement(createOperatorToken("{"));
    addLast(newNode,list);
    token=getToken();
    if(token==NULL){
      recur=0;
      jsonTok->list=list;
      return (Token *)jsonTok;
    }
  }

  do{
    switch(jsonObj->state){
      case WAIT_FOR_TOKEN :
        if(token-> type==TOKEN_OPERATOR_TYPE && strcmp(((OperatorToken *)(token))->symbol,"{")==0){
          jsonObj->state=OBJECT;
          newNode=createListElement(createOperatorToken("{"));
          addLast(newNode,list);
        }
        else{
          recur=0;
          jsonObj->state=ERROR;
          DUMP_REMAIN_TOKEN;
          if(token-> type==TOKEN_OPERATOR_TYPE){
            throwError(ERR_EXPECT_OPERATOR,"ERROR:Expected '{' but get '%s'.",((OperatorToken *)(token))->symbol);
          }
          else if(token-> type==TOKEN_IDENTIFIER_TYPE || token-> type==TOKEN_STRING_TYPE){
            throwError(ERR_EXPECT_OPERATOR,"ERROR:Expected '{' but get '%s'.",((StringToken *)(token))->name);
          }
          else if (token-> type==TOKEN_INTEGER_TYPE){
            throwError(ERR_EXPECT_OPERATOR,"ERROR:Expected '{' but get '%d'.",((IntegerToken *)(token))->value);
          }
          else{
            throwError(ERR_EXPECT_OPERATOR,"ERROR:Expected '{'.");
          }
        }break;

      case OBJECT :
        if(token->type==TOKEN_IDENTIFIER_TYPE){
          jsonObj->state=WAIT_FOR_COLON;
          leftToken=(Token *)createIdentifierToken(((IdentifierToken *)(token))->name);
        }
        else{
          recur=0;
          jsonObj->state=ERROR;
          DUMP_REMAIN_TOKEN;
          throwError(ERR_EXPECT_IDEN,"ERROR:Expected an Identifier for 'Key'.");
        }break;

      case WAIT_FOR_COLON :
        if(token->type==TOKEN_OPERATOR_TYPE && strcmp(((OperatorToken *)(token))->symbol,":")==0){
          jsonObj->state=VALUE;
        }
        else{
          jsonObj->state=ERROR;
          DUMP_REMAIN_TOKEN;
          recur=0;
          if(token-> type==TOKEN_OPERATOR_TYPE){
            throwError(ERR_EXPECT_OPERATOR,"ERROR:Expected ':' but get '%s'.",((OperatorToken *)(token))->symbol);
          }
          else if(token-> type==TOKEN_IDENTIFIER_TYPE || token-> type==TOKEN_STRING_TYPE){
            throwError(ERR_EXPECT_OPERATOR,"ERROR:Expected ':' but get '%s'.",((StringToken *)(token))->name);
          }
          else if (token-> type==TOKEN_INTEGER_TYPE){
            throwError(ERR_EXPECT_OPERATOR,"ERROR:Expected ':' but get '%d'.",((IntegerToken *)(token))->value);
          }
          else{
            throwError(ERR_EXPECT_OPERATOR,"ERROR:Expected ':'.");
          }
        }break;

      case VALUE :
        if(token->type==TOKEN_OPERATOR_TYPE){
          if(strcmp(((OperatorToken *)(token))->symbol,"{")==0){

            jsonObj->state=WAIT_FOR_OPERATOR;

            recur++;
            recurJsonObj=createJsonObject();
            token=jsonParse(recurJsonObj);
            if(recurJsonObj->state!=END){
              throwError(ERR_ACCESS_DENIED,"ERROR:ACCESS DENIED!!!The Json List is not completed.");
            }
            newNode=createListElement(link2Tokens(leftToken, ":", token));
            addLast(newNode,list);
          }
          else if(strcmp(((OperatorToken *)(token))->symbol,"[")==0){
            jsonObj->state=ARRAY;
          }
          else{
            recur=0;
            jsonObj->state=ERROR;
            DUMP_REMAIN_TOKEN;
            throwError(ERR_ILLEGAL_VALUE,"ERROR:Illegal Value.");
          }
        }
        else if(token->type==TOKEN_STRING_TYPE){
          jsonObj->state=STRING;
          rightToken=(Token *)createStringToken(((StringToken *)(token))->name);
          newNode=createListElement(link2Tokens(leftToken, ":", rightToken));
          addLast(newNode,list);
        }
        else if(token->type==TOKEN_INTEGER_TYPE || token->type==TOKEN_FLOAT_TYPE){
          jsonObj->state=NUMBER;
          rightToken=(Token *)createIntegerToken(((IntegerToken *)(token))->value);
          newNode=createListElement(link2Tokens(leftToken, ":", rightToken));
          addLast(newNode,list);
        }
        else{
          recur=0;
          jsonObj->state=ERROR;
          DUMP_REMAIN_TOKEN;
          throwError(ERR_ILLEGAL_VALUE,"ERROR:Illegal Value.");
        }break;

      case STRING :
        if(token->type==TOKEN_OPERATOR_TYPE){
          if(strcmp(((OperatorToken *)(token))->symbol,"}")==0){
            jsonObj->state=END;
            newNode=createListElement(createOperatorToken("}"));
            addLast(newNode,list);
          }
          else if(strcmp(((OperatorToken *)(token))->symbol,",")==0){
            jsonObj->state=OBJECT;
          }
          else{
            recur=0;
            jsonObj->state=ERROR;
            DUMP_REMAIN_TOKEN;
            throwError(ERR_EXPECT_OPERATOR,"ERROR:Expected Operator '}' or ',' but get '%s'.",((OperatorToken *)(token))->symbol);
          }
        }
        else{
          recur=0;
          jsonObj->state=ERROR;
          DUMP_REMAIN_TOKEN;
          if(token-> type==TOKEN_IDENTIFIER_TYPE || token-> type==TOKEN_STRING_TYPE){
            throwError(ERR_EXPECT_OPERATOR,"ERROR:Expected Operator '}' or ',' but get '%s'.",((StringToken *)(token))->name);
          }
          else if (token-> type==TOKEN_INTEGER_TYPE){
            throwError(ERR_EXPECT_OPERATOR,"ERROR:Expected Operator '}' or ',' but get '%d'.",((IntegerToken *)(token))->value);
          }
          else{
            throwError(ERR_EXPECT_OPERATOR,"ERROR:Expected an Operator.");
          }
        }break;

      case NUMBER :
        if(token->type==TOKEN_OPERATOR_TYPE ){
          if(strcmp(((OperatorToken *)(token))->symbol,"}")==0){
            jsonObj->state=END;
            newNode=createListElement(createOperatorToken("}"));
            addLast(newNode,list);
          }
          else if(strcmp(((OperatorToken *)(token))->symbol,",")==0){
            jsonObj->state=OBJECT;
          }
          else{
            recur=0;
            jsonObj->state=ERROR;
            DUMP_REMAIN_TOKEN;
            throwError(ERR_EXPECT_OPERATOR,"ERROR:Expected Operator '}' or ',' but get '%s'.",((OperatorToken *)(token))->symbol);
          }
        }
        else{
          recur=0;
          jsonObj->state=ERROR;
          DUMP_REMAIN_TOKEN;
          if(token-> type==TOKEN_IDENTIFIER_TYPE || token-> type==TOKEN_STRING_TYPE){
            throwError(ERR_EXPECT_OPERATOR,"ERROR:Expected Operator '}' or ',' but get '%s'.",((StringToken *)(token))->name);
          }
          else if (token-> type==TOKEN_INTEGER_TYPE){
            throwError(ERR_EXPECT_OPERATOR,"ERROR:Expected Operator '}' or ',' but get '%d'.",((IntegerToken *)(token))->value);
          }
          else{
            throwError(ERR_EXPECT_OPERATOR,"ERROR:Expected an Operator.");
          }
        }break;

      case WAIT_FOR_OPERATOR :
        if(token->type==TOKEN_OPERATOR_TYPE ){
          if(strcmp(((OperatorToken *)(token))->symbol,"}")==0){
            jsonObj->state=END;
            newNode=createListElement(createOperatorToken("}"));
            addLast(newNode,list);
          }
          else if(strcmp(((OperatorToken *)(token))->symbol,",")==0){
            jsonObj->state=OBJECT;
          }
          else{
            recur=0;
            jsonObj->state=ERROR;
            DUMP_REMAIN_TOKEN;
            throwError(ERR_EXPECT_OPERATOR,"ERROR:Expected Operator '}' or ','.");
          }
        }
        else{
          recur=0;
          jsonObj->state=ERROR;
          DUMP_REMAIN_TOKEN;
          if(token-> type==TOKEN_OPERATOR_TYPE){
            throwError(ERR_EXPECT_OPERATOR,"ERROR:Expected Operator '}' or ',' but get '%s'.",((OperatorToken *)(token))->symbol);
          }
          else if(token-> type==TOKEN_IDENTIFIER_TYPE || token-> type==TOKEN_STRING_TYPE){
            throwError(ERR_EXPECT_OPERATOR,"ERROR:Expected Operator '}' or ',' but get '%s'.",((StringToken *)(token))->name);
          }
          else if (token-> type==TOKEN_INTEGER_TYPE){
            throwError(ERR_EXPECT_OPERATOR,"ERROR:Expected Operator '}' or ',' but get '%d'.",((IntegerToken *)(token))->value);
          }
          else{
            throwError(ERR_EXPECT_OPERATOR,"ERROR:Expected Operator '}' or ','.");
          }
        }break;

      case END :
        recur=0;
        jsonObj->state=ERROR;
        DUMP_REMAIN_TOKEN;
        throwError(ERR_ACCESS_DENIED,"ERROR:ACCESS DENIED!!!The Json List already completed.");break;

      default:
        recur=0;
        jsonObj->state=ERROR;
        DUMP_REMAIN_TOKEN;
        throwError(ERR_ILLEGAL_VALUE,"ERROR:Unknown Error");
    }

    token=getToken();
    if(token!=NULL){
      if(recur!=0 && token->type==TOKEN_OPERATOR_TYPE){
        if(strcmp(((OperatorToken *)(token))->symbol,"}")==0){
          if(jsonObj->state==STRING || jsonObj->state==NUMBER || jsonObj->state==WAIT_FOR_OPERATOR){
            jsonObj->state=END;
            newNode=createListElement(createOperatorToken("}"));
            addLast(newNode,list);
            recur--;
            break;
          }
          else{
            recur=0;
            jsonObj->state=ERROR;
            DUMP_REMAIN_TOKEN;
            throwError(ERR_ILLEGAL_VALUE,"ERROR:Illegal Value.");
          }
        }
        else{}
      }
    }
    else{
      break;
    }
  }while(token!=NULL);

  if(jsonObj->state!=END){
    recur=0;
    throwError(ERR_ACCESS_DENIED,"ERROR:ACCESS DENIED!!!The Json List is not completed.");
  }
  else{
    jsonTok->list=list;
    return (Token *)jsonTok;
  }
}





