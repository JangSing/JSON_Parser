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
  LinkedList *list=malloc(sizeof(LinkedList));

  Token *token;
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
          jsonObj->state=ERROR;
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
          jsonObj->state=ERROR;
          throwError(ERR_EXPECT_IDEN,"ERROR:Expected an Identifier for 'Key'");
        }break;

      case WAIT_FOR_COLON :
        if(token->type==TOKEN_OPERATOR_TYPE && strcmp(((OperatorToken *)(token))->symbol,":")==0){
          jsonObj->state=VALUE;
        }
        else{
          jsonObj->state=ERROR;
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
            JsonObject *recurJsonObj;
            jsonObj->state=WAIT_FOR_OPERATOR;

            recur=1;
            recurJsonObj=createJsonObject();

            token=jsonParse(recurJsonObj);
            newNode=createListElement(link2Tokens(leftToken, ":", token));
            addLast(newNode,list);
          }
          else if(strcmp(((OperatorToken *)(token))->symbol,"[")==0){
            jsonObj->state=ARRAY;
          }
          else{
            jsonObj->state=ERROR;
            throwError(ERR_ILLEGAL_VALUE,"ERROR:Illegal Value type.");
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
          jsonObj->state=ERROR;
          throwError(ERR_ILLEGAL_VALUE,"ERROR:Illegal Value type.");
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
            jsonObj->state=ERROR;
            throwError(ERR_EXPECT_OPERATOR,"ERROR:Expected Operator '}' or ','.");
          }
        }
        else{
          jsonObj->state=ERROR;
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
            jsonObj->state=ERROR;
            throwError(ERR_EXPECT_OPERATOR,"ERROR:Expected Operator '}' or ','.");
          }
        }
        else{
          jsonObj->state=ERROR;
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
            jsonObj->state=ERROR;
            throwError(ERR_EXPECT_OPERATOR,"ERROR:Expected Operator '}' or ','.");
          }
        }
        else{
          jsonObj->state=ERROR;
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
        throwError(ERR_ACCESS_DENIED,"ERROR:ACCESS DENIED!!!The Json List already completed.");break;

      default:
        jsonObj->state=ERROR;
        throwError(ERR_ILLEGAL_VALUE,"ERROR:Unknown Error");
    }

    token=getToken();

    if(recur==1 && token->type==TOKEN_OPERATOR_TYPE){
      if(strcmp(((OperatorToken *)(token))->symbol,"}")==0){
        if(jsonObj->state==STRING || jsonObj->state==NUMBER){
          jsonObj->state=END;
          newNode=createListElement(createOperatorToken("}"));
          addLast(newNode,list);
          recur=0;
          break;
        }
        else{
          jsonObj->state=ERROR;
          throwError(ERR_ILLEGAL_VALUE,"ERROR:Illegal Value type.");
        }
      }
    }

  }while(token!=NULL);

  if(jsonObj->state!=END){
    throwError(ERR_ACCESS_DENIED,"ERROR:ACCESS DENIED!!!The Json List is not completed.Expected '}'.");
  }
  else{
    jsonTok->list=list;
    return (Token *)jsonTok;
  }
}





