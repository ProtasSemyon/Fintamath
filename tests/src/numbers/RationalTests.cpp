#include <gtest/gtest.h>

#include "fintamath/numbers/Rational.hpp"

using namespace fintamath;

TEST(RationalTests, constructorTest) {
  EXPECT_EQ(Rational(), 0);
}

TEST(RationalTests, stringConstructorTest) {
  EXPECT_EQ(Rational("-93"), -93);
  EXPECT_EQ(Rational("-9.3").toString(), "-93/10");
  EXPECT_EQ(Rational("0989929039237832000.9302930929333").toString(), "9899290392378320009302930929333/10000000000000");

  EXPECT_THROW(Rational("--10"), std::invalid_argument);
  EXPECT_THROW(Rational("test"), std::invalid_argument);
  EXPECT_THROW(Rational(""), std::invalid_argument);
  EXPECT_THROW(Rational("+"), std::invalid_argument);
  EXPECT_THROW(Rational("939849.0-0023"), std::invalid_argument);
  EXPECT_THROW(Rational("a"), std::invalid_argument);
  EXPECT_THROW(Rational("a.1"), std::invalid_argument);
  EXPECT_THROW(Rational("1.a"), std::invalid_argument);
  EXPECT_THROW(Rational("1a.1"), std::invalid_argument);
  EXPECT_THROW(Rational("1.1a"), std::invalid_argument);
  EXPECT_THROW(Rational(".1"), std::invalid_argument);
  EXPECT_THROW(Rational("1."), std::invalid_argument);
  EXPECT_THROW(Rational("--10.-1"), std::invalid_argument);
  EXPECT_THROW(Rational("10.-1"), std::invalid_argument);
  EXPECT_THROW(Rational("1-0.1"), std::invalid_argument);
  EXPECT_THROW(Rational("10-.1"), std::invalid_argument);
  EXPECT_THROW(Rational("10.--1"), std::invalid_argument);
}

TEST(RationalTests, integerIntegerConstructorTest) {
  EXPECT_EQ(Rational(-380, -608).toString(), "5/8");
  EXPECT_EQ(Rational(2849300, 18493).toString(), "2849300/18493");
  EXPECT_EQ(Rational(2849300, -1893).toString(), "-2849300/1893");

  EXPECT_THROW(Rational(23070, 0), std::domain_error);
}

TEST(RationalTests, integerConstructorTest) {
  EXPECT_EQ(Rational(2), 2);
  EXPECT_EQ(Rational(Integer(10)), 10);
}

TEST(RationalTests, integerAssignmentOperatorTest) {
  Rational a;
  EXPECT_EQ(a = 2, 2);

  Rational b;
  EXPECT_EQ(b = 91820370928039, Rational("91820370928039"));
}

TEST(RationalTests, plusAssignmentOperatorTest) {
  EXPECT_EQ(Rational(2, 3) += Rational(5, 2), Rational(19, 6));
  EXPECT_EQ(Rational(-738, 10) += Rational(5, 2), Rational(-713, 10));
  EXPECT_EQ(Rational(738, 10) += Rational(5, 2), Rational(763, 10));
  EXPECT_EQ(Rational(-738, 10) += Rational(-5, 2), Rational(-763, 10));
}

TEST(RationalTests, integerPlusAssignmentOperatorTest) {
  EXPECT_EQ(Rational(-10) += 5, -5);
  EXPECT_EQ(Rational(2, 3) += -5, Rational(-13, 3));
}

TEST(RationalTests, plusOperatorTest) {
  EXPECT_EQ(Rational(170, 15) + Rational(-5, 2), Rational(53, 6));
  EXPECT_EQ(Rational(17, 19) + Rational(53, 5), Rational(1092, 95));
  EXPECT_EQ(Rational(170, 12) + Rational(2, 5), Rational(437, 30));
}

TEST(RationalTests, integerPlusOperatorTest) {
  EXPECT_EQ(Rational(170) + -5, 165);
  EXPECT_EQ(Rational(17) + 53, 70);
  EXPECT_EQ(Rational(170, 12) + 2, Rational(194, 12));
}

TEST(RationalTests, friendIntegerPlusOperatorTest) {
  EXPECT_EQ(2 + Rational(-18), -16);
  EXPECT_EQ(4938493849 + Rational(1009), 4938494858);
}

