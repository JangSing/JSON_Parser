#ifndef JSON_H
#define JSON_H

#include "LinkedList.h"
#include "Token.h"

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

LinkedList *jsonParse();

Token *jsonParse1(JsonObject *jsonObj);

JsonObject *createJsonObject();

Token *link2Tokens(Token *leftValue, char *operatorSymbol, Token *rightValue);

Token *getElementValue(ListElement *findKey);


#endif // JSON_H
