#pragma once

#include "fintamath/numbers/Rational.hpp"

#include <string>

namespace fintamath {
  class Function : public MathObject<Function> {
  public:
    explicit Function(const std::string &str);

    Rational solve(const Rational &rhs, int64_t precision) const;

    Rational solve(const Rational &lhs, const Rational &rhs, int64_t precision) const;

    std::string toString() const override;

    std::unique_ptr<MathObjectBase> clone() const override;

    bool equals(const Function &rhs) const override;

  private:
    std::string name;
  };

  namespace types {
    bool isFunction(const std::string &str);

    bool isBinaryFunction(const std::string_view &str);
  }
}