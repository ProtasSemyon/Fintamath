#pragma once

#include "fintamath/expressions/interfaces/IBinaryExpression.hpp"
#include "fintamath/numbers/Integer.hpp"

namespace fintamath {

class DivExpression : public IBinaryExpressionCRTP<DivExpression> {
public:
  explicit DivExpression(const ArgumentPtr &inLhsChild, const ArgumentPtr &inRhsChild);

protected:
  SimplifyFunctionsVector getFunctionsForSimplify() const override;

  SimplifyFunctionsVector getFunctionsForPostSimplify() const override;

private:
  static ArgumentPtr zeroSimplify(const ArgumentPtr &lhs, const ArgumentPtr &rhs);

  static ArgumentPtr numSimplify(const ArgumentPtr &lhs, const ArgumentPtr &rhs);

  static ArgumentPtr divSimplify(const ArgumentPtr &lhs, const ArgumentPtr &rhs);

  static ArgumentPtr mulSimplify(const ArgumentPtr &lhs, const ArgumentPtr &rhs);

  static ArgumentPtr sumSimplify(const ArgumentPtr &lhs, const ArgumentPtr &rhs);

  static ArgumentPtr sumSumSimplify(const ArgumentPtr &lhs, const ArgumentPtr &rhs);

  static ArgumentPtr sumMulSimplify(const ArgumentPtr &lhs, const ArgumentPtr &rhs);

  static std::pair<ArgumentPtr, ArgumentPtr> mulSumSimplify(const ArgumentPtr &lhs, const ArgumentPtr &rhs);

  static ArgumentPtr divPowerSimplify(const ArgumentPtr &lhs, const ArgumentPtr &rhs);

  static std::pair<ArgumentPtr, ArgumentPtr> getRateValuePair(const ArgumentPtr &rhs);

  static ArgumentPtr addRatesToValue(const ArgumentsPtrVector &rates, const ArgumentPtr &value);
};

}