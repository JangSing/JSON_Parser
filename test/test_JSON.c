#include "unity.h"
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#include "mock_Token.h"
#include "LinkedList.h"
#include "JSON.h"

void setUp(void)
{
}

void tearDown(void)
{
}

void test_getToken()
{

  // Token *token;
  Token *INT=malloc(sizeof(Token));
  Token *FLOAT=malloc(sizeof(Token));
  Token *IDEN=malloc(sizeof(Token));
  Token *STR=malloc(sizeof(Token));
  Token *OPE=malloc(sizeof(Token));

  ((IntegerToken *)(INT))-> value=100;
  ((FloatToken *)(FLOAT))-> value=12.34;
  ((IdentifierToken *)(IDEN))-> name="JangSing";
  ((StringToken *)(STR))-> name="Wong";
  ((OperatorToken *)(OPE))-> symbol="{";

	getToken_ExpectAndReturn(INT);
	getToken_ExpectAndReturn(FLOAT);
	getToken_ExpectAndReturn(IDEN);
	getToken_ExpectAndReturn(STR);
	getToken_ExpectAndReturn(OPE);

  TEST_ASSERT_EQUAL(100,((IntegerToken *)(getToken()))-> value);
  TEST_ASSERT_EQUAL_FLOAT(12.34,((FloatToken *)(getToken()))-> value);
  TEST_ASSERT_EQUAL_STRING("JangSing",((IdentifierToken *)(getToken()))-> name);
  TEST_ASSERT_EQUAL_STRING("Wong",((StringToken *)(getToken()))-> name);
  TEST_ASSERT_EQUAL_STRING("{",((OperatorToken *)(getToken()))-> symbol);
}

void test_createListElement()
{
  ListElement *NewNode;
  IntegerToken *IntTok;

  IntTok=createIntegerToken(123);
  NewNode = createListElement(IntTok);

  TEST_ASSERT_NOT_NULL(NewNode);
  TEST_ASSERT_NOT_NULL(NewNode->value);

  TEST_ASSERT_EQUAL(123,IntTok->value);

  TEST_ASSERT_EQUAL(123,((IntegerToken *)(NewNode->value))->value);
  TEST_ASSERT_EQUAL(TOKEN_INTEGER_TYPE,((IntegerToken *)(NewNode->value))->type);
}

/**
 *  {
 *    "NAME1":"JS",
 *    "NAME2":"STEVEN"
 *  }
 */
