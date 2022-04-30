#include "fintamath/operators/Operator.hpp"

namespace fintamath {
  class Div: public OperatorImpl<Div> {
  public:

    explicit Div() = default;

    std::string toString() const override;

    int getPriority() const override;

    MathObjectPtr operator()(const MathObject &lhs, const MathObject &rhs) const;

  protected:
    bool equals(const Div& rhs) const override;
    MathObjectPtr call(const std::vector<std::reference_wrapper<const MathObject>> &argsVect) const override;

  private:
    int priority = 2;
  };
}