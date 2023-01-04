#pragma once

#include "fintamath/core/IArithmetic.hpp"
#include "fintamath/functions/IFunction.hpp"
#include "fintamath/numbers/INumber.hpp"

namespace fintamath {

class Sqrt : public IFunctionCRTP<Sqrt, INumber> {
public:
  Sqrt() = default;

  std::string toString() const override {
    return "sqrt";
  }

protected:
  MathObjectPtr call(const ArgumentsVector &argsVect) const override;
};

}