void test_Simple_JSON_List()
{
  LinkedList *List;

  Token *OpenBrace=createOperatorToken("{");
  Token *CloseBrace=createOperatorToken("}");
  Token *Coma=(Token*)createOperatorToken(",");
  Token *Colon=(Token*)createOperatorToken(":");
  Token *Key0=(Token*)createIdentifierToken("NAME1");
  Token *Key1=(Token*)createIdentifierToken("AGE");
  Token *Value0=(Token*)createStringToken("JS");
  Token *Value1=(Token*)createIntegerToken(20);

  getToken_ExpectAndReturn(OpenBrace);    //"{"
  getToken_ExpectAndReturn(Key0);         //"NAME1"
  getToken_ExpectAndReturn(Colon);        //":"
  getToken_ExpectAndReturn(Value0);       //"JS"
  getToken_ExpectAndReturn(Coma);         //","
  getToken_ExpectAndReturn(Key1);         //"AGE"
  getToken_ExpectAndReturn(Colon);        //":"
  getToken_ExpectAndReturn(Value1);       //20
  getToken_ExpectAndReturn(CloseBrace);   //"}"

  getToken_ExpectAndReturn(NULL);

  List=DetermineState();

  OperatorToken *Token1 = ((OperatorToken *)(List->head->value));
  OperatorToken *Token2 = ((OperatorToken *)(List->head->next->value));
  OperatorToken *Token3 = ((OperatorToken *)(List->head->next->next->value));
  OperatorToken *Token4 = ((OperatorToken *)(List->head->next->next->next->value));
  OperatorToken *Token5 = ((OperatorToken *)(List->head->next->next->next->next->value));

  TEST_ASSERT_EQUAL(END,List->state);
  TEST_ASSERT_EQUAL_STRING("{",Token1->symbol);
  TEST_ASSERT_EQUAL_STRING(":",Token2->symbol);
  TEST_ASSERT_EQUAL_STRING("NAME1",((IdentifierToken *)(Token2->token[0]))->name);
  TEST_ASSERT_EQUAL_STRING("JS",((StringToken *)(Token2->token[1]))->name);
  TEST_ASSERT_EQUAL_STRING(",",Token3->symbol);
  TEST_ASSERT_EQUAL_STRING(":",Token4->symbol);
  TEST_ASSERT_EQUAL_STRING("AGE",((IdentifierToken *)(Token4->token[0]))->name);
  TEST_ASSERT_EQUAL(20,((IntegerToken *)(Token4->token[1]))->value);
  TEST_ASSERT_EQUAL_STRING("}",Token5->symbol);
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
  LinkedList *List;

  Token *OpenBrace=createOperatorToken("{");
  Token *CloseBrace=createOperatorToken("}");
  Token *Coma=(Token*)createOperatorToken(",");
  Token *Colon=(Token*)createOperatorToken(":");
  Token *Key0=(Token*)createIdentifierToken("NAME1");
  Token *Key1=(Token*)createIdentifierToken("AGE");
  Token *Key2=(Token*)createIdentifierToken("NAME2");
  Token *Key3=(Token*)createIdentifierToken("NAME3");
  Token *Value0=(Token*)createStringToken("JS");
  Token *Value1=(Token*)createStringToken("STEVEN");
  Token *Value2=(Token*)createStringToken("Yen");

  getToken_ExpectAndReturn(OpenBrace);    //"{"
  getToken_ExpectAndReturn(Key0);         //"NAME1"
  getToken_ExpectAndReturn(Colon);        //":"
  getToken_ExpectAndReturn(Value0);       //"JS"
  getToken_ExpectAndReturn(Coma);         //","
  getToken_ExpectAndReturn(Key1);         //"AGE"
  getToken_ExpectAndReturn(Colon);        //":"
  getToken_ExpectAndReturn(OpenBrace);    //"{"
  getToken_ExpectAndReturn(Key2);         //"NAME2"
  getToken_ExpectAndReturn(Colon);        //":"
  getToken_ExpectAndReturn(Value1);       //"STEVEN"
  getToken_ExpectAndReturn(Coma);         //","
  getToken_ExpectAndReturn(Key3);         //"NAME3"
  getToken_ExpectAndReturn(Colon);        //":"
  getToken_ExpectAndReturn(Value2);       //"Yen"
  getToken_ExpectAndReturn(CloseBrace);   //"}"
  getToken_ExpectAndReturn(CloseBrace);   //"}"
  getToken_ExpectAndReturn(NULL);

  List=DetermineState();

  OperatorToken *Token1 = ((OperatorToken *)(List->head->value));
  OperatorToken *Token2 = ((OperatorToken *)(List->head->next->value));
  OperatorToken *Token3 = ((OperatorToken *)(List->head->next->next->value));
  OperatorToken *Token4 = ((OperatorToken *)(List->head->next->next->next->value));
  OperatorToken *Token5 = ((OperatorToken *)(List->head->next->next->next->next->value));

  TEST_ASSERT_EQUAL(END,List->state);
  TEST_ASSERT_EQUAL_STRING("{",Token1->symbol);
  TEST_ASSERT_EQUAL_STRING(":",Token2->symbol);
  TEST_ASSERT_EQUAL_STRING("NAME1",((IdentifierToken *)(Token2->token[0]))->name);
  TEST_ASSERT_EQUAL_STRING("JS",((StringToken *)(Token2->token[1]))->name);
  TEST_ASSERT_EQUAL_STRING(",",Token3->symbol);
  TEST_ASSERT_EQUAL_STRING(":",Token4->symbol);
  TEST_ASSERT_EQUAL_STRING("AGE",((IdentifierToken *)(Token4->token[0]))->name);

  OperatorToken *Token4Token1 = ((OperatorToken *)(((LinkedList *)(Token4->token[1]))->head->value));
  OperatorToken *Token4Token2 = ((OperatorToken *)(((LinkedList *)(Token4->token[1]))->head->next->value));
  OperatorToken *Token4Token3 = ((OperatorToken *)(((LinkedList *)(Token4->token[1]))->head->next->next->value));
  OperatorToken *Token4Token4 = ((OperatorToken *)(((LinkedList *)(Token4->token[1]))->head->next->next->next->value));
  OperatorToken *Token4Token5 = ((OperatorToken *)(((LinkedList *)(Token4->token[1]))->head->next->next->next->next->value));

  TEST_ASSERT_EQUAL_STRING("{", Token4Token1->symbol);
  TEST_ASSERT_EQUAL_STRING(":", Token4Token2->symbol);
  TEST_ASSERT_EQUAL_STRING("NAME2", ((IdentifierToken *)(Token4Token2->token[0]))->name);
  TEST_ASSERT_EQUAL_STRING("STEVEN",((StringToken *)(Token4Token2->token[1]))->name);
  TEST_ASSERT_EQUAL_STRING(",", Token4Token3->symbol);
  TEST_ASSERT_EQUAL_STRING(":", Token4Token4->symbol);
  TEST_ASSERT_EQUAL_STRING("NAME3", ((IdentifierToken *)(Token4Token4->token[0]))->name);
  TEST_ASSERT_EQUAL_STRING("Yen",((StringToken *)(Token4Token4->token[1]))->name);
  TEST_ASSERT_EQUAL_STRING("}", Token4Token5->symbol);
  TEST_ASSERT_EQUAL_STRING("}",Token5->symbol);
}



