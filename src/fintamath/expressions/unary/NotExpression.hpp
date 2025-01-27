#pragma once

#include "fintamath/expressions/interfaces/IUnaryExpression.hpp"

namespace fintamath {

class NotExpression : public IUnaryExpressionCRTP<NotExpression> {
public:
  explicit NotExpression(const ArgumentPtr &inChild);

  static MathObjectTypeId getTypeIdStatic() {
    return MathObjectTypeId(MathObjectType::NotExpression);
  }

protected:
  SimplifyFunctionsVector getFunctionsForPreSimplify() const override;

  SimplifyFunctionsVector getFunctionsForPostSimplify() const override;

private:
  static ArgumentPtr callFunctionSimplify(const IFunction &func, const ArgumentPtr &rhs);

  static ArgumentPtr logicNegatableSimplify(const IFunction &func, const ArgumentPtr &rhs);

  static ArgumentPtr nestedNotSimplify(const IFunction &func, const ArgumentPtr &rhs);

  static std::shared_ptr<IFunction> getLogicOppositeFunction(const IFunction &function);
};

}