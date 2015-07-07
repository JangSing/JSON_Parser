#include "CustomAssertion.h"
#include "Coordinate.h"


void customTestAssertCoordinate(float within,
                           float x,
                           float y,
                           float z,
                           Coordinate actual,
                           int lineNo){

  TEST_ASSERT_FLOAT_WITHIN(within, x, actual.x);
  TEST_ASSERT_FLOAT_WITHIN(within, y, actual.y);
  TEST_ASSERT_FLOAT_WITHIN(within, z, actual.z);
}