/**
 *  {
 *    "NAME1":"JS",
 *    "NAME2":"STEVEN"
 *  }
 */
void test_Finding_Element_in_Simple_JSON_List()
{
  LinkedList *List;
  ListElement *FindEle;

  Token *OpenBrace=createOperatorToken("{");
  Token *CloseBrace=createOperatorToken("}");
  Token *Coma=(Token*)createOperatorToken(",");
  Token *Colon=(Token*)createOperatorToken(":");
  Token *Key0=(Token*)createIdentifierToken("NAME1");
  Token *Key1=(Token*)createIdentifierToken("AGE");
  Token *Value0=(Token*)createStringToken("JS");
  Token *Value1=(Token*)createIntegerToken(20);

  getToken_ExpectAndReturn(OpenBrace);    //"{"
  getToken_ExpectAndReturn(Key0);         //"NAME1"
  getToken_ExpectAndReturn(Colon);        //":"
  getToken_ExpectAndReturn(Value0);       //"JS"
  getToken_ExpectAndReturn(Coma);         //","
  getToken_ExpectAndReturn(Key1);         //"AGE"
  getToken_ExpectAndReturn(Colon);        //":"
  getToken_ExpectAndReturn(Value1);       //20
  getToken_ExpectAndReturn(CloseBrace);   //"}"

  getToken_ExpectAndReturn(NULL);

  List=DetermineState();

  FindEle=(ListElement *)(KeyFind(List, "AGE", strCompare));

  // printf("value=%s",((IdentifierToken *)((OperatorToken *)(FindEle->value))->token[0])->name);
  // TEST_ASSERT_EQUAL("AGE",((IdentifierToken *)((OperatorToken *)(FindEle->value))->token[0])->name);
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
  LinkedList *List;
  ListElement *FindKey;
  Token *FindVal;

  Token *OpenBrace=createOperatorToken("{");
  Token *CloseBrace=createOperatorToken("}");
  Token *Coma=(Token*)createOperatorToken(",");
  Token *Colon=(Token*)createOperatorToken(":");
  Token *Key0=(Token*)createIdentifierToken("NAME1");
  Token *Key1=(Token*)createIdentifierToken("AGE");
  Token *Key2=(Token*)createIdentifierToken("NAME2");
  Token *Key3=(Token*)createIdentifierToken("NAME3");
  Token *Value0=(Token*)createStringToken("JS");
  Token *Value1=(Token*)createStringToken("STEVEN");
  Token *Value2=(Token*)createStringToken("Yen");

  getToken_ExpectAndReturn(OpenBrace);    //"{"
  getToken_ExpectAndReturn(Key0);         //"NAME1"
  getToken_ExpectAndReturn(Colon);        //":"
  getToken_ExpectAndReturn(Value0);       //"JS"
  getToken_ExpectAndReturn(Coma);         //","
  getToken_ExpectAndReturn(Key1);         //"AGE"
  getToken_ExpectAndReturn(Colon);        //":"
  getToken_ExpectAndReturn(OpenBrace);    //"{"
  getToken_ExpectAndReturn(Key2);         //"NAME2"
  getToken_ExpectAndReturn(Colon);        //":"
  getToken_ExpectAndReturn(Value1);       //"STEVEN"
  getToken_ExpectAndReturn(Coma);         //","
  getToken_ExpectAndReturn(Key3);         //"NAME3"
  getToken_ExpectAndReturn(Colon);        //":"
  getToken_ExpectAndReturn(Value2);       //"Yen"
  getToken_ExpectAndReturn(CloseBrace);   //"}"
  getToken_ExpectAndReturn(CloseBrace);   //"}"
  getToken_ExpectAndReturn(NULL);

  List=DetermineState();

  FindKey=(ListElement *)(KeyFind(List, "AGE", strCompare));
  FindKey=(ListElement *)(KeyFind((LinkedList *)(((OperatorToken *)(FindKey->value))->token[1]), "NAME3", strCompare));
  FindVal=(Token *)(getElementValue(FindKey));

  printf("Key=%s\n",((IdentifierToken *)((OperatorToken *)(FindKey->value))->token[0])->name);
  printf("value=%s",((StringToken *)(FindVal))->name);
  // TEST_ASSERT_EQUAL("AGE",((IdentifierToken *)((OperatorToken *)(FindEle->value))->token[0])->name);
}

