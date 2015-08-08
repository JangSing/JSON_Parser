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

#include <stdarg.h>
#include <malloc.h>
#include <stdio.h>
#include <assert.h>
#include <ctype.h>

int recur=0;
int array=0;

Token *link2Tokens(Token *leftValue, char *operatorSymbol, Token *rightValue){
  if( leftValue==NULL || operatorSymbol==NULL || rightValue==NULL){
    return NULL;
  }
  else{
    OperatorToken *opTok;

    opTok=(OperatorToken *)createOperatorToken(operatorSymbol);

    opTok->token[0]=leftValue;
    opTok->token[1]=rightValue;

    return (Token *)opTok;
  }
}

Token *getElementValue(ListElement *findKey){
  if(findKey==NULL){
    return NULL;
  }
  else{
    return ((OperatorToken *)(findKey->value))->token[1];
  }
}

JsonObject *createJsonObject(){
  JsonObject *jsonObj=malloc(sizeof(JsonObject));
  jsonObj->state=WAIT_FOR_TOKEN;
  return jsonObj;
}

Token *jsonParse(JsonObject *jsonObj){

  JsonToken *jsonTok=malloc(sizeof(JsonToken));
  LinkedList *list;

  JsonObject *recurJsonObj;
  Token *token,*dumpToken;
  ListElement *newNode;
  Token *leftToken,*rightToken;
  char *errMsg;
  int i;

  if(jsonObj==NULL){
    printf("\n\n");
    errMsg="ERROR[%d]:Empty object passing into the JsonParse.";
    printf(errMsg,ERR_EMPTY_OBJECT);
    throwError(ERR_EMPTY_OBJECT,errMsg,ERR_EMPTY_OBJECT);
  }

  list=createLinkedList();

  if(recur==0){
    token=getToken();
    if(token->type==TOKEN_OPERATOR_TYPE && strcmp(((OperatorToken *)(token))->symbol,"$")==0){
      printf("\n");
      errMsg="ERROR[%d]:Empty String passing into the JsonParse.";
      printf(errMsg,ERR_EMPTY_STRING);
      throwError(ERR_EMPTY_STRING,errMsg,ERR_EMPTY_STRING);
    }
  }
  else{
    jsonObj->state=OBJECT;
    newNode=createListElement(createOperatorToken("{"));
    addLast(newNode,list);
    token=getToken();
    if(token->type==TOKEN_OPERATOR_TYPE && strcmp(((OperatorToken *)(token))->symbol,"$")==0){
      recur=0;
      jsonTok->list=list;
      return (Token *)jsonTok;
    }
  }

  do{
    switch(jsonObj->state){
      case WAIT_FOR_TOKEN :
        if(token-> type==TOKEN_OPERATOR_TYPE && strcmp(((OperatorToken *)(token))->symbol,"{")==0){
          // printf("{\n");
          jsonObj->state=OBJECT;
          newNode=createListElement(token);
          addLast(newNode,list);
        }
        else{
          recur=0;
          jsonObj->state=ERROR;
          DUMP_REMAIN_TOKEN;
          DECLARE_CURRENT_PTR;
          // Check Token type and Throw the Error.
          if(token-> type==TOKEN_OPERATOR_TYPE){
            printf("\n");
            errMsg="ERROR[%d]:Expected '{' at the beginning of JsonList but get '%s'.";
            printf(errMsg,ERR_EXPECT_OPERATOR,opCurrentTok);
            throwError(ERR_EXPECT_OPERATOR,errMsg,ERR_EXPECT_OPERATOR,opCurrentTok);
          }
          else if(token-> type==TOKEN_IDENTIFIER_TYPE || token-> type==TOKEN_STRING_TYPE){
            printf("\n");
            errMsg="ERROR[%d]:Expected '{' at the beginning of JsonList but get '%s'.";
            printf(errMsg,ERR_EXPECT_OPERATOR,strCurrentTok);
            throwError(ERR_EXPECT_OPERATOR,errMsg,ERR_EXPECT_OPERATOR,strCurrentTok);
          }
          else if (token-> type==TOKEN_INTEGER_TYPE){
            printf("\n");
            errMsg="ERROR[%d]:Expected '{' at the beginning of JsonList but get '%d'.";
            printf(errMsg,ERR_EXPECT_OPERATOR,intCurrentTok);
            throwError(ERR_EXPECT_OPERATOR,errMsg,ERR_EXPECT_OPERATOR,intCurrentTok);
          }
          else{
            printf("\n");
            errMsg="ERROR[%d]:Expected '{' at the beginning of JsonList.";
            printf(errMsg,ERR_EXPECT_OPERATOR);
            throwError(ERR_EXPECT_OPERATOR,errMsg,ERR_EXPECT_OPERATOR);
          }
        }break;

      case OBJECT :
        if(token->type==TOKEN_IDENTIFIER_TYPE){
          // for(i=recur;i!=0;i--){
            // printf("\t\t");
          // }printf("\t%s\t",((IdentifierToken *)token)->name);
          jsonObj->state=WAIT_FOR_COLON;
          leftToken=token;
        }
        else{
          recur=0;
          jsonObj->state=ERROR;
          DUMP_REMAIN_TOKEN;
          DECLARE_CURRENT_PTR;
          // Check Token type and Throw the Error.
          if(token-> type==TOKEN_OPERATOR_TYPE){
            printf("\n");
            errMsg="ERROR[%d]:Expected an Identifier for 'Key' but get '%s'.\n\n{'%s'\n%*s^\n";
            printf(errMsg,ERR_EXPECT_IDEN,opCurrentTok,opCurrentTok,1,"");
            throwError(ERR_EXPECT_IDEN,errMsg,ERR_EXPECT_IDEN,opCurrentTok);
          }
          else if(token-> type==TOKEN_IDENTIFIER_TYPE || token-> type==TOKEN_STRING_TYPE){
            printf("\n");
            errMsg="ERROR[%d]:Expected an Identifier for 'Key' but get '%s'.\n\n{'%s'\n%*s^\n";
            printf(errMsg,ERR_EXPECT_IDEN,strCurrentTok,strCurrentTok,1,"");
            throwError(ERR_EXPECT_IDEN,errMsg,ERR_EXPECT_IDEN,strCurrentTok,strCurrentTok,1,"");
          }
          else if (token-> type==TOKEN_INTEGER_TYPE){
            printf("\n");
            errMsg="ERROR[%d]:Expected an Identifier for 'Key' but get '%d'.\n\n{%d\n%*s^\n";
            printf(errMsg,ERR_EXPECT_IDEN,intCurrentTok,intCurrentTok,1,"");
            throwError(ERR_EXPECT_IDEN,errMsg,ERR_EXPECT_IDEN,intCurrentTok,intCurrentTok,1,"");
          }
          else{
            printf("\n");
            errMsg="ERROR[%d]:Expected an Identifier for 'Key'.";
            printf(errMsg,ERR_EXPECT_IDEN);
            throwError(ERR_EXPECT_IDEN,errMsg,ERR_EXPECT_IDEN);
          }
        }break;

      case WAIT_FOR_COLON :
        if(token->type==TOKEN_OPERATOR_TYPE && strcmp(((OperatorToken *)(token))->symbol,":")==0){
          // printf(":");
          jsonObj->state=VALUE;
        }
        else{
          recur=0;
          jsonObj->state=ERROR;
          DUMP_REMAIN_TOKEN;
          DECLARE_CURRENT_PTR;
          DECLARE_LEFT_PTR;
          // Check Token type and Throw the Error.
          if(token-> type==TOKEN_OPERATOR_TYPE){
            printf("\n");
            errMsg="ERROR[%d]:Expected ':' after 'Key' but get '%s'.\n\n{'%s'%s\n%*s^\n";
            printf(errMsg,ERR_EXPECT_OPERATOR,opCurrentTok,idenLeftTok,opCurrentTok,(leftToken->length)+3,"");
            throwError(ERR_EXPECT_OPERATOR,errMsg,ERR_EXPECT_OPERATOR,opCurrentTok,idenLeftTok,opCurrentTok,(leftToken->length)+3,"");
          }
          else if(token-> type==TOKEN_IDENTIFIER_TYPE || token-> type==TOKEN_STRING_TYPE){
            printf("\n");
            errMsg="ERROR[%d]:Expected ':' after 'Key' but get '%s'.\n\n{'%s''%s'\n%*s^\n";
            printf(errMsg,ERR_EXPECT_OPERATOR,strCurrentTok,idenLeftTok,strCurrentTok,(leftToken->length)+3,"");
            throwError(ERR_EXPECT_OPERATOR,errMsg,ERR_EXPECT_OPERATOR,strCurrentTok,idenLeftTok,strCurrentTok,(leftToken->length)+3,"");
          }
          else if (token-> type==TOKEN_INTEGER_TYPE){
            printf("\n");
            errMsg="ERROR[%d]:Expected ':' after 'Key' but get '%d'.\n\n{'%s'%d\n%*s^\n";
            printf(errMsg,ERR_EXPECT_OPERATOR,intCurrentTok,idenLeftTok,intCurrentTok,(leftToken->length)+3,"");
            throwError(ERR_EXPECT_OPERATOR,errMsg,ERR_EXPECT_OPERATOR,intCurrentTok,idenLeftTok,intCurrentTok,(leftToken->length)+3,"");
          }
          else{
            printf("\n");
            errMsg="ERROR[%d]:Expected ':' after 'Key'.";
            printf(errMsg,ERR_EXPECT_OPERATOR);
            throwError(ERR_EXPECT_OPERATOR,errMsg,ERR_EXPECT_OPERATOR);
          }
        }break;

      case VALUE :
        if(token->type==TOKEN_OPERATOR_TYPE){
          if(strcmp(((OperatorToken *)(token))->symbol,"{")==0){
            // printf("{\n");
            jsonObj->state=WAIT_FOR_OPERATOR;

            recur++;
            recurJsonObj=createJsonObject();
            rightToken=jsonParse(recurJsonObj);
            if(recurJsonObj->state!=END){
              printf("\n");
              errMsg="ERROR[%d]:ACCESS DENIED!!!The Json List is not completed.";
              printf(errMsg,ERR_ACCESS_DENIED);
              throwError(ERR_ACCESS_DENIED,errMsg,ERR_ACCESS_DENIED);
            }
            newNode=createListElement(link2Tokens(leftToken, ":", rightToken));
            addLast(newNode,list);
          }
          else{
            recur=0;
            jsonObj->state=ERROR;
            DUMP_REMAIN_TOKEN;
            DECLARE_CURRENT_PTR;
            DECLARE_LEFT_PTR;
            printf("\n");
            errMsg="ERROR[%d]:Expected an Integer/String/Float/{ for 'Value' but get %s.\n\n'%s'%s%s\n%*s^\n";
            printf(errMsg,ERR_ILLEGAL_VALUE,opCurrentTok,idenLeftTok,":",opCurrentTok,(leftToken->length)+3,"");
            throwError(ERR_ILLEGAL_VALUE,errMsg,ERR_ILLEGAL_VALUE,opCurrentTok,idenLeftTok,":",opCurrentTok,(leftToken->length)+3,"");
          }
        }
        else if(token->type==TOKEN_STRING_TYPE || token->type==TOKEN_INTEGER_TYPE || token->type==TOKEN_FLOAT_TYPE){
          // if(token->type==TOKEN_STRING_TYPE)
            // printf("%s",((StringToken *)token)->name);
          // else if(token->type==TOKEN_INTEGER_TYPE)
            // printf("%d",((IntegerToken *)token)->value);
          // else
            // printf("%d",((FloatToken *)token)->value);
          jsonObj->state=WAIT_FOR_OPERATOR;
          rightToken=token;
          newNode=createListElement(link2Tokens(leftToken, ":", rightToken));
          addLast(newNode,list);
        }
        else{
          recur=0;
          jsonObj->state=ERROR;
          DUMP_REMAIN_TOKEN;
          printf("\n");
          errMsg="ERROR[%d]:Expected an Integer/String/Float/{ for 'Value'.";
          printf(errMsg,ERR_ILLEGAL_VALUE);
          throwError(ERR_ILLEGAL_VALUE,errMsg,ERR_ILLEGAL_VALUE);
        }break;

      case WAIT_FOR_OPERATOR :
        if(token->type==TOKEN_OPERATOR_TYPE){
          if(strcmp(((OperatorToken *)(token))->symbol,"}")==0){
            // printf("\n}\n");
            jsonObj->state=END;
            newNode=createListElement(token);
            addLast(newNode,list);
          }
          else if(strcmp(((OperatorToken *)(token))->symbol,",")==0){
            // printf(",\n");
            jsonObj->state=OBJECT;
          }
          else{
            recur=0;
            jsonObj->state=ERROR;
            DUMP_REMAIN_TOKEN;
            DECLARE_CURRENT_PTR;
            DECLARE_LEFT_PTR;
            DECLARE_RIGHT_PTR;
            printf("\n");
            if(rightToken->type==TOKEN_INTEGER_TYPE){
              errMsg="ERROR[%d]:Expected Operator '}' or ',' after 'Value' but get '%s'.\n\n'%s'%s%d%s\n%*s^\n";
              printf(errMsg,ERR_EXPECT_OPERATOR,opCurrentTok,idenLeftTok,":",intRightTok,opCurrentTok,(leftToken->length)+(rightToken->length)+3,"");
              throwError(ERR_EXPECT_OPERATOR,errMsg,ERR_EXPECT_OPERATOR,opCurrentTok,idenLeftTok,":",intRightTok,opCurrentTok,(leftToken->length)+(rightToken->length)+3,"");
            }
            else{
              errMsg="ERROR[%d]:Expected Operator '}' or ',' after 'Value' but get '%s'.\n\n'%s'%s'%s'%s\n%*s^\n";
              printf(errMsg,ERR_EXPECT_OPERATOR,opCurrentTok,idenLeftTok,":",strRightTok,opCurrentTok,(leftToken->length)+(rightToken->length)+5,"");
              throwError(ERR_EXPECT_OPERATOR,errMsg,ERR_EXPECT_OPERATOR,opCurrentTok,idenLeftTok,":",strRightTok,opCurrentTok,(leftToken->length)+(rightToken->length)+5,"");
            }
          }
        }
        else{
          recur=0;
          jsonObj->state=ERROR;
          DUMP_REMAIN_TOKEN;
          DECLARE_CURRENT_PTR;
          DECLARE_LEFT_PTR;
          DECLARE_RIGHT_PTR;
          // Check Token type and Throw the Error.
          if(token-> type==TOKEN_IDENTIFIER_TYPE || token-> type==TOKEN_STRING_TYPE){
            printf("\n");
            if(rightToken->type==TOKEN_INTEGER_TYPE){
              errMsg="ERROR[%d]:Expected Operator '}' or ',' after 'Value' but get '%s'.\n\n'%s'%s%d'%s'\n%*s^\n";
              printf(errMsg,ERR_EXPECT_OPERATOR,strCurrentTok,idenLeftTok,":",intRightTok,strCurrentTok,(leftToken->length)+(rightToken->length)+3,"");
              throwError(ERR_EXPECT_OPERATOR,errMsg,ERR_EXPECT_OPERATOR,strCurrentTok,idenLeftTok,":",intRightTok,strCurrentTok,(leftToken->length)+(rightToken->length)+3,"");
            }
            else{
              errMsg="ERROR[%d]:Expected Operator '}' or ',' after 'Value' but get '%s'.\n\n'%s'%s'%s''%s'\n%*s^\n";
              printf(errMsg,ERR_EXPECT_OPERATOR,strCurrentTok,idenLeftTok,":",strRightTok,strCurrentTok,(leftToken->length)+(rightToken->length)+5,"");
              throwError(ERR_EXPECT_OPERATOR,errMsg,ERR_EXPECT_OPERATOR,strCurrentTok,idenLeftTok,":",strRightTok,strCurrentTok,(leftToken->length)+(rightToken->length)+5,"");
            }
          }
          else if (token-> type==TOKEN_INTEGER_TYPE){
            printf("\n");
            if(rightToken->type==TOKEN_INTEGER_TYPE){
              errMsg="ERROR[%d]:Expected Operator '}' or ',' after 'Value' but get '%d'.\n\n'%s'%s%d %d\n%*s^\n";
              printf(errMsg,ERR_EXPECT_OPERATOR,intCurrentTok,idenLeftTok,":",intRightTok,intCurrentTok,(leftToken->length)+(rightToken->length)+4,"");
              throwError(ERR_EXPECT_OPERATOR,errMsg,ERR_EXPECT_OPERATOR,intCurrentTok,idenLeftTok,":",intRightTok,intCurrentTok,(leftToken->length)+(rightToken->length)+4,"");
            }
            else{
              errMsg="ERROR[%d]:Expected Operator '}' or ',' after 'Value' but get '%d'.\n\n'%s'%s'%s'%d\n%*s^\n";
              printf(errMsg,ERR_EXPECT_OPERATOR,intCurrentTok,idenLeftTok,":",strRightTok,intCurrentTok,(leftToken->length)+(rightToken->length)+5,"");
              throwError(ERR_EXPECT_OPERATOR,errMsg,ERR_EXPECT_OPERATOR,intCurrentTok,idenLeftTok,":",strRightTok,intCurrentTok,(leftToken->length)+(rightToken->length)+5,"");
            }
          }
          else{
            printf("\n");
            errMsg="ERROR[%d]:Expected an Operator '}' or ',' after 'Value'.";
            printf(errMsg,ERR_EXPECT_OPERATOR);
            throwError(ERR_EXPECT_OPERATOR,errMsg,ERR_EXPECT_OPERATOR);
          }
        }break;

      case END :
        recur=0;
        jsonObj->state=ERROR;
        DUMP_REMAIN_TOKEN;
        printf("\n");
        errMsg="ERROR[%d]:ACCESS DENIED!!!The Json List already completed.";
        printf(errMsg,ERR_ACCESS_DENIED);
        throwError(ERR_ACCESS_DENIED,errMsg,ERR_ACCESS_DENIED);break;

      default:
        recur=0;
        jsonObj->state=ERROR;
        DUMP_REMAIN_TOKEN;
        printf("\n");
        errMsg="ERROR[%d]:Unknown Error";
        printf(errMsg,ERR_UNKNOWN_ERROR);
        throwError(ERR_UNKNOWN_ERROR,errMsg,ERR_UNKNOWN_ERROR);
    }

    token=getToken();
    if(token->type==TOKEN_OPERATOR_TYPE && strcmp(((OperatorToken *)(token))->symbol,"$")==0){
      break;
    }
    else{
      if(recur!=0 && token->type==TOKEN_OPERATOR_TYPE){
        if(strcmp(((OperatorToken *)(token))->symbol,"}")==0){
          if(jsonObj->state==STRING || jsonObj->state==NUMBER || jsonObj->state==WAIT_FOR_OPERATOR){
            // printf("\n");
            // for(i=recur;i!=0;i--){
              // printf("\t\t");
            // }printf("}");
            jsonObj->state=END;
            newNode=createListElement(token);
            addLast(newNode,list);
            recur--;
            break;
          }
          else{
            recur=0;
            jsonObj->state=ERROR;
            DUMP_REMAIN_TOKEN;
            printf("\n");
            errMsg="ERROR[%d]:Expected an Integer/String/Float/{ for 'Value' but get %s.\n\n'%s'%s%s\n%*s^\n";
            printf(errMsg,ERR_ILLEGAL_VALUE,((OperatorToken *)(token))->symbol,((IdentifierToken *)(leftToken))->name,":",((OperatorToken *)(token))->symbol,(leftToken->length)+3,"");
            throwError(ERR_ILLEGAL_VALUE,errMsg,ERR_ILLEGAL_VALUE,((OperatorToken *)(token))->symbol,((IdentifierToken *)(leftToken))->name,":",((OperatorToken *)(token))->symbol,(leftToken->length)+3,"");
          }
        }
        else{}
      }
      else{}
    }

  }while(1);

  if(jsonObj->state!=END){
    recur=0;
    jsonObj->state=ERROR;
    printf("\n");
    errMsg="ERROR[%d]:ACCESS DENIED!!!The Json List is not completed.";
    printf(errMsg,ERR_ACCESS_DENIED);
    throwError(ERR_ACCESS_DENIED,errMsg,ERR_ACCESS_DENIED);
  }
  else{
    jsonTok->list=list;
    return (Token *)jsonTok;
  }
}





