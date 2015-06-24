#include "JSON.h"
#include "getToken.h"
#include <malloc.h>
#include <stdio.h>
#include <assert.h>

Token *ReceiveToken(){
  return getToken();
}

Token *DetermineState(Token *token){
  int state;
 
  Token *getToken=malloc(sizeof(Token));
  
  switch(state){
  case WAIT_FOR_TOKEN :
    if(getToken->value=="{")
      state=OBJECT;
    else 
      state=ERROR;break;
    
    
    }
  printf("state=%d",state);
  
  
}
  