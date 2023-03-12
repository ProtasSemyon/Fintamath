#pragma once

#include "fintamath/expressions/IExpression.hpp"

namespace fintamath {

class IBinaryExpression : virtual public IExpression {
public:
  IBinaryExpression(const IBinaryExpression &rhs);

  IBinaryExpression(IBinaryExpression &&rhs) noexcept = default;

  IBinaryExpression &operator=(const IBinaryExpression &rhs);

  IBinaryExpression &operator=(IBinaryExpression &&rhs) noexcept = default;

  explicit IBinaryExpression(const IFunction &func, std::shared_ptr<IMathObject> lhsChild,
                             std::shared_ptr<IMathObject> rhsChild);

  void setPrecision(uint8_t precision) final;

  std::string toString() const final;

  std::shared_ptr<IFunction> getFunction() const final;

protected:
  void validate() const final;

  void compress() final;

protected:
  std::shared_ptr<IFunction> func;

  std::shared_ptr<IMathObject> lhsChild;

  std::shared_ptr<IMathObject> rhsChild;
};

template <typename Derived>
class IBinaryExpressionCRTP : virtual public IExpressionCRTP<Derived>, virtual public IBinaryExpression {};

}