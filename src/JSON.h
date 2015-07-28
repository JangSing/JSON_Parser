#ifndef JSON_H
#define JSON_H

#include "LinkedList.h"
#include "Token.h"

#define TOKEN_DECLARE                               \
  Token *openBrace0=createOperatorToken("{");       \
  Token *openBrace1=createOperatorToken("{");       \
  Token *closeBrace0=createOperatorToken("}");      \
  Token *closeBrace1=createOperatorToken("}");      \
  Token *caret=createOperatorToken("^");            \
  Token *coma=createOperatorToken(",");             \
  Token *colon0=createOperatorToken(":");           \
  Token *colon1=createOperatorToken(":");           \
  Token *colon2=createOperatorToken(":");           \
  Token *colon3=createOperatorToken(":");           \
  Token *NAME1=createIdentifierToken("NAME1");      \
  Token *AGE=createIdentifierToken("AGE");          \
  Token *NAME2=createIdentifierToken("NAME2");      \
  Token *NAME3=createIdentifierToken("NAME3");      \
  Token *JS=createStringToken("JS");                \
  Token *STEVEN=createStringToken("STEVEN");        \
  Token *YEN=createStringToken("YEN");              \
  Token *int20=createIntegerToken(20)

#define DUMP_REMAIN_TOKEN                           \
  Token *dumpToken;                                 \
  dumpToken=getToken();                             \
  while(dumpToken!=NULL){                           \
    dumpToken=getToken();                           \
  }

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

Token *getElementValue(ListElement *findKey);


#endif // JSON_H
