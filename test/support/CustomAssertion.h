#ifndef CustomAssertion_H
#define CustomAssertion_H

#include "unity.h"
#include "Token.h"
#include "JSON.h"
#include "LinkedList.h"

#define TEST_ASSERT_TREE(Key, Value, actual)      \
                    customTestAssertTree(Key, Value, actual, __LINE__)

#define CUSTOM_TEST_FAIL(msg,...)              {                                                                              \
                                               char buffer[256];                                                              \
                                               sprintf(buffer,msg, ## __VA_ARGS__);                                           \
                                               UNITY_TEST_FAIL(__LINE__, buffer); \
                                               }
                    
                    
void customTestAssertTree(void *Key, void *Value,Iterator *actual, int lineNo);


#endif // CustomAssertion_H
