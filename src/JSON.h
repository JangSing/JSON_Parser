#ifndef JSON_H
#define JSON_H

#include "LinkedList.h"
#include "Token.h"

LinkedList *jsonParse();

Token *createOperatorToken(char *symbol);
IdentifierToken *createIdentifierToken(char *key);
IntegerToken *createIntegerToken(int value);
StringToken *createStringToken(char *value);

Token *link2Tokens(Token *leftValue, char *operatorSymbol, Token *rightValue);

Token *getElementValue(ListElement *findKey);


#endif // JSON_H
