#include "Operator.hpp"

#include <regex>

#include "fintamath/functions/NamespaceFunctions.hpp"

namespace fintamath {
  namespace types {
    bool isOperator(const std::string &str) {
      std::regex reg(R"(\+|\-|\*|\/|\^)");
      return regex_search(str, reg);
    }
  }
}
