#include "fintamath/literals/Variable.hpp"

#include <regex>

#include "fintamath/exceptions/InvalidInputException.hpp"

namespace fintamath {

bool isVariable(const std::string &str);

Variable::Variable(const std::string &str) {
  if (!isVariable(str)) {
    throw InvalidInputException(str);
  }

  name = str;
}

std::string Variable::toString() const {
  return name;
}

bool isVariable(const std::string &str) {
  if (str.size() != 1) {
    return false;
  }

  char ch = str.front();

  return (ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z');
}

}
