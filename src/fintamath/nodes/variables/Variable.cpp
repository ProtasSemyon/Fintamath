//
// Created by dashk on 31.03.2022.
//
#include "Variable.hpp"
namespace fintamath {
  Variable::Variable(const std::string &strVariable) {
    if (!types::isVariable(strVariable)) {
      throw std::invalid_argument("Variable invalid input");
    }
    name = strVariable;
  }

  std::string Variable::toString() const {
    return name;
  }

  std::shared_ptr<Object> Variable::clone() const {
    return std::make_shared<Variable>(*this);
  }

  bool Variable::equals(const Object &rhs) const {
    if (rhs.is<Variable>() && (this->name == rhs.to<Variable>().name)){
      return true;
    }
    return false;
  }

  Expression Variable::operator+(const Node& rhs) const{
    return Expression(this->name + "+" + rhs.toString());
  }

  Expression Variable::operator-(const Node& rhs) const{
    return Expression(this->name + "-" + rhs.toString());
  }

  Expression Variable::operator*(const Node& rhs) const{
    return Expression(this->name + "*" + rhs.toString());
  }

  Expression Variable::operator/(const Node& rhs) const{
    return Expression(this->name + "/" + rhs.toString());
  }

  bool Variable::operator==(const Node& rhs) const{
    return this->equals(rhs);
  }

  bool Variable::operator!=(const Node& rhs) const{
    return !this->equals(rhs);
  }

  namespace types {
      bool isVariable(const std::string &str) {
        if (str.size() == 1 && ((str[0] >= 'A' && str[0] <= 'Z') || (str[0] >= 'a' && str[0] <= 'z'))) {
          return true;
        }
        return false;
    }
  }
}