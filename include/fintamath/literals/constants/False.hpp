#pragma once

#include "fintamath/literals/Boolean.hpp"
#include "fintamath/literals/constants/IConstant.hpp"

namespace fintamath {

class False : public IConstantCRTP<Boolean, False> {
public:
  std::string toString() const override {
    return Boolean(false).toString();
  }

  static MathObjectTypeId getTypeIdStatic() {
    return MathObjectTypeId(MathObjectType::False);
  }

protected:
  std::unique_ptr<IMathObject> call() const override;
};

}
