#include "createTokenType.h"
#include "Token.h"
#include "LinkedList.h"
#include "JSON.h"
#include "IteratorFunction.h"

#include <malloc.h>
#include <stdio.h>
#include <assert.h>
#include <ctype.h>

Token *createOperatorToken(char *symbol) {

    OperatorToken *opTok =malloc(sizeof(OperatorToken)+sizeof(Token *)*2);

    opTok->type=TOKEN_OPERATOR_TYPE;
    opTok->symbol=symbol;
    opTok->token[0]=NULL;
    opTok->token[1]=NULL;

  return (Token *)opTok;
}

IdentifierToken *createIdentifierToken(char *key){

    IdentifierToken *IdenTok =malloc(sizeof(IdentifierToken));

    IdenTok->type=TOKEN_IDENTIFIER_TYPE;
    IdenTok->name =key;

  return IdenTok;
}

IntegerToken *createIntegerToken(int value){

    IntegerToken *intTok =malloc(sizeof(IntegerToken));

    intTok->type=TOKEN_INTEGER_TYPE;
    intTok->value=value;

  return intTok;
}

StringToken *createStringToken(char *value){

    StringToken *StrTok =malloc(sizeof(StringToken));

    StrTok->type=TOKEN_STRING_TYPE;
    StrTok->name=value;

  return StrTok;
}