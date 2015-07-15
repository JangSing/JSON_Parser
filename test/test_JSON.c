#include "unity.h"
#include "mock_Token.h"
#include "LinkedList.h"
#include "JSON.h"
#include "compareFunction.h"
#include "IteratorFunction.h"

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

void setUp()
{
}

void tearDown()
{
}

void test_getToken()
{

  // Token *Token;
  Token *INT=malloc(sizeof(Token));
  Token *FLOAT=malloc(sizeof(Token));
  Token *IDEN=malloc(sizeof(Token));
  Token *STR=malloc(sizeof(Token));
  Token *OPE=malloc(sizeof(Token));

  ((IntegerToken *)(INT))-> value=100;
  ((FloatToken *)(FLOAT))-> value=12.34;
  ((IdentifierToken *)(IDEN))-> name="JangSing";
  ((StringToken *)(STR))-> name="Wong";
  ((operatorToken *)(OPE))-> symbol="{";

	getToken_ExpectAndReturn(INT);
	getToken_ExpectAndReturn(FLOAT);
	getToken_ExpectAndReturn(IDEN);
	getToken_ExpectAndReturn(STR);
	getToken_ExpectAndReturn(OPE);

  TEST_ASSERT_EQUAL(100,((IntegerToken *)(getToken()))-> value);
  TEST_ASSERT_EQUAL_FLOAT(12.34,((FloatToken *)(getToken()))-> value);
  TEST_ASSERT_EQUAL_STRING("JangSing",((IdentifierToken *)(getToken()))-> name);
  TEST_ASSERT_EQUAL_STRING("Wong",((StringToken *)(getToken()))-> name);
  TEST_ASSERT_EQUAL_STRING("{",((operatorToken *)(getToken()))-> symbol);
}

void test_createListElement()
{
  ListElement *newNode;
  IntegerToken *intTok;

  intTok=createIntegerToken(123);
  newNode = createListElement(intTok);

  TEST_ASSERT_NOT_NULL(newNode);
  TEST_ASSERT_NOT_NULL(newNode->value);

  TEST_ASSERT_EQUAL(123,intTok->value);

  TEST_ASSERT_EQUAL(123,((IntegerToken *)(newNode->value))->value);
  TEST_ASSERT_EQUAL(TOKEN_INTEGER_TYPE,((IntegerToken *)(newNode->value))->type);
}

/**
 *  {
 *    "NAME1":"JS",
 *    "NAME2":"STEVEN"
 *  }
 */
void test_Simple_JSON_List()
{
  LinkedList *list;

  Token *openBrace=createOperatorToken("{");
  Token *closeBrace=createOperatorToken("}");
  Token *coma=(Token*)createOperatorToken(",");
  Token *colon=(Token*)createOperatorToken(":");
  Token *key0=(Token*)createIdentifierToken("NAME1");
  Token *key1=(Token*)createIdentifierToken("AGE");
  Token *value0=(Token*)createStringToken("JS");
  Token *value1=(Token*)createIntegerToken(20);

  getToken_ExpectAndReturn(openBrace);    //"{"
  getToken_ExpectAndReturn(key0);         //"NAME1"
  getToken_ExpectAndReturn(colon);        //":"
  getToken_ExpectAndReturn(value0);       //"JS"
  getToken_ExpectAndReturn(coma);         //","
  getToken_ExpectAndReturn(key1);         //"AGE"
  getToken_ExpectAndReturn(colon);        //":"
  getToken_ExpectAndReturn(value1);       //20
  getToken_ExpectAndReturn(closeBrace);   //"}"

  getToken_ExpectAndReturn(NULL);

  list=jsonParse();

  TEST_ASSERT_EQUAL(END,list->state);

  operatorToken *token1 = ((operatorToken *)(list->head->value));
  operatorToken *token2 = ((operatorToken *)(list->head->next->value));
  operatorToken *token3 = ((operatorToken *)(list->head->next->next->value));
  operatorToken *token4 = ((operatorToken *)(list->head->next->next->next->value));

  TEST_ASSERT_EQUAL_STRING("{",token1->symbol);
  TEST_ASSERT_EQUAL_STRING(":",token2->symbol);
  TEST_ASSERT_EQUAL_STRING("NAME1",((IdentifierToken *)(token2->token[0]))->name);
  TEST_ASSERT_EQUAL_STRING("JS",((StringToken *)(token2->token[1]))->name);
  TEST_ASSERT_EQUAL_STRING(":",token3->symbol);
  TEST_ASSERT_EQUAL_STRING("AGE",((IdentifierToken *)(token3->token[0]))->name);
  TEST_ASSERT_EQUAL(20,((IntegerToken *)(token3->token[1]))->value);
  TEST_ASSERT_EQUAL_STRING("}",token4->symbol);
}

