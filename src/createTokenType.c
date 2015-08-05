#include "ErrorObject.h"
#include "CException.h"
#include "compareFunction.h"
#include "createTokenType.h"
#include "FindElementFunction.h"
#include "IteratorFunction.h"
#include "JSON.h"
#include "LinkedList.h"
#include "Token.h"
#include "CustomAssertion.h"

#include <malloc.h>
#include <stdio.h>
#include <assert.h>
#include <ctype.h>
#include <string.h>

Token *createOperatorToken(char *symbol) {
  if(symbol==NULL){
    return NULL;
  }
  else{
    OperatorToken *opTok =malloc(sizeof(OperatorToken)+sizeof(Token *)*2);

    opTok->type=TOKEN_OPERATOR_TYPE;
    opTok->symbol   =symbol;
    opTok->token[0] =NULL;
    opTok->token[1] =NULL;
    opTok->length   =strlen(symbol);

    return (Token *)opTok;
  }
}

Token *createIdentifierToken(char *key){
  if(key==NULL){
    return NULL;
  }
  else{
    IdentifierToken *IdenTok =malloc(sizeof(IdentifierToken));

    IdenTok->type   =TOKEN_IDENTIFIER_TYPE;
    IdenTok->name   =key;
    IdenTok->length =strlen(key);

    return (Token *)IdenTok;
  }
}

Token *createIntegerToken(int value){
  if(&value==NULL){
    return NULL;
  }
  else{
    IntegerToken *intTok =malloc(sizeof(IntegerToken));
    char *buffer=malloc(sizeof(char)*512);
    int length;
    length=sprintf(buffer,"%d",value);
    
    intTok->type    =TOKEN_INTEGER_TYPE;
    intTok->value   =value;
    intTok->length  =length;

    return (Token *)intTok;
  }
}

Token *createFloatToken(double value){
  if(&value==NULL){
    return NULL;
  }
  else{
    FloatToken *floatTok =malloc(sizeof(FloatToken));
    char *buffer=malloc(sizeof(char)*512);
    int length;
    length=sprintf(buffer,"%d",value);

    floatTok->type=TOKEN_FLOAT_TYPE;
    floatTok->value=value;
    floatTok->length=length;

    return (Token *)floatTok;
  }
}

Token *createStringToken(char *value){
  if(value==NULL){
    return NULL;
  }
  else{
    StringToken *StrTok =malloc(sizeof(StringToken));

    StrTok->type=TOKEN_STRING_TYPE;
    StrTok->name=value;
    StrTok->length=strlen(value);

    return (Token *)StrTok;
  }
}

Token *createJsonToken(JsonObject *json){
  if(json==NULL){
    return NULL;
  }
  else{
    JsonToken *jsonTok =malloc(sizeof(JsonToken));

    jsonTok->type=TOKEN_JSON_TYPE;
    jsonTok->list->state=json->state;

    return (Token *)jsonTok;
  }
}