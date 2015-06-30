#include "Token.h"
#include "LinkedList.h"
#include "JSON.h"

#include <malloc.h>
#include <stdio.h>
#include <assert.h>
#include <ctype.h>

Token *createOperatorToken(char *symbol) {

    OperatorToken *opTok =malloc(sizeof(OperatorToken)+sizeof(Token *)*2);

    opTok->type=TOKEN_OPERATOR_TYPE;
    opTok->symbol=symbol;

  return (Token *)opTok;
}

IntegerToken *createIntegerToken(int value){

    IntegerToken *IntTok =malloc(sizeof(IntegerToken));

    IntTok->type=TOKEN_INTEGER_TYPE;
    IntTok->value=value;

  return IntTok;
}

IdentifierToken *createIdentifierToken(char *key){

    IdentifierToken *IdenTok =malloc(sizeof(IdentifierToken));

    IdenTok->type=TOKEN_INTEGER_TYPE;
    IdenTok->name =key;

  return IdenTok;
}


Token *Link2Tokens(Token *leftValue, char *operatorSymbol, Token *rightValue){

  OperatorToken *opTok;

  opTok=(OperatorToken *)createOperatorToken(operatorSymbol);

  opTok->token[0]=leftValue;
  opTok->token[1]=rightValue;

  return (Token *)opTok;
}

