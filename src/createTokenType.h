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
