#pragma once

#include "fintamath/functions/IFunction.hpp"
#include "fintamath/numbers/INumber.hpp"

namespace fintamath {

class Asin : public IFunctionCRTP<INumber, Asin, INumber> {
public:
  Asin() = default;

  std::string toString() const override {
    return "asin";
  }

protected:
  MathObjectPtr call(const ArgumentsVector &argsVect) const override;
};

}
