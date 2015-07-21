#ifndef ErrorObject_H
#define ErrorObject_H

typedef enum {
  ERR_EXPECT_COLON,
  ERR_EXPECT_OPERATOR,
  ERR_EXPECT_IDEN,
  ERR_ILLEGAL_VALUE,
  ERR_NO_ERROR,
  ERR_WORNG_CODE,
  ERR_DUNNO_WHAT_HAPPEN,
  ERR_NUMBER_NOT_NEGATIVE,
  ERR_NUMBER_NOT_POSITIVE,
  ERR_NUMBER_TOO_LARGE,
}ErrorCode;

typedef struct{
  char *errorMsg;
  ErrorCode errorCode;
}ErrorObject;

void freeError(ErrorObject *err);

void ThrowError(char *msg, ErrorCode errCode);

#endif // ErrorObject_H