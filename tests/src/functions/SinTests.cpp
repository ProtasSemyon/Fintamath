#include "gtest/gtest.h"
#include <fintamath/operators/Add.hpp>
#include <fintamath/variables/Variable.hpp>
#include <fintamath/constants/Constant.hpp>

#include <fintamath/functions/Sin.hpp>

using namespace fintamath;

TEST(SinTests, toStringTest) {
  EXPECT_EQ(Sin().toString(), "sin");
}

TEST(SinTests, callTest){
  EXPECT_EQ(Sin()(Integer(0))->to<Rational>().toString(5), "0");
  EXPECT_EQ(Sin()(Integer(10))->to<Rational>().toString(10), "-0.5440211109");
  EXPECT_EQ(Sin()(Integer(5))->to<Rational>().toString(36), "-0.958924274663138468893154406155993973");
  EXPECT_EQ(Sin()(Rational(1, 10))->to<Rational>().toString(10), "0.0998334166");
  EXPECT_EQ(Sin()(Rational(Constant("pi").toRational(10) / 2))->to<Rational>().toString(5), "1");

  EXPECT_ANY_THROW(Sin()(Variable("a")));

  std::unique_ptr<Function> f = std::make_unique<Sin>();
  EXPECT_ANY_THROW((*f)());
  EXPECT_ANY_THROW((*f)(Integer(1), Integer(1), Integer(1)));
}

TEST(SinTests, equalsTest) {
  EXPECT_TRUE(Sin() == Sin());
  EXPECT_FALSE(Sin() == Add());
}
