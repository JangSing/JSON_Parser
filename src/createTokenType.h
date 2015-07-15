#ifndef createTokenType_H
#define createTokenType_H

#include "Token.h"

Token *createOperatorToken(char *symbol);
IdentifierToken *createIdentifierToken(char *key);
IntegerToken *createIntegerToken(int value);
StringToken *createStringToken(char *value);


#endif // createTokenType_H
