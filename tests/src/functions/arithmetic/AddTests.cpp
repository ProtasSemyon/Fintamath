#include "gtest/gtest.h"

#include "fintamath/functions/arithmetic/Add.hpp"

#include "fintamath/exceptions/InvalidInputException.hpp"
#include "fintamath/functions/arithmetic/Sub.hpp"
#include "fintamath/functions/arithmetic/UnaryPlus.hpp"
#include "fintamath/literals/Boolean.hpp"
#include "fintamath/literals/Variable.hpp"
#include "fintamath/numbers/Rational.hpp"

using namespace fintamath;

const Add f;

TEST(AddTests, toStringTest) {
  EXPECT_EQ(f.toString(), "+");
}

TEST(AddTests, getFunctionTypeTest) {
  EXPECT_EQ(f.getFunctionType(), IFunction::Type::Binary);
}

TEST(AddTests, getOperatorPriorityTest) {
  EXPECT_EQ(f.getOperatorPriority(), IOperator::Priority::Addition);
}

TEST(AddTests, callTest) {
  EXPECT_EQ(f(Integer(3), Integer(5))->toString(), "8");
  EXPECT_EQ(f(Integer(3), Rational(5, 2))->toString(), "11/2");
  EXPECT_EQ(f(Rational(5, 2), Integer(3))->toString(), "11/2");
  EXPECT_EQ(f(Rational(5, 2), Rational(5, 2))->toString(), "5");
  EXPECT_EQ(f(Rational(5, 2), Rational(5, 3))->toString(), "25/6");

  EXPECT_EQ(f(Integer(3), Variable("a"))->toString(), "a + 3");

  EXPECT_THROW(f(Integer(1)), InvalidInputFunctionException);
  EXPECT_THROW(f(Rational(2, 3)), InvalidInputFunctionException);
  EXPECT_THROW(f(), InvalidInputFunctionException);
  EXPECT_THROW(f(Integer(1), Integer(1), Integer(1)), InvalidInputFunctionException);
}

TEST(AddTests, doArgsMatchTest) {
  Integer a;

  EXPECT_FALSE(f.doArgsMatch({}));
  EXPECT_FALSE(f.doArgsMatch({a}));
  EXPECT_TRUE(f.doArgsMatch({a, a}));
  EXPECT_FALSE(f.doArgsMatch({a, a, a}));
}

TEST(AddTests, equalsTest) {
  EXPECT_EQ(f, f);
  EXPECT_EQ(f, Add());
  EXPECT_EQ(Add(), f);
  EXPECT_EQ(f, cast<IMathObject>(Add()));
  EXPECT_EQ(cast<IMathObject>(Add()), f);
  EXPECT_NE(f, Sub());
  EXPECT_NE(Sub(), f);
  EXPECT_NE(f, UnaryPlus());
  EXPECT_NE(UnaryPlus(), f);
}

TEST(AddTests, getTypeIdTest) {
  EXPECT_EQ(Add::getTypeIdStatic(), MathObjectTypeId(MathObjectType::Add));
  EXPECT_EQ(Add().getTypeId(), MathObjectTypeId(MathObjectType::Add));
}