TEST(RationalTests, minusAssignmentOperatorTest) {
  EXPECT_EQ(Rational(2, 3) -= Rational(5, 2), Rational(-11, 6));
  EXPECT_EQ(Rational(-738, 10) -= Rational(5, 2), Rational(-763, 10));
  EXPECT_EQ(Rational(738, 10) -= Rational(5, 2), Rational(713, 10));
  EXPECT_EQ(Rational(-738, 10) -= Rational(-5, 2), Rational(-713, 10));
}

TEST(RationalTests, integerMinusAssignmentOperatorTest) {
  EXPECT_EQ(Rational(-738, -10) -= -5, Rational(394, 5));
  EXPECT_EQ(Rational(-738, 10) -= 5, Rational(-394, 5));
}

TEST(RationalTests, minusOperatorTest) {
  EXPECT_EQ(Rational(170, 15) - Rational(-5, 2), Rational(83, 6));
  EXPECT_EQ(Rational(17, 19) - Rational(53, 5), Rational(-922, 95));
  EXPECT_EQ(Rational(170, 12) - Rational(2, 5), Rational(413, 30));
}

TEST(RationalTests, integerMinusOperatorTest) {
  EXPECT_EQ(Rational(170) - 5, 165);
  EXPECT_EQ(Rational(17) - 53, -36);
  EXPECT_EQ(Rational(170, 12) - -2, Rational(194, 12));
}

TEST(RationalTests, friendIntegerMinusOperatorTest) {
  EXPECT_EQ(2 - Rational(-18), 20);
  EXPECT_EQ(4938493849 - Rational(1009), 4938492840);
}

TEST(RationalTests, multiplyAssignmentOperatorTest) {
  EXPECT_EQ(Rational(2, 3) *= Rational(5, 2), Rational(5, 3));
  EXPECT_EQ(Rational(-738, 10) *= Rational(5, 2), Rational(-369, 2));
  EXPECT_EQ(Rational(738, 10) *= Rational(5, 2), Rational(369, 2));
  EXPECT_EQ(Rational(-738, 10) *= Rational(-5, 2), Rational(369, 2));
}

TEST(RationalTests, integerMultiplyAssignmentOperatorTest) {
  EXPECT_EQ(Rational(2, 3) *= -5, Rational(-10, 3));
  EXPECT_EQ(Rational(738, -10) *= 5894, Rational(-4349772, 10));
  EXPECT_EQ(Rational(-738, -10) *= 10, 738);
}

TEST(RationalTests, multiplyOperatorTest) {
  EXPECT_EQ(Rational(170, 15) * Rational(-5, 2), Rational(-85, 3));
  EXPECT_EQ(Rational(17, 19) * Rational(53, 5), Rational(901, 95));
  EXPECT_EQ(Rational(170, 12) * Rational(2, 5), Rational(17, 3));
}

TEST(RationalTests, integerMultiplyOperatorTest) {
  EXPECT_EQ(Rational(2, 3) * -5, Rational(-10, 3));
  EXPECT_EQ(Rational(738, -10) * 5894, Rational(-4349772, 10));
  EXPECT_EQ(Rational(-738, -10) * 10, 738);
}

TEST(RationalTests, friendIntegerMultiplyOperatorTest) {
  EXPECT_EQ(-5 * Rational(2, 3), Rational(-10, 3));
  EXPECT_EQ(589398724 * Rational(1, 8372738), Rational(589398724, 8372738));
  EXPECT_EQ(10 * Rational(-738, -10), 738);
}

TEST(RationalTests, divideAssignmentOperatorTest) {
  EXPECT_EQ(Rational(2, 3) /= Rational(5, 2), Rational(4, 15));
  EXPECT_EQ(Rational(-738, 10) /= Rational(5, 2), Rational(-738, 25));
  EXPECT_EQ(Rational(738, 10) /= Rational(5, 2), Rational(738, 25));
  EXPECT_EQ(Rational(-738, 10) /= Rational(-5, 2), Rational(738, 25));

  EXPECT_THROW(Rational(-738, -10) /= Rational("0"), std::domain_error);
}

TEST(RationalTests, integerDivideAssignmentOperatorTest) {
  EXPECT_EQ(Rational(2, 3) /= -2, Rational(1, -3));
  EXPECT_EQ(Rational(738, -10) /= 5894, Rational(-738, 58940));
  EXPECT_EQ(Rational(-738, -10) /= 10, Rational(369, 50));
}