/**
 *{
 *  "NAME1":"JS",
 *  "AGE"  :{ "NAME2":"STEVEN",
 *            "NAME3":"YEN"}
 *}
 */
void test_JSON_List_with_Recursion_JSON_List()
{
  LinkedList *list;

  Token *openBrace=createOperatorToken("{");
  Token *closeBrace=createOperatorToken("}");
  Token *coma=(Token*)createOperatorToken(",");
  Token *colon=(Token*)createOperatorToken(":");
  Token *key0=(Token*)createIdentifierToken("NAME1");
  Token *key1=(Token*)createIdentifierToken("AGE");
  Token *key2=(Token*)createIdentifierToken("NAME2");
  Token *key3=(Token*)createIdentifierToken("NAME3");
  Token *value0=(Token*)createStringToken("JS");
  Token *value1=(Token*)createStringToken("STEVEN");
  Token *value2=(Token*)createStringToken("Yen");

  getToken_ExpectAndReturn(openBrace);    //"{"
  getToken_ExpectAndReturn(key0);         //"NAME1"
  getToken_ExpectAndReturn(colon);        //":"
  getToken_ExpectAndReturn(value0);       //"JS"
  getToken_ExpectAndReturn(coma);         //","
  getToken_ExpectAndReturn(key1);         //"AGE"
  getToken_ExpectAndReturn(colon);        //":"
  getToken_ExpectAndReturn(openBrace);    //"{"
  getToken_ExpectAndReturn(key2);         //"NAME2"
  getToken_ExpectAndReturn(colon);        //":"
  getToken_ExpectAndReturn(value1);       //"STEVEN"
  getToken_ExpectAndReturn(coma);         //","
  getToken_ExpectAndReturn(key3);         //"NAME3"
  getToken_ExpectAndReturn(colon);        //":"
  getToken_ExpectAndReturn(value2);       //"Yen"
  getToken_ExpectAndReturn(closeBrace);   //"}"
  getToken_ExpectAndReturn(closeBrace);   //"}"
  getToken_ExpectAndReturn(NULL);

  list=jsonParse();

  TEST_ASSERT_EQUAL(END,list->state);

  operatorToken *token1 = ((operatorToken *)(list->head->value));
  operatorToken *token2 = ((operatorToken *)(list->head->next->value));
  operatorToken *token3 = ((operatorToken *)(list->head->next->next->value));
  operatorToken *token4 = ((operatorToken *)(list->head->next->next->next->value));

  TEST_ASSERT_EQUAL_STRING("{",token1->symbol);
  TEST_ASSERT_EQUAL_STRING(":",token2->symbol);
  TEST_ASSERT_EQUAL_STRING("NAME1",((IdentifierToken *)(token2->token[0]))->name);
  TEST_ASSERT_EQUAL_STRING("JS",((StringToken *)(token2->token[1]))->name);
  TEST_ASSERT_EQUAL_STRING(":",token3->symbol);
  TEST_ASSERT_EQUAL_STRING("AGE",((IdentifierToken *)(token3->token[0]))->name);

  operatorToken *Token3Token1 = ((operatorToken *)(((LinkedList *)(token3->token[1]))->head->value));
  operatorToken *Token3Token2 = ((operatorToken *)(((LinkedList *)(token3->token[1]))->head->next->value));
  operatorToken *Token3Token3 = ((operatorToken *)(((LinkedList *)(token3->token[1]))->head->next->next->value));
  operatorToken *Token3Token4 = ((operatorToken *)(((LinkedList *)(token3->token[1]))->head->next->next->next->value));

  TEST_ASSERT_EQUAL_STRING("{", Token3Token1->symbol);
  TEST_ASSERT_EQUAL_STRING(":", Token3Token2->symbol);
  TEST_ASSERT_EQUAL_STRING("NAME2", ((IdentifierToken *)(Token3Token2->token[0]))->name);
  TEST_ASSERT_EQUAL_STRING("STEVEN",((StringToken *)(Token3Token2->token[1]))->name);
  TEST_ASSERT_EQUAL_STRING(":", Token3Token3->symbol);
  TEST_ASSERT_EQUAL_STRING("NAME3", ((IdentifierToken *)(Token3Token3->token[0]))->name);
  TEST_ASSERT_EQUAL_STRING("Yen",((StringToken *)(Token3Token3->token[1]))->name);
  TEST_ASSERT_EQUAL_STRING("}", Token3Token4->symbol);
  TEST_ASSERT_EQUAL_STRING("}",token4->symbol);
}

