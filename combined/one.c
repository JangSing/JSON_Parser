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
#include <stdlib.h>

void throwError(ErrorCode errCode,char *msg , ...){
  ErrorObject *errorObj=malloc(sizeof(ErrorObject));

  char *msgBuffer;
  int strLength;

  va_list args;
  va_start(args,msg);
  strLength=vsnprintf(msgBuffer,0,msg,args);
  msgBuffer=malloc(strLength + 1);
  vsprintf(msgBuffer, msg, args);

  errorObj->errorMsg=msgBuffer;
  errorObj->errorCode=errCode;

  va_end(args);
  Throw(errorObj);
}



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

ListElement *keyFind(LinkedList *list, void *key, int(*compare)(void *,void *)){
  char *errMsg;

  if(list==NULL || compare==NULL){
    return NULL;
  }
  else{
    ListElement *elemPtr;
    elemPtr=list->head;

    if(key==NULL || (compare(elemPtr ->value , key)==-1)){
      return NULL;
    }

    else{
      elemPtr=elemPtr->next;
      //if they are not the same then continue looping
      while (compare(((IdentifierToken *)(((OperatorToken *)(elemPtr ->value))->token[0]))->name , key)==1){
        elemPtr =elemPtr->next;
        if (((Token *)(elemPtr->value))->type==TOKEN_OPERATOR_TYPE && strcmp(((OperatorToken *)(elemPtr->value))->symbol,"}")==0){
          errMsg="ERROR[%d]:Key not Found.Finding 'Key'=>'%s'.";
          printf(errMsg,ERR_KEY_NOT_FOUND,(char *)(key));
          throwError(ERR_KEY_NOT_FOUND,errMsg,ERR_KEY_NOT_FOUND,(char *)(key));
        }
      }
      printf("Finding 'Value' for 'Key'='%s'\n",(char *)(key));
      return elemPtr;
    }
  }
}

Token *getElementValue(ListElement *findKey){
  Token *leftToken=((OperatorToken *)(findKey->value))->token[0];
  Token *rightToken=((OperatorToken *)(findKey->value))->token[1];

  if(findKey==NULL){
    return NULL;
  }
  else{
    if(rightToken->type==TOKEN_STRING_TYPE){
      printf("The 'Value' for '%s' is '%s'\n",((IdentifierToken *)leftToken)->name,((StringToken *)rightToken)->name);
    }
    else if(rightToken->type==TOKEN_INTEGER_TYPE){
      printf("The 'Value' for '%s' is '%d'\n",((IdentifierToken *)leftToken)->name,((IntegerToken *)rightToken)->value);
    }
    return rightToken;
  }
}

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

Iterator *createIterator(LinkedList *list){
  Iterator *iter=malloc(sizeof(Iterator));

  if(list==NULL){
    return NULL;
  }
  else{
    iter->current=list->head;
    return iter;
  }
}