TEST(RationalTests, divideOperatorTest) {
  EXPECT_EQ(Rational(170, 15) / Rational(-5, 2), Rational(-68, 15));
  EXPECT_EQ(Rational(17, 19) / Rational(53, 5), Rational(85, 1007));
  EXPECT_EQ(Rational(170, 12) / Rational(2, 5), Rational(425, 12));
}

TEST(RationalTests, integerDivideOperatorTest) {
  EXPECT_EQ(Rational(2, 3) / -5, Rational(-2, 15));
  EXPECT_EQ(Rational(738, -10) / 5894, Rational(738, -58940));
}

TEST(RationalTests, friendIntegerDivideOperatorTest) {
  EXPECT_EQ(-5 / Rational(2, 3), Rational(-15, 2));
  EXPECT_EQ(589398724 / Rational(8372738), Rational(589398724, 8372738));
  EXPECT_EQ(10 / Rational(-10, -738), 738);
}

TEST(RationalTests, preIncrementOperatorTest) {
  EXPECT_EQ(++Rational(-10), -9);
  EXPECT_EQ(++Rational(1, 2), Rational(3, 2));
}

TEST(RationalTests, postIncrementOperatorTest) {
  Rational a = {5};
  EXPECT_EQ(a++, 5);
  EXPECT_EQ(a, 6);

  Rational b(2, 3);
  EXPECT_EQ(b++, Rational(2, 3));
  EXPECT_EQ(b, Rational(5, 3));
}

TEST(RationalTests, preDecrementOperatorTest) {
  EXPECT_EQ(--Rational(-10), -11);
  EXPECT_EQ(--Rational(1, 2), Rational(-1, 2));
}

TEST(RationalTests, postDecrementOperatorTest) {
  Rational a = {5};
  EXPECT_EQ(a--, 5);
  EXPECT_EQ(a, 4);

  Rational b(2, 3);
  EXPECT_EQ(b--, Rational(2, 3));
  EXPECT_EQ(b, Rational(-1, 3));
}

TEST(RationalTests, unaryPlusOperatorTest) {
  EXPECT_EQ(+Rational(-5), -5);
}

TEST(RationalTests, unaryMinusOperatorTest) {
  EXPECT_EQ(-Rational(5), -5);
}

TEST(RationalTests, equalOperatorTest) {
  EXPECT_TRUE(Rational(1, 2) == Rational(1, 2));
  EXPECT_TRUE(Rational(5, 10) == Rational(1, 2));
  EXPECT_TRUE(Rational(5, -10) == Rational(-5, 10));

  EXPECT_FALSE(Rational(1, 2) == Rational(1, 3));
  EXPECT_FALSE(Rational(3, 2) == Rational(1, 3));
  EXPECT_FALSE(Rational(55, 10) == Rational(-1, 10));
}

TEST(RationalTests, integerEqualOperatorTest) {
  EXPECT_TRUE(Rational(500) == 500);
  EXPECT_TRUE(Rational(50, -10) == -5);
}

TEST(RationalTests, friendIntegerEqualOperatorTest) {
  EXPECT_TRUE(500 == Rational(500));
  EXPECT_TRUE(-5 == Rational(50, -10));
}

TEST(RationalTests, notEqualOperatorTest) {
  EXPECT_TRUE(Rational(55, 10) != Rational(-1, 10));

  EXPECT_FALSE(Rational(5, 10) != Rational(1, 2));
  EXPECT_FALSE(Rational(5, -10) != Rational(-5, 10));
}

TEST(RationalTests, integerNotEqualOperatorTest) {
  EXPECT_TRUE(Rational(50, 10) != -5);

  EXPECT_FALSE(Rational(500) != 500);
}

TEST(RationalTests, friendIntegerNotEqualOperatorTest) {
  EXPECT_TRUE(50 != Rational(3920));

  EXPECT_FALSE(500 != Rational(500));
  EXPECT_FALSE(-5 != Rational(50, -10));
}

TEST(RationalTests, lessOperatorTest) {
  EXPECT_TRUE(Rational(5, -10) < Rational(50, 10));

  EXPECT_FALSE(Rational(5, 10) < Rational(1, 2));
  EXPECT_FALSE(Rational(5, -10) < Rational(-50, 10));
  EXPECT_FALSE(Rational(55, 10) < Rational(1, 10));
}

TEST(RationalTests, integerLessOperatorTest) {
  EXPECT_TRUE(Rational(500) < 3283);

  EXPECT_FALSE(Rational(50, -10) < -5);
}

