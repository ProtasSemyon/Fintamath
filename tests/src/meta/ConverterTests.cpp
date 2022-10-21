#include <gtest/gtest.h>

#include "fintamath/helpers/Converter.hpp"

#include "fintamath/numbers/Rational.hpp"

using namespace fintamath;
using namespace fintamath::helpers;

TEST(ConverterTests, convertTest) {
  EXPECT_TRUE(convertMathObject(Integer(), Rational())->is<Rational>());

  EXPECT_FALSE(convertMathObject(Rational(), Integer()));
}
