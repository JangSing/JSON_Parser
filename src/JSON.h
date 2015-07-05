#ifndef JSON_H
#define JSON_H

#include "LinkedList.h"
#include "Token.h"

LinkedList *DetermineState();

Token *createOperatorToken(char *symbol);
IdentifierToken *createIdentifierToken(char *key);
IntegerToken *createIntegerToken(int value);
StringToken *createStringToken(char *value);

Token *Link2Tokens(Token *leftValue, char *operatorSymbol, Token *rightValue);

#endif // JSON_H
