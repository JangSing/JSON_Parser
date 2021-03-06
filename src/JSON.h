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
