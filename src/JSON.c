#include "Token.h"
#include "LinkedList.h"

#include <malloc.h>
#include <stdio.h>
#include <assert.h>
#include <ctype.h>


LinkedList *DetermineState(){

  int i;
  Token *token;
  LinkedList *List=malloc(sizeof(LinkedList));

  List->state=WAIT_FOR_TOKEN;

  token=getToken();
  do{

    switch(List->state){
      case WAIT_FOR_TOKEN :
        if(token-> type=TOKEN_OPERATOR_TYPE && strcmp(((OperatorToken *)(token))->symbol,"{")==0){
          List->state=OBJECT;
        }
        else{
          List->state=ERROR;
        }break;

      case OBJECT :
        if(token->type==TOKEN_IDENTIFIER_TYPE){
          List->state=WAIT_FOR_COLON;
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
