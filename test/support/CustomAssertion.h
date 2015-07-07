#ifndef CustomAssertion_H
#define CustomAssertion_H

#include "unity.h"
#include "Coordinate.h"

#define CUSTOM_TEST_FAIL(msg,...)              {                                                                              \
                                               char buffer[256];                                                              \
                                               sprintf(buffer,msg, ## __VA_ARGS__);                                           \
                                               UNITY_TEST_FAIL(__LINE__, buffer); \
                                               }

#define _TEST_ASSERT_EQUAL(expected ,actual)   if(expected != actual)                                                          \
                                               {                                                                               \
                                                  CUSTOM_TEST_FAIL("I expexted %d,but I see %d", expected,actual);              \
                                               }

#define TEST_ASSERT_COORDINATE(within, x, y, z,actual)      \
                    customTestAssertCoordinate(within, x, y, z, actual, __LINE__)

   #define SILLY

void customTestAssertCoordinate(float within,
                           float x,
                           float y,
                           float z,
                           Coordinate actual,
                           int lineNo);


#endif // CustomAssertion_H
