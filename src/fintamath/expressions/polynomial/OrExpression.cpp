#include "fintamath/expressions/polynomial/OrExpression.hpp"

#include "fintamath/expressions/ExpressionFunctions.hpp"
#include "fintamath/functions/logic/Or.hpp"
#include <memory>

namespace fintamath {

const Or OR;

OrExpression::OrExpression(ArgumentsPtrVector &&inPolynomVect) : IPolynomExpression(std::move(inPolynomVect)) {
  if (!polynomVect.empty()) {
    compress();
  }
}

std::string OrExpression::toString() const {
  return binaryOperatorToString(OR, polynomVect);
}

MathObjectPtr OrExpression::toMinimalObject() const {
  return simplify(false);
}

MathObjectPtr OrExpression::simplify(bool /*isPrecise*/) const {
  MathObjectPtr result = polynomVect.front()->clone();
  for (size_t i = 1; i < polynomVect.size(); i++) {
    const auto &lhsPtr = result;
    const auto &rhsPtr = polynomVect[i];
    const auto &lhs = *lhsPtr;
    const auto &rhs = *rhsPtr;

    if (const auto *lhsBool = cast<Boolean>(&lhs)) {
      if (*lhsBool == true) {
        result = std::make_unique<Boolean>(true);
      } else {
        *result = *rhsPtr;
      }
      continue;
    }

    if (const auto *rhsBool = cast<Boolean>(&rhs)) {
      if (*rhsBool == true) {
        result = std::make_unique<Boolean>(true);
      } else {
        *result = *lhsPtr;
      }
      continue;
    }

    if (lhs == notL(rhs)) {
      result = std::make_unique<Boolean>(true);
    }
  }

  return result;
}

const IFunction *OrExpression::getFunction() const {
  return &OR;
}

IMathObject *OrExpression::simplify() {
  return this;
}
}