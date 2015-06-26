#include "JSON.h"
#include "getToken.h"
#include "LinkedList.h"
#include <malloc.h>
#include <stdio.h>
#include <assert.h>
#include <ctype.h>

Token *ReceiveToken(){
  return getToken();
}

LinkedList *DetermineState(){
  Token *token;
  int i;

  LinkedList *List=malloc(sizeof(LinkedList));

  List->state=WAIT_FOR_TOKEN;


  for(i=0;i<5;i++){
    token=getToken();

    printf("i=%d token-> state=%d\n\n",i,List-> state);
    printf("i=%d token-> type=%d\n",i,token-> type);
    printf("i=%d token-> Operator=%d\n",i,token-> Operator);
    printf("i=%d token-> value=%s\n",i,token-> value);

    switch(List->state){
      case WAIT_FOR_TOKEN :
        if(token->type==TOKEN_OPERATOR_TYPE && token->Operator==OPERATOR1){
          List->state=OBJECT;
        }
        else{
          List->state=ERROR;
        }break;

      case OBJECT :
        if(token->type==TOKEN_IDENTIFIER_TYPE ){
          List->state=WAIT_FOR_OPERATOR2;
        }
        else{
          List->state=ERROR;
        }break;

      case WAIT_FOR_OPERATOR2 :
        if(token->type==TOKEN_OPERATOR_TYPE && token->Operator==OPERATOR2){
          List->state=VALUE;
        }
        else{
          List->state=ERROR;
        }break;

      case VALUE :
        if(token->type==TOKEN_OPERATOR_TYPE){
          if(token->Operator==OPERATOR1){
            List->state=OBJECT;
          }
          else if(token->Operator==OPERATOR6){
            List->state=ARRAY;
          }
          else{
            List->state=ERROR;
          }
        }
        else if(token->type==TOKEN_IDENTIFIER_TYPE){
          List->state=END_OR_CON;
          // if(isdigit(token->value))
            // List->state=NUMBER;
          // else if(isalpha(token->value))
            // List->state=STRING;
          // else
            // List->state=ERROR;
        }
        else{
          List->state=ERROR;
        }break;

      case END_OR_CON :
        if(token->type==TOKEN_OPERATOR_TYPE){
          if(token->Operator==OPERATOR4){
            List->state=END;
          }
          else if(token->Operator==OPERATOR3){
            List->state=OBJECT;
          }
          else{
            List->state=ERROR;
          }
        }
        else{
          List->state=ERROR;
        }break;


    }
    // token=getToken();
    // printf("token-> state=%d\n",token-> state);
    // printf("token-> type=%d\n",token-> type);
    // printf("token-> Operator=%d\n",token-> Operator);
    // printf("token-> value=%s\n\n",token-> value);
  }
// }

  // state=state;



  return List;
}
