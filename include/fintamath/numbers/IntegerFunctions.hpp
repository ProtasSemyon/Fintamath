#pragma once

#include "fintamath/exceptions/UndefinedBinaryOperatorException.hpp"
#include "fintamath/numbers/Integer.hpp"

namespace fintamath {

// Use exponentiation by squaring with constant auxiliary memory (iterative version).
// https://en.wikipedia.org/wiki/Exponentiation_by_squaring#With_constant_auxiliary_memory.
template <typename Lhs, typename = std::enable_if_t<std::is_base_of_v<INumber, Lhs>>>
Lhs pow(const Lhs &lhs, Integer rhs) {
  if (lhs == 0 && rhs == 0) {
    throw UndefinedBinaryOperatorException("^", lhs.toString(), rhs.toString());
  }

  if (rhs < 0) {
    return pow(1 / lhs, -rhs);
  }

  Lhs res(1);
  Lhs sqr = lhs;

  while (rhs != 0) {
    if ((*(rhs.toString().end() - 1) - '0') % 2 == 0) {
      rhs /= 2;
      sqr = sqr * sqr;
    }
    else {
      --rhs;
      res = res * sqr;
    }
  }

  return res;
}

Integer abs(const Integer &rhs);

Integer gcd(const Integer &lhs, const Integer &rhs);

Integer lcm(const Integer &lhs, const Integer &rhs);

Integer intSqrt(const Integer &rhs);

Integer intSqrt(const Integer &rhs, Integer &remainder);

Integer factorial(const Integer &rhs);

Integer factorial(const Integer &rhs, size_t order);

Integer combinations(const Integer &totalNumber, const Integer &choosedNumber);

Integer multinomialCoefficient(const Integer &totalNumber, const std::vector<Integer> &groupNumbers);

}
