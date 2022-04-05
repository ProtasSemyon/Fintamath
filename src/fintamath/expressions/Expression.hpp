#pragma once

#include <memory>
#include <vector>

#include "fintamath/core/MathObject.hpp"

namespace fintamath {
  class Expression : public MathObject<Expression> {
  public:
    struct Elem {
      std::shared_ptr<MathObjectBase> info;
      std::shared_ptr<Elem> left;
      std::shared_ptr<Elem> right;
    };

    Expression() = default;

    explicit Expression(const std::string &str);

    std::string toString() const override;

    std::unique_ptr<MathObjectBase> clone() const override;

    bool equals(const Expression &rhs) const override;

    std::string solve();

  private:
    std::shared_ptr<Elem> root;

    void makeExpression(const std::vector<std::string> &tokensVect);
  };
}