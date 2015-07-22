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
  char *errMsg;

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
          list->state=ERROR;
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
          list->state=WAIT_FOR_COLON;
          leftToken=(Token *)createIdentifierToken(((IdentifierToken *)(token))->name);
        }
        else{
          list->state=ERROR;
          throwError(ERR_EXPECT_IDEN,"ERROR:Expected an Identifier for 'Key'");
        }break;

      case WAIT_FOR_COLON :
        if(token->type==TOKEN_OPERATOR_TYPE && strcmp(((OperatorToken *)(token))->symbol,":")==0){
          list->state=VALUE;
        }
        else{
          list->state=ERROR;
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
            LinkedList *recurList=malloc(sizeof(LinkedList));
            list->state=WAIT_FOR_OPERATOR;
            recur=1;

            recurList=jsonParse();

            newNode=createListElement(link2Tokens(leftToken, ":", (Token *)(recurList)));
            addLast(newNode,list);
          }
          else if(strcmp(((OperatorToken *)(token))->symbol,"[")==0){
            list->state=ARRAY;
          }
          else{
            list->state=ERROR;
            throwError(ERR_ILLEGAL_VALUE,"ERROR:Illegal Value type.");
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
          list->state=ERROR;
          throwError(ERR_ILLEGAL_VALUE,"ERROR:Illegal Value type.");
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
            list->state=ERROR;
            throwError(ERR_EXPECT_OPERATOR,"ERROR:Expected Operator '}' or ','.");
          }
        }
        else{
          list->state=ERROR;
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
            list->state=END;
            newNode=createListElement(createOperatorToken("}"));
            addLast(newNode,list);
          }
          else if(strcmp(((OperatorToken *)(token))->symbol,",")==0){
            list->state=OBJECT;
          }
          else{
            list->state=ERROR;
            throwError(ERR_EXPECT_OPERATOR,"ERROR:Expected Operator '}' or ','.");
          }
        }
        else{
          list->state=ERROR;
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
            list->state=END;
            newNode=createListElement(createOperatorToken("}"));
            addLast(newNode,list);
          }
          else if(strcmp(((OperatorToken *)(token))->symbol,",")==0){
            list->state=OBJECT;
          }
          else{
            list->state=ERROR;
            throwError(ERR_EXPECT_OPERATOR,"ERROR:Expected Operator '}' or ','.");
          }
        }
        else{
          list->state=ERROR;
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
        list->state=ERROR;
        throwError(ERR_ILLEGAL_VALUE,"ERROR:Unknown Error");
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
          list->state=ERROR;
          throwError(ERR_ILLEGAL_VALUE,"ERROR:Illegal Value type.");
        }
      }
    }

  }while(token!=NULL);

  if(list->state!=END){
    throwError(ERR_ACCESS_DENIED,"ERROR:ACCESS DENIED!!!The Json List is not completed.Expected '}'.");
  }
  else{
    return list;
  }
}


