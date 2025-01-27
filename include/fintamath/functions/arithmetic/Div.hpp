#pragma once

#include "fintamath/core/IArithmetic.hpp"
#include "fintamath/functions/IOperator.hpp"

namespace fintamath {

class Integer;
class INumber;

class Div : public IOperatorCRTP<IArithmetic, Div, IArithmetic, IArithmetic> {
public:
  Div() : IOperatorCRTP(IOperator::Priority::Multiplication, false) {
  }

  std::string toString() const override {
    return "/";
  }

  static MathObjectTypeId getTypeIdStatic() {
    return MathObjectTypeId(MathObjectType::Div);
  }

protected:
  std::unique_ptr<IMathObject> call(const ArgumentsRefVector &argsVect) const override;

private:
  static std::unique_ptr<IMathObject> multiDivSimplify(const IArithmetic &lhs, const IArithmetic &rhs);

  static std::unique_ptr<IMathObject> divSimplify(const Integer &lhs, const Integer &rhs);
};

}
