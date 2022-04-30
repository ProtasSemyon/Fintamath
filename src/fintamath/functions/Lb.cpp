#include "Lb.hpp"
#include "NamespaceFunctions.hpp"

namespace fintamath {

  std::string Lb::toString() const {
    return "lb";
  }

  MathObjectPtr Lb::operator()(const MathObject &rhs) const {
    const int64_t defaultPrecision = 36;
    auto newRhs = meta::convertRhsToLhsType(Rational(), rhs);
    return std::make_unique<Rational>(functions::lb(newRhs->to<Rational>(), defaultPrecision));
  }

  bool Lb::equals(const Lb & /*rhs*/) const {
    return true;
  }

  MathObjectPtr Lb::call(const std::vector<std::reference_wrapper<const MathObject>> &argsVect) const {
    if (argsVect.size() != 1) {
      throw std::invalid_argument("The number of arguments must be 1");
    }
    return Lb::operator()(argsVect.at(0).get());
  }

}