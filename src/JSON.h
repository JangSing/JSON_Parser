#ifndef JSON_H
#define JSON_H

#include "LinkedList.h"
#include "Token.h"

LinkedList *DetermineState();

Token *createOperatorToken(char *symbol);
IntegerToken *createIntegerToken(int value);
IdentifierToken *createIdentifierToken(char *key);

Token *Link2Tokens(Token *leftValue, char *operatorSymbol, Token *rightValue);

#endif // JSON_H
