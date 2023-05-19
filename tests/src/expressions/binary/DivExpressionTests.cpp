#include <gtest/gtest.h>

#include "fintamath/expressions/Expression.hpp"
#include "fintamath/expressions/ExpressionUtils.hpp"
#include "fintamath/functions/arithmetic/Div.hpp"

using namespace fintamath;

TEST(DivExpressionTests, getTypeIdTest) {
  EXPECT_EQ(makeExpr(Div(), Integer(0).clone(), Integer(0).clone())->getTypeId(),
            MathObjectTypeId(MathObjectType::DivExpression));
}