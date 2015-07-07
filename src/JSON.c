#include "Token.h"
#include "LinkedList.h"
#include "JSON.h"

#include <malloc.h>
#include <stdio.h>
#include <assert.h>
#include <ctype.h>

int Recur=0;

Token *createOperatorToken(char *symbol) {

    OperatorToken *opTok =malloc(sizeof(OperatorToken)+sizeof(Token *)*2);

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

    IntegerToken *IntTok =malloc(sizeof(IntegerToken));

    IntTok->type=TOKEN_INTEGER_TYPE;
    IntTok->value=value;

  return IntTok;
}
StringToken *createStringToken(char *value){

    StringToken *StrTok =malloc(sizeof(StringToken));

    StrTok->type=TOKEN_STRING_TYPE;
    StrTok->name=value;

  return StrTok;
}
Token *Link2Tokens(Token *leftValue, char *operatorSymbol, Token *rightValue){

  OperatorToken *opTok;

  opTok=(OperatorToken *)createOperatorToken(operatorSymbol);

  opTok->token[0]=leftValue;
  opTok->token[1]=rightValue;

  return (Token *)opTok;
}

LinkedList *DetermineState(){

  Token *token;
  ListElement *NewNode;
  Token *leftToken,*rightToken;

  LinkedList *List=malloc(sizeof(LinkedList));

  List=createLinkedList();

  if(Recur==0){
    token=getToken();
  }
  else{
    List->state=OBJECT;
    NewNode=createListElement(createOperatorToken("{"));
    AddLast(NewNode,List);
    token=getToken();
  }

  do{

    switch(List->state){
      case WAIT_FOR_TOKEN :
        if(token-> type==TOKEN_OPERATOR_TYPE && strcmp(((OperatorToken *)(token))->symbol,"{")==0){
          List->state=OBJECT;
          NewNode=createListElement(createOperatorToken("{"));
          AddLast(NewNode,List);
        }
        else{
          List->state=ERROR;
        }break;

      case OBJECT :
        if(token->type==TOKEN_IDENTIFIER_TYPE){
          List->state=WAIT_FOR_COLON;
          leftToken=(Token *)createIdentifierToken(((IdentifierToken *)(token))->name);
        }
        else{
          List->state=ERROR;
        }break;

      case WAIT_FOR_COLON :
        if(token->type==TOKEN_OPERATOR_TYPE && strcmp(((OperatorToken *)(token))->symbol,":")==0){
          List->state=VALUE;
        }
        else{
          List->state=ERROR;
        }break;

      case VALUE :
        if(token->type==TOKEN_OPERATOR_TYPE){
          if(strcmp(((OperatorToken *)(token))->symbol,"{")==0){
            LinkedList *RecurList=malloc(sizeof(LinkedList));
            List->state=WAIT_FOR_OPERATOR;
            Recur=1;

            RecurList=DetermineState();

            if(RecurList->state==ERROR || RecurList->state!=END){
              List->state=ERROR;
              return List;
            }

            NewNode=createListElement(Link2Tokens(leftToken, ":", (Token *)(RecurList)));
            AddLast(NewNode,List);

          }
          else if(strcmp(((OperatorToken *)(token))->symbol,"[")==0){
            List->state=ARRAY;
          }
          else{
            List->state=ERROR;
          }
        }
        else if(token->type==TOKEN_STRING_TYPE){
          List->state=STRING;
          rightToken=(Token *)createIdentifierToken(((StringToken *)(token))->name);
          NewNode=createListElement(Link2Tokens(leftToken, ":", rightToken));
          AddLast(NewNode,List);
        }
        else if(token->type==TOKEN_INTEGER_TYPE || token->type==TOKEN_FLOAT_TYPE){
          List->state=NUMBER;
          rightToken=(Token *)createIntegerToken(((IntegerToken *)(token))->value);
          NewNode=createListElement(Link2Tokens(leftToken, ":", rightToken));
          AddLast(NewNode,List);

        }
        else{
          List->state=ERROR;
        }break;

      case STRING :
        if(token->type==TOKEN_OPERATOR_TYPE ){
          if(strcmp(((OperatorToken *)(token))->symbol,"}")==0){
            List->state=END;
            NewNode=createListElement(createOperatorToken("}"));
            AddLast(NewNode,List);

          }
          else if(strcmp(((OperatorToken *)(token))->symbol,",")==0){
            List->state=OBJECT;
            NewNode=createListElement(createOperatorToken(","));
            AddLast(NewNode,List);
          }
          else{
            List->state=ERROR;
          }
        }
        else{
          List->state=ERROR;

        }break;

      case NUMBER :
        if(token->type==TOKEN_OPERATOR_TYPE ){
          if(strcmp(((OperatorToken *)(token))->symbol,"}")==0){
            List->state=END;
            NewNode=createListElement(createOperatorToken("}"));
            AddLast(NewNode,List);
          }
          else if(strcmp(((OperatorToken *)(token))->symbol,",")==0){
            List->state=OBJECT;
            NewNode=createListElement(createOperatorToken(","));
            AddLast(NewNode,List);
          }
          else{
            List->state=ERROR;
          }
        }
        else{
          List->state=ERROR;
        }break;

      case WAIT_FOR_OPERATOR :
        if(token->type==TOKEN_OPERATOR_TYPE ){
          if(strcmp(((OperatorToken *)(token))->symbol,"}")==0){
            List->state=END;
            NewNode=createListElement(createOperatorToken("}"));
            AddLast(NewNode,List);
          }
          else if(strcmp(((OperatorToken *)(token))->symbol,",")==0){
            List->state=OBJECT;
            NewNode=createListElement(createOperatorToken(","));
            AddLast(NewNode,List);
          }
          else{
            List->state=ERROR;
          }
        }
        else{
          List->state=ERROR;
        }break;
    }

    token=getToken();

    if(Recur==1 && token->type==TOKEN_OPERATOR_TYPE){
      if(strcmp(((OperatorToken *)(token))->symbol,"}")==0){
        List->state=END;
        NewNode=createListElement(createOperatorToken("}"));
        AddLast(NewNode,List);
        Recur=0;
        break;
      }
    }

  }while(token!=NULL);

  return List;
}

Token *getElementValue(ListElement *FindKey){
  return ((OperatorToken *)(FindKey->value))->token[1];
}

