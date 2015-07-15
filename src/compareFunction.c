#include "compareFunction.h"

#include <stdio.h>
#include <assert.h>


int intCompare(void *first, void *second){
  int *ptr=(int *)(first);
  int *ptr1=(int *)(second);

  if(*ptr==*ptr1){
    return 0;
  }
  else if(first==NULL||second==NULL){
    return -1;
  }
  else{
    return 1;
  }
}

int strCompare (void *first, void *second){

  char *ptr=(char *)(first);
  char *ptr1=(char *)(second);

  if(strcmp(ptr,ptr1)==0){
    return 0;
  }
  else if(first==NULL||second==NULL){
    return -1;
  }
  else{
    return 1;
  }

}