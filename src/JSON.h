#ifndef JSON_H
#define JSON_H

#include "LinkedList.h"
#include "Token.h"

LinkedList *JsonParse();

Token *createOperatorToken(char *symbol);
IdentifierToken *createIdentifierToken(char *key);
IntegerToken *createIntegerToken(int value);
StringToken *createStringToken(char *value);

Token *Link2Tokens(Token *leftValue, char *operatorSymbol, Token *rightValue);

Token *getElementValue(ListElement *FindKey);


#endif // JSON_H
