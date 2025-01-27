#pragma once

#include <functional>
#include <memory>
#include <string>
#include <typeinfo>
#include <vector>

#include "fintamath/core/MathObjectTypes.hpp"

namespace fintamath {

class IMathObject;

using ArgumentRef = std::reference_wrapper<const IMathObject>;
using ArgumentPtr = std::shared_ptr<const IMathObject>;

using ArgumentsRefVector = std::vector<ArgumentRef>;
using ArgumentsPtrVector = std::vector<ArgumentPtr>;
using ArgumentsTypeIdsVector = std::vector<size_t>;

}
