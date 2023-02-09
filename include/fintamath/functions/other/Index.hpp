#pragma once

#include "fintamath/functions/IOperator.hpp"

namespace fintamath {

class INumber;

class Index : public IOperatorCRTP<IMathObject, Index, IMathObject, IMathObject> {
public:
  Index() : IOperatorCRTP(IOperator::Priority::Exponentiation, false) {
  }

  std::string toString() const override {
    return "_";
  }

protected:
  MathObjectPtr call(const ArgumentsVector &argsVect) const override;
};

}
