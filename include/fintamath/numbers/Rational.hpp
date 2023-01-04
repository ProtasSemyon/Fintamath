#pragma once

#include "fintamath/numbers/Integer.hpp"

namespace fintamath {

class Rational : public INumberCRTP<Rational> {
public:
  Rational() = default;

  explicit Rational(const std::string &str);

  explicit Rational(Integer numerator, Integer denominator);

  Rational(Integer rhs);

  Rational(int64_t rhs);

  std::string toString() const override;

  MathObjectPtr simplify() const override;

  Integer getInteger() const;

  Integer getNumerator() const;

  Integer getDenominator() const;

protected:
  bool equals(const Rational &rhs) const override;

  bool less(const Rational &rhs) const override;

  bool more(const Rational &rhs) const override;

  Rational &add(const Rational &rhs) override;

  Rational &substract(const Rational &rhs) override;

  Rational &multiply(const Rational &rhs) override;

  Rational &divide(const Rational &rhs) override;

  Rational &negate() override;

  Rational &increase() override;

  Rational &decrease() override;

private:
  void parse(const std::string &str);

  void fixNegative();

  void fixZero();

  void toIrreducibleRational();

  static void toCommonDenominators(Rational &lhs, Rational &rhs);

  Integer numerator = 0;
  Integer denominator = 1;
  bool sign{};
};

}