#pragma once

#include "fintamath/core/IComparable.hpp"
#include "fintamath/functions/IOperator.hpp"

namespace fintamath {

class MoreEqv : public IOperatorCRTP<MoreEqv, IComparable, IComparable> {
public:
  MoreEqv() : IOperatorCRTP(IOperator::Priority::Comparison) {
  }

  std::string toString() const override {
    return ">=";
  }

protected:
  MathObjectPtr call(const ArgumentsVector &argsVect) const override;
};

}