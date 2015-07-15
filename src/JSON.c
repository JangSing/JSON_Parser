#include "Token.h"
#include "LinkedList.h"
#include "JSON.h"
#include "IteratorFunction.h"

#include <malloc.h>
#include <stdio.h>
#include <assert.h>
#include <ctype.h>

int recur=0;

Token *createOperatorToken(char *symbol) {

    operatorToken *opTok =malloc(sizeof(operatorToken)+sizeof(Token *)*2);

    opTok->type=TOKEN_OPERATOR_TYPE;
    opTok->symbol=symbol;
    opTok->token[0]=NULL;
    opTok->token[1]=NULL;

  return (Token *)opTok;
}

IdentifierToken *createIdentifierToken(char *key){

    IdentifierToken *IdenTok =malloc(sizeof(IdentifierToken));

    IdenTok->type=TOKEN_IDENTIFIER_TYPE;
    IdenTok->name =key;

  return IdenTok;
}

IntegerToken *createIntegerToken(int value){

    IntegerToken *intTok =malloc(sizeof(IntegerToken));

    intTok->type=TOKEN_INTEGER_TYPE;
    intTok->value=value;

  return intTok;
}

StringToken *createStringToken(char *value){

    StringToken *StrTok =malloc(sizeof(StringToken));

    StrTok->type=TOKEN_STRING_TYPE;
    StrTok->name=value;

  return StrTok;
}

Token *link2Tokens(Token *leftValue, char *operatorSymbol, Token *rightValue){

  operatorToken *opTok;

  opTok=(operatorToken *)createOperatorToken(operatorSymbol);

  opTok->token[0]=leftValue;
  opTok->token[1]=rightValue;

  return (Token *)opTok;
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
        if(token-> type==TOKEN_OPERATOR_TYPE && strcmp(((operatorToken *)(token))->symbol,"{")==0){
          list->state=OBJECT;
          newNode=createListElement(createOperatorToken("{"));
          addLast(newNode,list);
        }
        else{
          list->state=ERROR;
        }break;

      case OBJECT :
        if(token->type==TOKEN_IDENTIFIER_TYPE){
          list->state=WAIT_FOR_COLON;
          leftToken=(Token *)createIdentifierToken(((IdentifierToken *)(token))->name);
        }
        else{
          list->state=ERROR;
        }break;

      case WAIT_FOR_COLON :
        if(token->type==TOKEN_OPERATOR_TYPE && strcmp(((operatorToken *)(token))->symbol,":")==0){
          list->state=value;
        }
        else{
          list->state=ERROR;
        }break;

      case value :
        if(token->type==TOKEN_OPERATOR_TYPE){
          if(strcmp(((operatorToken *)(token))->symbol,"{")==0){
            LinkedList *recurList=malloc(sizeof(LinkedList));
            list->state=WAIT_FOR_OPERATOR;
            recur=1;

            recurList=jsonParse();

            if(recurList->state==ERROR || recurList->state!=END){
              list->state=ERROR;
              return list;
            }
            newNode=createListElement(link2Tokens(leftToken, ":", (Token *)(recurList)));
            addLast(newNode,list);
          }
          else if(strcmp(((operatorToken *)(token))->symbol,"[")==0){
            list->state=ARRAY;
          }
          else{
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
          list->state=ERROR;
        }break;

      case STRING :
        if(token->type==TOKEN_OPERATOR_TYPE ){
          if(strcmp(((operatorToken *)(token))->symbol,"}")==0){
            list->state=END;
            newNode=createListElement(createOperatorToken("}"));
            addLast(newNode,list);
          }
          else if(strcmp(((operatorToken *)(token))->symbol,",")==0){
            list->state=OBJECT;
          }
          else{
            list->state=ERROR;
          }
        }
        else{
          list->state=ERROR;
        }break;

      case NUMBER :
        if(token->type==TOKEN_OPERATOR_TYPE ){
          if(strcmp(((operatorToken *)(token))->symbol,"}")==0){
            list->state=END;
            newNode=createListElement(createOperatorToken("}"));
            addLast(newNode,list);
          }
          else if(strcmp(((operatorToken *)(token))->symbol,",")==0){
            list->state=OBJECT;
          }
          else{
            list->state=ERROR;
          }
        }
        else{
          list->state=ERROR;
        }break;

      case WAIT_FOR_OPERATOR :
        if(token->type==TOKEN_OPERATOR_TYPE ){
          if(strcmp(((operatorToken *)(token))->symbol,"}")==0){
            list->state=END;
            newNode=createListElement(createOperatorToken("}"));
            addLast(newNode,list);
          }
          else if(strcmp(((operatorToken *)(token))->symbol,",")==0){
            list->state=OBJECT;
          }
          else{
            list->state=ERROR;
          }
        }
        else{
          list->state=ERROR;
        }break;

      case ERROR :
        return list;

      default:list->state=ERROR;
    }

    token=getToken();

    if(recur==1 && token->type==TOKEN_OPERATOR_TYPE){
      if(strcmp(((operatorToken *)(token))->symbol,"}")==0){
        list->state=END;
        newNode=createListElement(createOperatorToken("}"));
        addLast(newNode,list);
        recur=0;
        break;
      }
    }

  }while(token!=NULL);

  return list;
}

Token *getElementValue(ListElement *findKey){
  return ((operatorToken *)(findKey->value))->token[1];
}

