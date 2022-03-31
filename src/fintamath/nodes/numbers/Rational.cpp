#include "fintamath/nodes/numbers/Rational.hpp"

#include <algorithm>
#include <stdexcept>

namespace fintamath {
  static Integer gcd(const Integer &lhs, const Integer &rhs);
  static Integer lcm(const Integer &lhs, const Integer &rhs);

  Rational::Rational(const std::string_view &str) {
    size_t firstDigitNum = 0;
    size_t firstDotNum = std::distance(str.begin(), std::find(str.begin(), str.end(), '.'));

    bool isNegative = false;
    if (str.front() == '-') {
      isNegative = true;
      firstDigitNum++;
    }

    Integer intPart;
    try {
      intPart = Integer(str.substr(firstDigitNum, firstDotNum - firstDigitNum));
    } catch (const std::invalid_argument &) {
      throw std::invalid_argument("Rational invalid input");
    }

    if (firstDotNum != str.size()) {
      try {
        auto numeratorStr = str.substr(firstDotNum + 1);
        std::string denominatorStr(numeratorStr.size() + 1, '0');
        denominatorStr.front() = '1';
        numerator = Integer(numeratorStr);
        denominator = Integer(denominatorStr);
      } catch (const std::invalid_argument &) {
        throw std::invalid_argument("Rational invalid input");
      }
    }

    if (intPart < 0 || numerator < 0) {
      throw std::invalid_argument("Rational invalid input");
    }

    toIrreducibleRational();
    numerator += intPart * denominator;
    if (numerator != 0) {
      sign = isNegative;
    }
  }

  Rational::Rational(Integer numerator, Integer denominator)
      : numerator(std::move(numerator)), denominator(std::move(denominator)) {
    toIrreducibleRational();
  }

  Rational::Rational(Integer rhs) : numerator(std::move(rhs)) {
    fixNegative();
  }

  Rational &Rational::operator=(const Integer &rhs) {
    return *this = Rational(rhs);
  }

  Rational &Rational::operator+=(const Rational &rhs) {
    Rational tmpRhs = rhs;
    toCommonDenominators(*this, tmpRhs);
    numerator += tmpRhs.numerator;
    toIrreducibleRational();
    return *this;
  }

  Rational &Rational::operator+=(const Integer &rhs) {
    return *this += Rational(rhs);
  }

  Rational Rational::operator+(const Rational &rhs) const {
    Rational lhs = *this;
    return lhs += rhs;
  }

  Rational Rational::operator+(const Integer &rhs) const {
    return *this + Rational(rhs);
  }

  Rational operator+(const Integer &lhs, const Rational &rhs) {
    return Rational(lhs) + rhs;
  }

  Rational &Rational::operator-=(const Rational &rhs) {
    Rational tmpRhs = rhs;
    toCommonDenominators(*this, tmpRhs);
    numerator -= tmpRhs.numerator;
    toIrreducibleRational();
    return *this;
  }

  Rational &Rational::operator-=(const Integer &rhs) {
    return *this -= Rational(rhs);
  }

  Rational Rational::operator-(const Rational &rhs) const {
    Rational lhs = *this;
    return lhs -= rhs;
  }

  Rational Rational::operator-(const Integer &rhs) const {
    return *this - Rational(rhs);
  }

  Rational operator-(const Integer &lhs, const Rational &rhs) {
    return Rational(lhs) - rhs;
  }

  Rational &Rational::operator*=(const Rational &rhs) {
    numerator *= rhs.numerator;
    denominator *= rhs.denominator;
    sign = !((sign && rhs.sign) || (!sign && !rhs.sign));
    toIrreducibleRational();
    return *this;
  }

  Rational &Rational::operator*=(const Integer &rhs) {
    return *this *= Rational(rhs);
  }

  Rational Rational::operator*(const Rational &rhs) const {
    Rational lhs = *this;
    return lhs *= rhs;
  }

  Rational Rational::operator*(const Integer &rhs) const {
    return *this * Rational(rhs);
  }

  Rational operator*(const Integer &lhs, const Rational &rhs) {
    return Rational(lhs) * rhs;
  }

  Rational &Rational::operator/=(const Rational &rhs) {
    numerator *= rhs.denominator;
    denominator *= rhs.numerator;
    sign = !((sign && rhs.sign) || (!sign && !rhs.sign));
    toIrreducibleRational();
    return *this;
  }

  Rational &Rational::operator/=(const Integer &rhs) {
    return *this /= Rational(rhs);
  }

  Rational Rational::operator/(const Rational &rhs) const {
    Rational lhs = *this;
    return lhs /= rhs;
  }

  Rational Rational::operator/(const Integer &rhs) const {
    return *this / Rational(rhs);
  }

  Rational operator/(const Integer &lhs, const Rational &rhs) {
    return Rational(lhs) / rhs;
  }

  Rational &Rational::operator++() {
    return *this += 1;
  }

  Rational Rational::operator++(int) {
    Rational val = *this;
    *this += 1;
    return val;
  }

  Rational &Rational::operator--() {
    return *this -= 1;
  }

  Rational Rational::operator--(int) {
    Rational val = *this;
    *this -= 1;
    return val;
  }

  Rational Rational::operator+() const {
    return *this;
  }

  Rational Rational::operator-() const {
    Rational val = *this;
    val.sign = !val.sign;
    return val;
  }

  bool Rational::operator==(const Rational &rhs) const {
    return (sign == rhs.sign && numerator == rhs.numerator && denominator == rhs.denominator);
  }

  bool Rational::operator==(const Integer &rhs) const {
    return *this == Rational(rhs);
  }

  bool operator==(const Integer &lhs, const Rational &rhs) {
    return Rational(lhs) == rhs;
  }

