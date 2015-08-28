#ifndef __C_EXCEPTION_CONFIG_H__
#define __C_EXCEPTION_CONFIG_H__
#include <stdio.h>
#include "ErrorObject.h"

#define CEXCEPTION_T      ErrorObject *
#define CEXCEPTION_NONE   NULL


#endif // CExeptionConfig_H
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
#ifndef FindElementFunction_H
#define FindElementFunction_H

#include "Token.h"
#include "LinkedList.h"

ListElement *keyFind(LinkedList *list, void *key, int(*compare)(void *,void *));
Token *getElementValue(ListElement *findKey);

#endif // FindElementFunction_H
#ifndef IteratorFunction_H
#define IteratorFunction_H

#include "LinkedList.h"

typedef struct {
   ListElement *current;
} Iterator;

Iterator *createIterator(LinkedList *list);
Iterator *iteratorGetNext(Iterator *iter);

#endif // IteratorFunction_H
#ifndef JSON_H
#define JSON_H

#include "LinkedList.h"
#include "Token.h"

#define TOKEN_DECLARE                               \
  Token *openBrace0=createOperatorToken("{");       \
  Token *openBrace1=createOperatorToken("{");       \
  Token *openBrace2=createOperatorToken("{");       \
  Token *openBrace3=createOperatorToken("{");       \
  Token *closeBrace0=createOperatorToken("}");      \
  Token *closeBrace1=createOperatorToken("}");      \
  Token *closeBrace2=createOperatorToken("}");      \
  Token *closeBrace3=createOperatorToken("}");      \
  Token *caret=createOperatorToken("^");            \
  Token *coma0=createOperatorToken(",");            \
  Token *coma1=createOperatorToken(",");            \
  Token *coma2=createOperatorToken(",");            \
  Token *coma3=createOperatorToken(",");            \
  Token *colon0=createOperatorToken(":");           \
  Token *colon1=createOperatorToken(":");           \
  Token *colon2=createOperatorToken(":");           \
  Token *colon3=createOperatorToken(":");           \
  Token *colon4=createOperatorToken(":");           \
  Token *colon5=createOperatorToken(":");           \
  Token *colon6=createOperatorToken(":");           \
  Token *dollarSign=createOperatorToken("$");       \
  Token *NAME1=createIdentifierToken("NAME1");      \
  Token *NAME2=createIdentifierToken("NAME2");      \
  Token *NAME3=createIdentifierToken("NAME3");      \
  Token *NAME4=createIdentifierToken("NAME4");      \
  Token *AGE=createIdentifierToken("AGE");          \
  Token *ADD=createIdentifierToken("ADD");          \
  Token *JS=createStringToken("JS");                \
  Token *STEVEN=createStringToken("STEVEN");        \
  Token *YEN=createStringToken("YEN");              \
  Token *ABU=createStringToken("ABU");              \
  Token *int20=createIntegerToken(20);              \
  Token *int30=createIntegerToken(30);

#define TOKEN_FREE        \
  free(openBrace0);       \
  free(openBrace1);       \
  free(openBrace2);       \
  free(openBrace3);       \
  free(closeBrace0);      \
  free(closeBrace1);      \
  free(closeBrace2);      \
  free(closeBrace3);      \
  free(caret);            \
  free(coma0);            \
  free(coma1);            \
  free(coma2);            \
  free(coma3);            \
  free(colon0);           \
  free(colon1);           \
  free(colon2);           \
  free(colon3);           \
  free(NAME1);            \
  free(AGE);              \
  free(NAME2);            \
  free(NAME3);            \
  free(JS);               \
  free(STEVEN);           \
  free(YEN);              \
  free(int20);            \
  free(int30);

#define DUMP_REMAIN_TOKEN                                                                               \
  dumpToken=getToken();                                                                                 \
  while(1){                                                                                             \
    if(dumpToken->type==TOKEN_OPERATOR_TYPE && strcmp(((OperatorToken *)(dumpToken))->symbol,"$")==0)   \
      break;                                                                                            \
    dumpToken=getToken();                                                                               \
  }

#define DECLARE_CURRENT_PTR                                                                                       \
  char *opCurrentTok=((OperatorToken *)(token))->symbol;                                                          \
  int intCurrentTok=((IntegerToken *)(token))->value;                                                             \
  char *strCurrentTok=((StringToken *)(token))->name;                                                             \
  char *idenCurrentTok=((IdentifierToken *)(token))->name;