/**
 *  {
 *    "NAME1":"JS",
 *    "NAME2":"STEVEN"
 *  }
 */
void test_Finding_Element_in_Simple_JSON_List()
{
  LinkedList *list;
  ListElement *findEle;

  Token *openBrace=createOperatorToken("{");
  Token *closeBrace=createOperatorToken("}");
  Token *coma=(Token*)createOperatorToken(",");
  Token *colon=(Token*)createOperatorToken(":");
  Token *key0=(Token*)createIdentifierToken("NAME1");
  Token *key1=(Token*)createIdentifierToken("AGE");
  Token *value0=(Token*)createStringToken("JS");
  Token *value1=(Token*)createIntegerToken(20);

  getToken_ExpectAndReturn(openBrace);    //"{"
  getToken_ExpectAndReturn(key0);         //"NAME1"
  getToken_ExpectAndReturn(colon);        //":"
  getToken_ExpectAndReturn(value0);       //"JS"
  getToken_ExpectAndReturn(coma);         //","
  getToken_ExpectAndReturn(key1);         //"AGE"
  getToken_ExpectAndReturn(colon);        //":"
  getToken_ExpectAndReturn(value1);       //20
  getToken_ExpectAndReturn(closeBrace);   //"}"

  getToken_ExpectAndReturn(NULL);

  list=jsonParse();

  findEle=(ListElement *)(keyFind(list, "AGE", strCompare));

  // printf("value=%s",((IdentifierToken *)((operatorToken *)(findEle->value))->token[0])->name);
  // TEST_ASSERT_EQUAL("AGE",((IdentifierToken *)((operatorToken *)(findEle->value))->token[0])->name);
}

/**
 *{
 *  "NAME1":"JS",
 *  "AGE"  :{ "NAME2":"STEVEN",
 *            "NAME3":"YEN"}
 *}
 */
void test_Finding_Element_in_Recursion_JSON_List()
{
  LinkedList *list;
  ListElement *findKey;
  Token *findVal;

  Token *openBrace=createOperatorToken("{");
  Token *closeBrace=createOperatorToken("}");
  Token *coma=(Token*)createOperatorToken(",");
  Token *colon=(Token*)createOperatorToken(":");
  Token *key0=(Token*)createIdentifierToken("NAME1");
  Token *key1=(Token*)createIdentifierToken("AGE");
  Token *key2=(Token*)createIdentifierToken("NAME2");
  Token *key3=(Token*)createIdentifierToken("NAME3");
  Token *value0=(Token*)createStringToken("JS");
  Token *value1=(Token*)createStringToken("STEVEN");
  Token *value2=(Token*)createStringToken("Yen");

  getToken_ExpectAndReturn(openBrace);    //"{"
  getToken_ExpectAndReturn(key0);         //"NAME1"
  getToken_ExpectAndReturn(colon);        //":"
  getToken_ExpectAndReturn(value0);       //"JS"
  getToken_ExpectAndReturn(coma);         //","
  getToken_ExpectAndReturn(key1);         //"AGE"
  getToken_ExpectAndReturn(colon);        //":"
  getToken_ExpectAndReturn(openBrace);    //"{"
  getToken_ExpectAndReturn(key2);         //"NAME2"
  getToken_ExpectAndReturn(colon);        //":"
  getToken_ExpectAndReturn(value1);       //"STEVEN"
  getToken_ExpectAndReturn(coma);         //","
  getToken_ExpectAndReturn(key3);         //"NAME3"
  getToken_ExpectAndReturn(colon);        //":"
  getToken_ExpectAndReturn(value2);       //"Yen"
  getToken_ExpectAndReturn(closeBrace);   //"}"
  getToken_ExpectAndReturn(closeBrace);   //"}"
  getToken_ExpectAndReturn(NULL);

  list=jsonParse();

  findKey=(ListElement *)(keyFind(list, "AGE", strCompare));
  findKey=(ListElement *)(keyFind((LinkedList *)(((operatorToken *)(findKey->value))->token[1]), "NAME3", strCompare));
  findVal=(Token *)(getElementValue(findKey));

  printf("key=%s\n",((IdentifierToken *)((operatorToken *)(findKey->value))->token[0])->name);
  printf("value=%s",((StringToken *)(findVal))->name);
  // TEST_ASSERT_EQUAL("AGE",((IdentifierToken *)((operatorToken *)(findEle->value))->token[0])->name);
}

