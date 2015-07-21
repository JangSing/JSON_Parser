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

#include <stdio.h>
#include <assert.h>


int intCompare(void *first, void *second){

  if(first==NULL||second==NULL){
    return -1;
  }
  int *ptr=(int *)(first);
  int *ptr1=(int *)(second);

  if(*ptr==*ptr1){
    return 0;
  }
  else{
    return 1;
  }
}

int strCompare (void *first, void *second){

  if(first==NULL||second==NULL){
    return -1;
  }
  char *ptr=(char *)(first);
  char *ptr1=(char *)(second);

  if(strcmp(ptr,ptr1)==0){
    return 0;
  }
  else{
    return 1;
  }

}