#ifndef ErrorObject_H
#define ErrorObject_H

#include <stdarg.h>

typedef enum {
  ERR_NO_ERROR,
  ERR_WORNG_CODE,
  ERR_DUNNO_WHAT_HAPPEN,
  ERR_NUMBER_NOT_NEGATIVE,
  ERR_NUMBER_NOT_POSITIVE,
  ERR_NUMBER_TOO_LARGE,
  ERR_EXPECT_COLON,
  ERR_EXPECT_OPERATOR,
  ERR_EXPECT_IDEN,
  ERR_ACCESS_DENIED,
  ERR_ILLEGAL_VALUE,
  ERR_UNKNOWN_ERROR,
  ERR_EMPTY_OBJECT,
  ERR_EMPTY_STRING,
  ERR_KEY_NOT_FOUND
}ErrorCode;

typedef struct{
  char *errorMsg;
  ErrorCode errorCode;
}ErrorObject;

void throwError(ErrorCode errCode, char *msg, ...);

#endif // ErrorObject_H