LinkedList *DetermineState(){

  int i;
  Token *token;
  ListElement *NewNode;
  Token *tempToken;
  LinkedList *List=malloc(sizeof(LinkedList));

  List=createLinkedList();

  token=getToken();
  do{

    switch(List->state){
      case WAIT_FOR_TOKEN :
        if(token-> type=TOKEN_OPERATOR_TYPE && strcmp(((OperatorToken *)(token))->symbol,"{")==0){
          List->state=OBJECT;
          NewNode=createListElement(createOperatorToken("{"));
          AddLast(NewNode,List);
          // printf("List->head=%d\n",List->head);
          // printf("NewNode=%d\n",NewNode);
          // printf("((OperatorToken *)(NewNode->value))->symbol=%s\n",((OperatorToken *)(NewNode->value))->symbol);
          // printf("((OperatorToken *)(NewNode->value))->type=%d\n",((OperatorToken *)(NewNode->value))->type);
        }
        else{
          List->state=ERROR;
        }break;

      case OBJECT :
        if(token->type==TOKEN_IDENTIFIER_TYPE){
          List->state=WAIT_FOR_COLON;
          tempToken=(Token *)createIdentifierToken(((IdentifierToken *)(token))->name);
        }
        else{
          List->state=ERROR;
        }break;

      case WAIT_FOR_COLON :
        if(token->type==TOKEN_OPERATOR_TYPE && strcmp(((OperatorToken *)(token))->symbol,":")==0){
          List->state=VALUE;
          NewNode=createListElement(Link2Tokens(tempToken, ":", NULL));
          AddLast(NewNode,List);
          // printf("List->head->next=%d\n",List->head->next);
          // printf("NewNode=%d\n",NewNode);
          // printf("symbol=%s\n",((OperatorToken *)(NewNode->value))->symbol);
          // printf("token[0]=%s\n",((IdentifierToken *)(((OperatorToken *)(NewNode->value))->token[0]))->name);
          // printf("token[1]=%d\n",((OperatorToken *)(NewNode->value))->token[1]);
          // printf("List->head->next->value->token[0]=%s\n",((IdentifierToken *)(((OperatorToken *)(List->head->next->value))->token[0]))->name);

        }
        else{
          List->state=ERROR;
        }break;

      case VALUE :
        if(token->type==TOKEN_OPERATOR_TYPE){
          if(strcmp(((OperatorToken *)(token))->symbol,"{")==0){
            List->state=OBJECT;
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
          tempToken=(Token *)createIdentifierToken(((StringToken *)(token))->name);
          ((Token *)((StringToken *)(((OperatorToken *)(List->head->next->value))->token[1])))=tempToken;
          printf("List->head->next=%d\n",List->head->next);
          printf("NewNode=%d\n",NewNode);
          printf("symbol=%s\n",((OperatorToken *)(NewNode->value))->symbol);
          printf("token[0]=%s\n",((IdentifierToken *)(((OperatorToken *)(NewNode->value))->token[0]))->name);
          printf("token[1]=%d\n",((OperatorToken *)(NewNode->value))->token[1]);
          printf("List->head->next->value->token[0]=%s\n",((IdentifierToken *)(((OperatorToken *)(List->head->next->value))->token[0]))->name);
          printf("List->head->next->value->token[1]=%s\n",((StringToken *)(((OperatorToken *)(List->head->next->value))->token[1]))->name);

        }
        else if(token->type==TOKEN_INTEGER_TYPE || token->type==TOKEN_FLOAT_TYPE){
          List->state=NUMBER;
        }
        else{
          List->state=ERROR;
        }break;

      case STRING :
        if(token->type==TOKEN_OPERATOR_TYPE ){
          if(strcmp(((OperatorToken *)(token))->symbol,"}")==0){
            List->state=END;
          }
          else if(strcmp(((OperatorToken *)(token))->symbol,",")==0){
            List->state=OBJECT;
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
          }
          else if(strcmp(((OperatorToken *)(token))->symbol,",")==0){
            List->state=OBJECT;
          }
          else{
            List->state=ERROR;
          }
        }
        else{
          List->state=ERROR;
        }break;

      // case ARRAY_VALUE:
        // if(token->type==TOKEN_OPERATOR_TYPE){
          // if(strcmp(((OperatorToken *)(token))->symbol,"{")==0){
            // List->state=OBJECT;
          // }
          // else if(strcmp(((OperatorToken *)(token))->symbol,"[")==0){
            // List->state=ARRAY;
          // }
          // else{
            // List->state=ERROR;
          // }
        // }
        // else if(token->type==TOKEN_STRING_TYPE){
          // List->state=STRING;
        // }
        // else if(token->type==TOKEN_INTEGER_TYPE || token->type==TOKEN_FLOAT_TYPE){
          // List->state=NUMBER;
        // }
        // else{
          // List->state=ERROR;
        // }break;

      // case ARRAY_OBJECT:
        // if(token->type==TOKEN_IDENTIFIER_TYPE){
          // List->state=ARRAY_WAIT_FOR_COLON;
        // }
        // else{
          // List->state=ERROR;
        // }break;

      // case ARRAY_WAIT_FOR_COLON:
        // if(token->type==TOKEN_OPERATOR_TYPE && strcmp(((OperatorToken *)(token))->symbol,":")==0){
          // List->state=ARRAY_VALUE;
        // }
        // else{
          // List->state=ERROR;
        // }break;

      // case ARRAY_STRING :
        // if(token->type==TOKEN_OPERATOR_TYPE ){
          // if(strcmp(((OperatorToken *)(token))->symbol,"}")==0){
            // List->state=END;
          // }
          // else if(strcmp(((OperatorToken *)(token))->symbol,",")==0){
            // List->state=OBJECT;
          // }
          // else{
            // List->state=ERROR;
          // }
        // }
        // else{
          // List->state=ERROR;
        // }break;

      // case ARRAY_NUMBER :
        // if(token->type==TOKEN_OPERATOR_TYPE ){
          // if(strcmp(((OperatorToken *)(token))->symbol,"}")==0){
            // List->state=END;
          // }
          // else if(strcmp(((OperatorToken *)(token))->symbol,",")==0){
            // List->state=OBJECT;
          // }
          // else{
            // List->state=ERROR;
          // }
        // }
        // else{
          // List->state=ERROR;
        // }break;


    }
    token=getToken();

  }while(token!=NULL);

  return List;
}