void test_iteratorGetNext()
{
  int value[]={1,3,4};

  LinkedList *ptr;
  Iterator *iter;

  ptr=createLinkedList();

  addLast(createListElement(&value[0]),ptr);
  addLast(createListElement(&value[1]),ptr);
  addLast(createListElement(&value[2]),ptr);

  iter=createIterator(ptr);

  TEST_ASSERT_NOT_NULL(iter);
  TEST_ASSERT_NOT_NULL(iter->current->next);
  TEST_ASSERT_EQUAL(1,*((int *)(iter->current->value)));
  iter=iteratorGetNext(iter);

  TEST_ASSERT_NOT_NULL(iter);
  TEST_ASSERT_NOT_NULL(iter->current->next);
  TEST_ASSERT_EQUAL(3,*((int *)(iter->current->value)));
  iter=iteratorGetNext(iter);

  TEST_ASSERT_EQUAL(4,*((int *)(iter->current->value)));
}

void test_iteratorGetNext_for_Simple_List()
{
  LinkedList *list;
  Iterator *iter;

  Token *openBrace=createOperatorToken("{");
  Token *closeBrace=createOperatorToken("}");
  Token *coma=(Token*)createOperatorToken(",");
  Token *colon=(Token*)createOperatorToken(":");
  Token *key0=(Token*)createIdentifierToken("NAME1");
  Token *key1=(Token*)createIdentifierToken("AGE");
  Token *value0=(Token*)createStringToken("JS");
  Token *value1=(Token*)createIntegerToken(20);

  getToken_ExpectAndReturn(openBrace);    //"{"
  getToken_ExpectAndReturn(key0);         //"NAME1"
  getToken_ExpectAndReturn(colon);        //":"
  getToken_ExpectAndReturn(value0);       //"JS"
  getToken_ExpectAndReturn(coma);         //","
  getToken_ExpectAndReturn(key1);         //"AGE"
  getToken_ExpectAndReturn(colon);        //":"
  getToken_ExpectAndReturn(value1);       //20
  getToken_ExpectAndReturn(closeBrace);   //"}"
  getToken_ExpectAndReturn(NULL);

  list=jsonParse();


  TEST_ASSERT_EQUAL(END,list->state);

  iter=createIterator(list);
  TEST_ASSERT_EQUAL_STRING("{",((operatorToken *)(iter->current->value))->symbol);
  iter=iteratorGetNext(iter);
  TEST_ASSERT_EQUAL_STRING(":",((operatorToken *)(iter->current->value))->symbol);
  iter=iteratorGetNext(iter);
  TEST_ASSERT_EQUAL_STRING(":",((operatorToken *)(iter->current->value))->symbol);
  iter=iteratorGetNext(iter);
  TEST_ASSERT_EQUAL_STRING("}",((operatorToken *)(iter->current->value))->symbol);

  // operatorToken *Token = ((operatorToken *)(tempToken->value));

  // operatorToken *token2 = ((operatorToken *)(list->head->next->value));
  // operatorToken *token3 = ((operatorToken *)(list->head->next->next->value));
  // operatorToken *token4 = ((operatorToken *)(list->head->next->next->next->value));

  // TEST_ASSERT_EQUAL_STRING(":",token2->symbol);
  // TEST_ASSERT_EQUAL_STRING("NAME1",((IdentifierToken *)(token2->token[0]))->name);
  // TEST_ASSERT_EQUAL_STRING("JS",((StringToken *)(token2->token[1]))->name);
  // TEST_ASSERT_EQUAL_STRING(":",token3->symbol);
  // TEST_ASSERT_EQUAL_STRING("AGE",((IdentifierToken *)(token3->token[0]))->name);
  // TEST_ASSERT_EQUAL(20,((IntegerToken *)(token3->token[1]))->value);
  // TEST_ASSERT_EQUAL_STRING("}",token4->symbol);
}

