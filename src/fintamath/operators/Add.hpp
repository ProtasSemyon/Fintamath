#include "fintamath/operators/Operator.hpp"
#include "fintamath/expressions/Expression.hpp"

namespace fintamath {
  class Add: public OperatorImpl<Add> {
  public:

    explicit Add() = default;

    int getPriority() const override;

    std::string toString() const override;

    MathObjectPtr operator()(const MathObject &lhs, const MathObject &rhs) const;

  protected:
    bool equals(const Add& rhs) const override;
    MathObjectPtr call(const std::vector<std::reference_wrapper<const MathObject>> &argsVect) const override;

  private:
    int priority = 1;
  };
}

