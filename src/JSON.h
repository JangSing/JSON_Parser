#ifndef JSON_H
#define JSON_H

#include "LinkedList.h"
#include "Token.h"

LinkedList *jsonParse();

Token *link2Tokens(Token *leftValue, char *operatorSymbol, Token *rightValue);

Token *getElementValue(ListElement *findKey);


#endif // JSON_H
