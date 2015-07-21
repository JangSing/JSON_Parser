#include "ErrorObject.h"
#include <stdlib.h>

void ThrowError(char *msg, ErrorCode errCode){

  ErrorObject *errorObj=malloc(sizeof(ErrorObject));

  errorObj->errorMsg=msg;
  errorObj->errorCode=errCode;
  Throw(errorObj);
}

void freeError(ErrorObject *err){
  free(err);
}