#define DECLARE_RIGHT_PTR                                                                                         \
  char *opRightTok=((OperatorToken *)(rightToken))->symbol;                                                       \
  int intRightTok=((IntegerToken *)(rightToken))->value;                                                          \
  char *strRightTok=((StringToken *)(rightToken))->name;                                                          \
  char *idenRightTok=((IdentifierToken *)(rightToken))->name;

#define DECLARE_LEFT_PTR                                                                                          \
  char *opLeftTok=((OperatorToken *)(leftToken))->symbol;                                                         \
  int intLeftTok=((IntegerToken *)(leftToken))->value;                                                            \
  char *strLeftTok=((StringToken *)(leftToken))->name;                                                            \
  char *idenLeftTok=((IdentifierToken *)(leftToken))->name;


typedef struct {
  JsonState state;
} JsonObject;

typedef struct {
  TokenType type;
  uint32_t startColumn;
  uint32_t length;
  char *symbol;
  Arity arity;
  LinkedList *list;
} JsonToken;

Token *jsonParse(JsonObject *jsonObj);

JsonObject *createJsonObject();

Token *link2Tokens(Token *leftValue, char *operatorSymbol, Token *rightValue);




#endif // JSON_H
#ifndef LinkedList_H
#define LinkedList_H

#include "Token.h"

typedef enum{
  WAIT_FOR_TOKEN,
  OBJECT,
  WAIT_FOR_COLON,
  VALUE,
  ARRAY,
  NUMBER,
  STRING,
  END_OR_CONTINUE,
  END,
  WAIT_FOR_OPERATOR,
  ERROR,
}JsonState;

typedef struct ListElement_t{
  struct ListElement_t *next;
  void *value;
}ListElement;

typedef struct {
  ListElement *head;
  ListElement *tail;
  int length;
  JsonState state;
}LinkedList;

//*** initialize LinkedList function start here***
LinkedList *createLinkedList();
ListElement *createListElement(void *value);

//*** Adding Element function start here ***
void addLast(ListElement *newEle,LinkedList *list );
void addFirst(LinkedList *list,ListElement *newElem);

//*** Removing Element function start here ***
ListElement *removeFirst(LinkedList *list);
ListElement *removeLast(LinkedList *list);


#endif // LinkedList_H
#ifndef Token_H
#define Token_H

#include "LinkedList.h"
#include <stdint.h>

typedef enum {
  TOKEN_UNKNOWN_TYPE,
  TOKEN_INTEGER_TYPE,
  TOKEN_FLOAT_TYPE,
  TOKEN_STRING_TYPE,
  TOKEN_OPERATOR_TYPE,
  TOKEN_IDENTIFIER_TYPE,
  TOKEN_JSON_TYPE,
} TokenType;

typedef enum {
  PREFIX, //-2
  INFIX,	//2*2
  POSTFIX	//x++
} Arity;

typedef enum {
  NONE,
  LEFT_TO_RIGHT,
  RIGHT_TO_LEFT,
} Associativity;

typedef struct {
  TokenType type;
  uint32_t startColumn;
  uint32_t length;
} Token;

typedef struct {
  TokenType type;
  uint32_t startColumn;
  uint32_t length;
  int value;
} IntegerToken;

typedef struct {
  TokenType type;
  uint32_t startColumn;
  uint32_t length;
  double value;
} FloatToken;

typedef struct {
  TokenType type;
  uint32_t startColumn;
  uint32_t length;
  char *name;
} IdentifierToken, StringToken;

typedef struct {
  TokenType type;
  uint32_t startColumn;
  uint32_t length;
  char *symbol;
  Arity arity;
  Token *token[0];
} OperatorToken;

Token *getToken();



#endif // Token_H

#ifndef compareFunction_H
#define compareFunction_H

int intCompare(void *first, void *second);
int strCompare (void *first, void *second);

#endif // compareFunction_H
#ifndef createTokenType_H
#define createTokenType_H

#include "Token.h"
#include "JSON.h"

Token *createOperatorToken(char *symbol);
Token *createIdentifierToken(char *key);
Token *createIntegerToken(int value);
Token *createFloatToken(double value);
Token *createStringToken(char *value);
Token *createJsonToken(JsonObject *json);


#endif // createTokenType_H
