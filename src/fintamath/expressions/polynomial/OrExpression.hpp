#pragma once

#include <cstdint>

#include "fintamath/expressions/polynomial/IPolynomExpression.hpp"

namespace fintamath {
class OrExpression : public IPolynomExpressionCRTP<OrExpression> {
public:
  explicit OrExpression(ArgumentsPtrVector children);

  std::string toString() const override;

  std::unique_ptr<IMathObject> simplify(bool isPrecise) const override;

protected:
  std::shared_ptr<IMathObject> simplify() override;
};

}