  bool Rational::operator!=(const Rational &rhs) const {
    return !(*this == rhs);
  }

  bool Rational::operator!=(const Integer &rhs) const {
    return *this != Rational(rhs);
  }

  bool operator!=(const Integer &lhs, const Rational &rhs) {
    return Rational(lhs) != rhs;
  }

  bool Rational::operator<(const Rational &rhs) const {
    Rational lhs = *this;
    Rational tmpRhs = rhs;
    toCommonDenominators(lhs, tmpRhs);
    return (lhs.numerator < tmpRhs.numerator);
  }

  bool Rational::operator<(const Integer &rhs) const {
    return *this < Rational(rhs);
  }

  bool operator<(const Integer &lhs, const Rational &rhs) {
    return Rational(lhs) < rhs;
  }

  bool Rational::operator>(const Rational &rhs) const {
    Rational lhs = *this;
    Rational tmpRhs = rhs;
    toCommonDenominators(lhs, tmpRhs);
    return (lhs.numerator > tmpRhs.numerator);
  }

  bool Rational::operator>(const Integer &rhs) const {
    return *this > Rational(rhs);
  }

  bool operator>(const Integer &lhs, const Rational &rhs) {
    return Rational(lhs) > rhs;
  }

  bool Rational::operator<=(const Rational &rhs) const {
    Rational lhs = *this;
    Rational tmpRhs = rhs;
    toCommonDenominators(lhs, tmpRhs);
    return (lhs.numerator <= tmpRhs.numerator);
  }

  bool Rational::operator<=(const Integer &rhs) const {
    return *this <= Rational(rhs);
  }

  bool operator<=(const Integer &lhs, const Rational &rhs) {
    return Rational(lhs) <= rhs;
  }

  bool Rational::operator>=(const Rational &rhs) const {
    Rational lhs = *this;
    Rational tmpRhs = rhs;
    toCommonDenominators(lhs, tmpRhs);
    return (lhs.numerator >= tmpRhs.numerator);
  }

  bool Rational::operator>=(const Integer &rhs) const {
    return *this >= Rational(rhs);
  }

  bool operator>=(const Integer &lhs, const Rational &rhs) {
    return Rational(lhs) >= rhs;
  }

  Integer Rational::getInteger() const {
    return numerator / denominator;
  }

  Integer Rational::getNumerator() const {
    return numerator % denominator;
  }

  Integer Rational::getDenominator() const {
    return denominator;
  }

  Rational Rational::round(size_t precision) const {
    return Rational(toString(precision));
  }

  std::string Rational::toString() const {
    return (sign ? "-" : "") + numerator.toString() + "/" + denominator.toString();
  }

  std::string Rational::toString(size_t precision) const {
    const int64_t base = 10;
    const int64_t roundUp = 5;

    std::string precisionStr(precision + 2, '0');
    precisionStr.front() = '1';

    Integer val = numerator * Integer(precisionStr) / denominator;
    if (val % base >= roundUp) {
      val += base;
    }
    val /= base;

    std::string strVal = val.toString();
    if (strVal.size() <= precision) {
      strVal.insert(strVal.begin(), precision + 1 - strVal.size(), '0');
    }
    strVal.insert(strVal.end() - (int64_t)precision, '.');

    while (!strVal.empty() && strVal.back() == '0') {
      strVal.pop_back();
    }
    if (strVal.back() == '.') {
      strVal.pop_back();
    }

    if (sign) {
      strVal.insert(strVal.begin(), '-');
    }

    return strVal;
  }

  void Rational::fixZero() {
    if (numerator == 0) {
      sign = false;
      denominator = 1;
    }
  }

  void Rational::fixNegative() {
    if (numerator < 0) {
      numerator *= -1;
      sign = !sign;
    }
    if (denominator < 0) {
      denominator *= -1;
      sign = !sign;
    }
  }

  void Rational::toIrreducibleRational() {
    if (denominator == 0) {
      throw std::domain_error("Div by zero");
    }
    fixNegative();
    Integer gcdVal = gcd(numerator, denominator);
    numerator /= gcdVal;
    denominator /= gcdVal;
    fixZero();
  }

  void Rational::toCommonDenominators(Rational &lhs, Rational &rhs) {
    Integer lcmVal = lcm(lhs.denominator, rhs.denominator);

    if (lhs.sign) {
      lhs.numerator *= -1;
    }
    lhs.numerator *= (lcmVal / lhs.denominator);
    lhs.denominator = lcmVal;
    lhs.sign = false;

    if (rhs.sign) {
      rhs.numerator *= -1;
    }
    rhs.numerator *= (lcmVal / rhs.denominator);
    rhs.denominator = lcmVal;
    rhs.sign = false;
  }
  std::shared_ptr<Object> Rational::clone() const {
    return std::make_shared<Rational>(*this);
  }
  bool Rational::equals(const Object &rhs) const {
    if (rhs.is<Rational>() && (this->sign == rhs.to<Rational>().sign) &&
        (this->numerator == rhs.to<Rational>().numerator) && (this->denominator == rhs.to<Rational>().denominator)) {
      return true;
    }
    return false;
  }

  // Using Euclid's algorithm
  static Integer gcd(const Integer &lhs, const Integer &rhs) {
    Integer tmpLhs = lhs;
    Integer tmpRhs = rhs;
    while (tmpRhs != 0) {
      Integer buff = tmpLhs % tmpRhs;
      tmpLhs = tmpRhs;
      tmpRhs = buff;
    }
    return tmpLhs;
  }

  // Using the formula lcm(a, b) = a * b / gcd(a, b)
  static Integer lcm(const Integer &lhs, const Integer &rhs) {
    return lhs * rhs / gcd(lhs, rhs);
  }
}
