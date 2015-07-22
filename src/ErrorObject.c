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
#include <stdlib.h>

void freeError(ErrorObject *err){
  free(err);
}

void throwError(ErrorCode errCode,char *msg , ...){

  ErrorObject *errorObj=malloc(sizeof(ErrorObject));

  char *msgBuffer;
  int strLength;

  va_list args;
  va_start(args,msg);
  strLength=vsnprintf(msgBuffer,0,msg,args);
  msgBuffer=malloc(strLength + 1);
  vsprintf(msgBuffer, msg, args);

  errorObj->errorMsg=msgBuffer;
  errorObj->errorCode=errCode;

  va_end(args);
  Throw(errorObj);
}


