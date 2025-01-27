#include <gtest/gtest.h>

#include "fintamath/expressions/Expression.hpp"
#include "fintamath/expressions/ExpressionUtils.hpp"
#include "fintamath/functions/logarithms/Log.hpp"

using namespace fintamath;

TEST(LogExpressionTests, getTypeIdTest) {
  EXPECT_EQ(makeExpr(Log(), Integer(0), Integer(0))->getTypeId(), MathObjectTypeId(MathObjectType::LogExpression));
}
