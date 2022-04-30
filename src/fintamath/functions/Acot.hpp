#include "Function.hpp"

namespace fintamath {
  class Acot: public FunctionImpl<Acot> {
  public:

    explicit Acot() = default;

    std::string toString() const override;

    MathObjectPtr operator()(const MathObject &rhs) const;

  protected:

    bool equals(const Acot& rhs) const override;

    MathObjectPtr call(const std::vector<std::reference_wrapper<const MathObject>> &argsVect) const override;
  };
}