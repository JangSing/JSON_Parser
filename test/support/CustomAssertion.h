#ifndef CustomAssertion_H
#define CustomAssertion_H

#include "unity.h"
#include "Token.h"
#include "JSON.h"
#include "LinkedList.h"
#include "IteratorFunction.h"

#define TEST_ASSERT_KEY_VALUE(key, value, actual)      \
                    customTestAssertKeyValue(key, value, actual, __LINE__)

#define TEST_ASSERT_KEY(key, actual)      \
                    customTestAssertKey(key, actual, __LINE__)

#define TEST_ASSERT_VALUE(value, actual)      \
                    customTestAssertValue(value, actual, __LINE__)

#define CUSTOM_TEST_FAIL(msg,...)              {                                                                              \
                                               char buffer[256];                                                              \
                                               sprintf(buffer,msg, ## __VA_ARGS__);                                           \
                                               UNITY_TEST_FAIL(lineNo, buffer);                                               \
                                               }

#define TEST_FAIL_JSON(msg,...)                {                                                                              \
                                               char buffer[256];                                                              \
                                               sprintf(buffer,msg, ## __VA_ARGS__);                                           \
                                               UNITY_TEST_FAIL(__LINE__, buffer);                                             \
                                               }


void customTestAssertKeyValue(void *key, void *value, ListElement *actual, int lineNo);

void customTestAssertKey(void *key, ListElement *actual, int lineNo);

void customTestAssertValue(void *value, ListElement *actual, int lineNo);


#endif // CustomAssertion_H