Iterator *iteratorGetNext(Iterator *iter){
  iter->current=iter->current->next;
  return iter;
}#include "ErrorObject.h"
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
            errMsg="ERROR[%d]:Expected an Identifier for 'Key' but get '%s'.";
            printf(errMsg,ERR_EXPECT_IDEN,opCurrentTok);
            throwError(ERR_EXPECT_IDEN,errMsg,ERR_EXPECT_IDEN,opCurrentTok);
          }
          else if(token-> type==TOKEN_IDENTIFIER_TYPE || token-> type==TOKEN_STRING_TYPE){
            printf("\n");
            errMsg="ERROR[%d]:Expected an Identifier for 'Key' but get '%s'.";
            printf(errMsg,ERR_EXPECT_IDEN,strCurrentTok);
            throwError(ERR_EXPECT_IDEN,errMsg,ERR_EXPECT_IDEN,strCurrentTok);
          }
          else if (token-> type==TOKEN_INTEGER_TYPE){
            printf("\n");
            errMsg="ERROR[%d]:Expected an Identifier for 'Key' but get '%d'.";
            printf(errMsg,ERR_EXPECT_IDEN,intCurrentTok);
            throwError(ERR_EXPECT_IDEN,errMsg,ERR_EXPECT_IDEN,intCurrentTok);
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
            errMsg="ERROR[%d]:Expected ':' after 'Key' but get '%s'.\n\n'%s'%s\n%*s^\n";
            printf(errMsg,ERR_EXPECT_OPERATOR,opCurrentTok,idenLeftTok,opCurrentTok,(leftToken->length)+2,"");
            throwError(ERR_EXPECT_OPERATOR,errMsg,ERR_EXPECT_OPERATOR,opCurrentTok,idenLeftTok,opCurrentTok,(leftToken->length)+2,"");
          }
          else if(token-> type==TOKEN_IDENTIFIER_TYPE || token-> type==TOKEN_STRING_TYPE){
            printf("\n");
            errMsg="ERROR[%d]:Expected ':' after 'Key' but get '%s'.\n\n'%s''%s'\n%*s^\n";
            printf(errMsg,ERR_EXPECT_OPERATOR,strCurrentTok,idenLeftTok,strCurrentTok,(leftToken->length)+2,"");
            throwError(ERR_EXPECT_OPERATOR,errMsg,ERR_EXPECT_OPERATOR,strCurrentTok,idenLeftTok,strCurrentTok,(leftToken->length)+2,"");
          }
          else if (token-> type==TOKEN_INTEGER_TYPE){
            printf("\n");
            errMsg="ERROR[%d]:Expected ':' after 'Key' but get '%d'.\n\n'%s'%d\n%*s^\n";
            printf(errMsg,ERR_EXPECT_OPERATOR,intCurrentTok,idenLeftTok,intCurrentTok,(leftToken->length)+2,"");
            throwError(ERR_EXPECT_OPERATOR,errMsg,ERR_EXPECT_OPERATOR,intCurrentTok,idenLeftTok,intCurrentTok,(leftToken->length)+2,"");
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
            DECLARE_CURRENT_PTR;
            DECLARE_LEFT_PTR;
            printf("\n");
            errMsg="ERROR[%d]:Expected an Integer/String/Float/{ for 'Value' but get %s.\n\n'%s'%s%s\n%*s^\n";
            printf(errMsg,ERR_ILLEGAL_VALUE,opCurrentTok,idenLeftTok,":",opCurrentTok,(leftToken->length)+3,"");
            throwError(ERR_ILLEGAL_VALUE,errMsg,ERR_ILLEGAL_VALUE,opCurrentTok,idenLeftTok,":",opCurrentTok,(leftToken->length)+3,"");
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

LinkedList *createLinkedList(){
  LinkedList *list;
  list = malloc(sizeof(LinkedList));
  assert(list != NULL);

  list-> head   = NULL;
  list-> tail   = NULL;
  list-> length = 0;
  list-> state  = WAIT_FOR_TOKEN;

  return list;
}

ListElement *createListElement(void *value){

  ListElement *newNode= malloc(sizeof(ListElement));
  assert(newNode != NULL);
  if(value==NULL)
    return NULL;
  newNode -> value = value;
  newNode -> next = NULL;

  return newNode;
}

void addLast(ListElement *newEle,LinkedList *list ){

  Iterator *iter;

  if(newEle==NULL || list==NULL){}

  else {
    iter=createIterator(list);
    if(iter->current == NULL){
      list->head=newEle;
      list->tail=list->head;
    }
    else{
      iter->current=list->tail;
      iter=iteratorGetNext(iter);
      iter->current=newEle;
      list->tail->next=iter->current;
      list->tail=list->tail->next;
    }
    (list->length)++;
  }
}


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

#include <stdio.h>
#include <assert.h>


int intCompare(void *first, void *second){

  if(first==NULL||second==NULL){
    return -1;
  }
  int *ptr=(int *)(first);
  int *ptr1=(int *)(second);

  if(*ptr==*ptr1){
    return 0;
  }
  else{
    return 1;
  }
}

int strCompare (void *first, void *second){

  if(first==NULL||second==NULL){
    return -1;
  }
  char *ptr=(char *)(first);
  char *ptr1=(char *)(second);

  if(strcmp(ptr,ptr1)==0){
    return 0;
  }
  else{
    return 1;
  }

}#include "ErrorObject.h"
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