TEST(RationalTests, friendIntegerLessOperatorTest) {
  EXPECT_TRUE(-5 < Rational(50, 10));
  EXPECT_TRUE(7387 < Rational(3983920));

  EXPECT_FALSE(500 < Rational(500));
}

TEST(RationalTests, moreOperatorTest) {
  EXPECT_TRUE(Rational(5, -10) > Rational(-50, 10));
  EXPECT_TRUE(Rational(55, 10) > Rational(1, 10));

  EXPECT_FALSE(Rational(5, 10) > Rational(1, 2));
  EXPECT_FALSE(Rational(5, -10) > Rational(50, 10));
}

TEST(RationalTests, integerMoreOperatorTest) {
  EXPECT_FALSE(Rational(500) > 3283);
  EXPECT_FALSE(Rational(50, -10) > -5);
}

TEST(RationalTests, friendIntegerMoreOperatorTest) {
  EXPECT_TRUE(738657 > Rational(320));

  EXPECT_FALSE(500 > Rational(500));
  EXPECT_FALSE(-5 > Rational(50, 10));
}

TEST(RationalTests, lessEqualOperatorTest) {
  EXPECT_TRUE(Rational(5, 10) <= Rational(1, 2));
  EXPECT_TRUE(Rational(5, -10) <= Rational(50, 10));

  EXPECT_FALSE(Rational(5, -10) <= Rational(-50, 10));
  EXPECT_FALSE(Rational(55, 10) <= Rational(1, 10));
}

TEST(RationalTests, integerLessEqualOperatorTest) {
  EXPECT_TRUE(Rational(500) <= 3283);
  EXPECT_TRUE(Rational(50, -10) <= -5);
}

TEST(RationalTests, friendIntegerLessEqualOperatorTest) {
  EXPECT_TRUE(500 <= Rational(500));
  EXPECT_TRUE(-5 <= Rational(50, 10));

  EXPECT_FALSE(73687 <= Rational(30));
}

TEST(RationalTests, moreEqualOperatorTest) {
  EXPECT_TRUE(Rational(5, 10) >= Rational(1, 2));
  EXPECT_TRUE(Rational(5, -10) >= Rational(-50, 10));
  EXPECT_TRUE(Rational(55, 10) >= Rational(1, 10));

  EXPECT_FALSE(Rational(5, -10) >= Rational(50, 10));
}

TEST(RationalTests, integerMoreEqualOperatorTest) {
  EXPECT_TRUE(Rational(50, -10) >= -5);

  EXPECT_FALSE(Rational(500) >= 3283);
}

TEST(RationalTests, friendIntegerMoreEqualOperatorTest) {
  EXPECT_TRUE(500 >= Rational(500));
  EXPECT_TRUE(738657 >= Rational(320));

  EXPECT_FALSE(-5 >= Rational(50, 10));
}

TEST(RationalTests, getIntegerTest) {
  EXPECT_EQ(Rational(5, 2).getInteger(), 2);
  EXPECT_EQ(Rational(55).getInteger(), 55);
  EXPECT_EQ(Rational(-10, 100).getInteger(), 0);
}

TEST(RationalTests, getNumeratorTest) {
  EXPECT_EQ(Rational(5, 2).getNumerator(), 1);
  EXPECT_EQ(Rational(55).getNumerator(), 0);
  EXPECT_EQ(Rational(-10, 100).getNumerator(), 1);
}

TEST(RationalTests, getDenominatorTest) {
  EXPECT_EQ(Rational(5, 2).getDenominator(), 2);
  EXPECT_EQ(Rational(55).getDenominator(), 1);
  EXPECT_EQ(Rational(-10, 100).getDenominator(), 10);
}

TEST(RationalTests, toStringTest) {
  EXPECT_EQ(Rational(5, 2).toString(), "5/2");
  EXPECT_EQ(Rational(55, -10).toString(), "-11/2");
}

TEST(RationalTests, cloneTests){
  auto a = Rational("10.1");
  EXPECT_TRUE(&a != &(*a.clone()) && a == (*a.clone()).to<Rational>());
}

TEST(RationalTests, equalsTests){
  EXPECT_TRUE(Rational("100") == Rational("100"));
  EXPECT_TRUE(Rational("10.1") == Rational(101, 10));
  EXPECT_TRUE(Rational("10.1") == Rational(-101, -10));
  EXPECT_FALSE(Rational("10.1") == Rational("-100"));
  EXPECT_FALSE(Rational("1.01") == Rational("10.1"));
}
