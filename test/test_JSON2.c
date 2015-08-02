#include "unity.h"
#include "mock_Token.h"
#include "ErrorObject.h"
#include "CException.h"
#include "compareFunction.h"
#include "createTokenType.h"
#include "FindElementFunction.h"
#include "IteratorFunction.h"
#include "JSON.h"
#include "LinkedList.h"
#include "CustomAssertion.h"

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

void setUp()
{
}

void tearDown()
{
}

/**
 * Test Complex JsonList
 *
 *  {
 *    "NAME1":"JS",
 *    "AGE"  :{ "NAME2":"STEVEN",
 *              "NAME3":{ "NAME4":"ABU" }
 *            },
 *    "ADD"  : 30          
 *  }
 */
void test_Complex_Json_List()
{
  JsonObject *jsonObj;
  Token *jsonTok;
  ErrorObject *err;

  TOKEN_DECLARE;

  getToken_ExpectAndReturn(openBrace0);    //"{"
  getToken_ExpectAndReturn(NAME1);         //"NAME1"
  getToken_ExpectAndReturn(colon0);        //":"
  getToken_ExpectAndReturn(JS);            //"JS"
  getToken_ExpectAndReturn(coma0);         //","
  getToken_ExpectAndReturn(AGE);           //"AGE"
  getToken_ExpectAndReturn(colon1);        //":"
  getToken_ExpectAndReturn(openBrace1);    //"{"
  getToken_ExpectAndReturn(NAME2);         //"NAME2"
  getToken_ExpectAndReturn(colon2);        //":"
  getToken_ExpectAndReturn(STEVEN);        //"STEVEN"
  getToken_ExpectAndReturn(coma1);         //","
  getToken_ExpectAndReturn(NAME3);         //"NAME3"
  getToken_ExpectAndReturn(colon3);        //":"
  getToken_ExpectAndReturn(openBrace2);    //"{"
  getToken_ExpectAndReturn(NAME4);         //"NAME4"
  getToken_ExpectAndReturn(colon4);        //":"
  getToken_ExpectAndReturn(ABU);           //"ABU"
  getToken_ExpectAndReturn(closeBrace0);   //"}"
  getToken_ExpectAndReturn(closeBrace1);   //"}"
  getToken_ExpectAndReturn(coma2);         //","
  getToken_ExpectAndReturn(ADD);           //"ADD"
  getToken_ExpectAndReturn(colon5);        //":"
  getToken_ExpectAndReturn(int30);         //"30"
  getToken_ExpectAndReturn(closeBrace2);   //"}"
  getToken_ExpectAndReturn(NULL);

  jsonObj=createJsonObject();
  Try{
    jsonTok=jsonParse(jsonObj);
  }Catch(err){
    TEST_FAIL_JSON("unexpected error occurred =>'%s'",err->errorMsg);
    free(err);
  }

  free(jsonObj);
  free(jsonTok);

  TOKEN_FREE;
}

 
 