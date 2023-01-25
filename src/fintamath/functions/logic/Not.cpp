#include "fintamath/functions/logic/Not.hpp"

#include "fintamath/literals/Boolean.hpp"

namespace fintamath {

MathObjectPtr Not::call(const ArgumentsVector &argsVect) const {
  return std::make_unique<Boolean>(!argsVect.front().get().to<Boolean>());
}

}
