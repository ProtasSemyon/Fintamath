#include "gtest/gtest.h"

#include "fintamath/functions/arithmetic/Abs.hpp"

#include "fintamath/literals/Variable.hpp"
#include "fintamath/numbers/Rational.hpp"
#include "fintamath/numbers/Real.hpp"

using namespace fintamath;

const Abs f;

TEST(AbsTests, toStringTest) {
  EXPECT_EQ(f.toString(), "abs");
}

TEST(AbsTests, getFunctionTypeTest) {
  EXPECT_EQ(f.getFunctionType(), IFunction::Type::Unary);
}

TEST(AbsTests, callTest) {
  EXPECT_EQ(f(Integer(10))->toString(), "10");
  EXPECT_EQ(f(Integer(-10))->toString(), "10");
  EXPECT_EQ(f(Integer("-210"))->toString(), "210");
  EXPECT_EQ(f(Integer("4545628562"))->toString(), "4545628562");

  EXPECT_EQ(f(Rational(-5, 2))->toString(), "5/2");
  EXPECT_EQ(f(Rational(-1, 100))->toString(), "1/100");
  EXPECT_EQ(f(Rational(1, -100))->toString(), "1/100");
  EXPECT_EQ(f(Rational(10, 1000))->toString(), "1/100");

  EXPECT_EQ(f(Real("8465132.321651651"))->toString(), "8465132.321651651");
  EXPECT_EQ(f(Real("-98465136846516354684651.351"))->toString(), "98465136846516354684651.351");

  EXPECT_EQ(f(Variable("a"))->toString(), "abs(a)");

  EXPECT_THROW(f(), InvalidInputFunctionException);
  EXPECT_THROW(f(Integer(1), Integer(1), Integer(1)), InvalidInputFunctionException);
}
