#pragma once

#include "fintamath/functions/IFunction.hpp"
#include "fintamath/numbers/INumber.hpp"

namespace fintamath {

class Root : public IFunctionCRTP<INumber, Root, INumber, INumber> {
public:
  Root() = default;

  std::string toString() const override {
    return "root";
  }

protected:
  std::unique_ptr<IMathObject> call(const ArgumentsRefVector &argsVect) const override;
};

}
